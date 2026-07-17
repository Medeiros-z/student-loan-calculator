#ifndef STUDENT_LOAN_CALCULATOR_LOAN_H
#define STUDENT_LOAN_CALCULATOR_LOAN_H

#include <chrono>
#include <vector>
#include <Payment.h>

class Loan {
public:
    // Constructor & Destructor
    Loan(std::string name, double principle, double interest_rate, std::chrono::year_month_day date);
    ~Loan();

    std::string get_name() const;
    double get_principle() const;
    double get_interest_rate() const;
    std::chrono::year_month_day get_date() const;
    void make_payment(Payment payment);
    double get_current_amount() const;

private:
    std::string name;
    double principle;
    double interest_rate;
    std::chrono::year_month_day date{};
    std::vector<Payment> payments;

};


#endif //STUDENT_LOAN_CALCULATOR_LOAN_H
