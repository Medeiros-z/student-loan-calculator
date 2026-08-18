#ifndef STUDENT_LOAN_CALCULATOR_LOAN_H
#define STUDENT_LOAN_CALCULATOR_LOAN_H

#include <chrono>
#include <vector>
#include <Payment.h>
#include <nlohmann/json.hpp>

class Loan {
public:

    Loan() = default;
    Loan(std::string name, double principle, double interest_rate, std::chrono::year_month_day date,
        std::vector<Payment> payments);

    std::string get_name() const;
    double get_principle() const;
    double get_interest_rate() const;
    std::chrono::year_month_day get_date() const;
    std::vector<Payment> get_payments() const;
    void make_payment(Payment payment);
    double get_current_amount() const;
    std::string toString() const;

private:
    std::string name;
    double principle;
    double interest_rate;
    std::chrono::year_month_day date{};
    std::vector<Payment> payments;

    // JSON library functions
    friend void to_json(nlohmann::json& j, const Loan& loan);
    friend void from_json(const nlohmann::json& j, Loan& loan);

};


#endif //STUDENT_LOAN_CALCULATOR_LOAN_H
