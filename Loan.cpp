#include "Loan.h"
#include <chrono>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using std::chrono::year_month_day;

Loan::Loan(string name, double principle, double interest_rate, year_month_day date, vector<Payment> payments) {
    this->name = name;
    this->principle = principle;
    this->interest_rate = interest_rate;
    this->date = date;
    this->payments = payments;
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

std::vector<Payment> Loan::get_payments() const {
    return this->payments;
}

void Loan::make_payment(const Payment payment) {

    // Iterator finds the first payment in the vector with a later date,
    // so 'payment' can be placed in the vector and keep it sorted
    const auto iterator = ranges::upper_bound(payments, payment,
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
        long const days = days_between(d, payment.get_date());
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

    long const remain_days = days_between(d, today());
    accrued_interest += balance * daily_interest_rate * remain_days;

    return balance + accrued_interest;

}

// Helper functions for JSON operations
namespace {

    using namespace std::chrono;

    string date_to_string(const year_month_day& date)  {
        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(4) << static_cast<int>(date.year()) << "-"
            << std::setw(2) << static_cast<unsigned>(date.month()) << "-"
            << std::setw(2) << static_cast<unsigned>(date.day());
        return oss.str();
    }

    year_month_day string_to_date(const string date_string) {
        int y, m, d;
        std::sscanf(date_string.c_str(), "%d-%d-%d", &y, &m, &d);
        return year_month_day(
            year{y},
            month{static_cast<unsigned>(m)},
            day{static_cast<unsigned>(d)});
    }
}

std::string Loan::toString() const {
    string paymentsString;
    for (const Payment &payment : payments) {
        paymentsString += payment.toString() + "\n";
    }
    
    return "Loan: " + this->name + "\n"
        + "Principle: " + to_string(this->principle) + "\n"
        + "Interest Rate: " + to_string(this->interest_rate) + "\n"
        + "Date Taken Out: " + date_to_string(this->date) + "\n"
        + "Current Amount Owed: " + to_string(this->get_current_amount()) + "\n"
        + "Payments: \n" + paymentsString;
}

void to_json(json& j, const Loan& loan) {
    j = json{
        {"name", loan.get_name()},
        {"principle", loan.get_principle()},
        {"interest_rate", loan.get_interest_rate()},
        {"date", date_to_string(loan.get_date())},
        {"payments", loan.get_payments()},
    };
}

void from_json(const json& j, Loan& loan) {
    const string name = j.at("name").get<string>();
    const double principle = j.at("principle").get<double>();
    const double interest_rate = j.at("interest_rate").get<double>();
    const string date_string = j.at("date").get<string>();
    const vector<Payment> payments = j.at("payments");
    loan = Loan(name, principle, interest_rate, string_to_date(date_string), payments);
}








