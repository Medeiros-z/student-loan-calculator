#ifndef STUDENT_LOAN_CALCULATOR_PAYMENT_H
#define STUDENT_LOAN_CALCULATOR_PAYMENT_H

#include <chrono>
#include <nlohmann/json.hpp>

class Payment {
public:
    Payment(float amount, std::chrono::year_month_day date);

    float get_amount() const;
    std::chrono::year_month_day get_date() const;

private:
    float amount;
    std::chrono::year_month_day date;

    // JSON library functions
    friend void to_json(nlohmann::json& j, const Payment& p);
    friend void from_json(const nlohmann::json& j, Payment& p);
};


#endif //STUDENT_LOAN_CALCULATOR_PAYMENT_H
