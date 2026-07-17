#ifndef STUDENT_LOAN_CALCULATOR_PAYMENT_H
#define STUDENT_LOAN_CALCULATOR_PAYMENT_H

#include <Chrono>

class Payment {
public:
    Payment(float amount, std::chrono::year_month_day date);

    float get_amount() const;
    std::chrono::year_month_day get_date() const;

private:
    float amount;
    std::chrono::year_month_day date;
};


#endif //STUDENT_LOAN_CALCULATOR_PAYMENT_H
