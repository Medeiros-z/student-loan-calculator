#include "Loan.h"
#include <chrono>

using namespace std;
using std::chrono::year_month_day;

Loan::Loan(string name, double principle, double interest_rate, year_month_day date) {
    this->name = name;
    this->principle = principle;
    this->interest_rate = interest_rate;
    this->date = date;
}

string Loan::get_name() const {
    return this->name;
}

double Loan::get_principle() const {
    return this->principle;
}

double Loan::get_interest_rate() const {
    return this->interest_rate;
}

year_month_day Loan::get_date() const {
    return this->date;
}

void Loan::make_payment(Payment payment) {

    // Iterator finds the first payment in the vector with a later date,
    // so 'payment' can be placed in the vector and keep it sorted
    const auto iterator = upper_bound(payments.begin(), payments.end(), payment,
        [](const Payment &a, const Payment &b) {
            return a.get_date() < b.get_date();
        });

    this->payments.insert(iterator, payment);
}

// Helper functions for get_current_amount
namespace {

    using namespace std::chrono;

    // Returns number of days between two calendar dates
    long days_between(const year_month_day& from, const year_month_day& to) {
        return (sys_days(to) - sys_days(from)).count();
    }

    // Current date as a year_month_day calendar date
    year_month_day today() {
        return floor<days>(system_clock::now());
    }
}

double Loan::get_current_amount() const {
    const double daily_interest_rate = this->interest_rate / 365;
    double balance = this->principle;
    double accrued_interest = 0.0;
    year_month_day d = this->date; // d will cycle through dates with account activity, starting with taking out the loan

    // Accrue the interest between payments, adjusting the current balance according to the interest and payments
    for (const Payment &payment : payments) {
        long days = days_between(d, payment.get_date());
        accrued_interest += balance * daily_interest_rate * days;

        double payment_amount = payment.get_amount();
        if (payment_amount <= accrued_interest) { // payment was less than accrued interest
            accrued_interest -= payment_amount;
        } else { // payment was more than accrued interest -> part of the principle is paid off
            payment_amount -= accrued_interest;
            accrued_interest = 0.0;
            balance -= payment_amount;
            if (balance < 0.0) { balance = 0.0; }
        }

        d = payment.get_date();
    }

    long remain_days = days_between(d, today());
    accrued_interest += balance * daily_interest_rate * remain_days;

    return balance + accrued_interest;

}








