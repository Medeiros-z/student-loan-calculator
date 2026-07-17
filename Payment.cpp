#include "Payment.h"
#include <chrono>

using namespace std;


Payment::Payment(float amount, chrono::year_month_day date) {
    this->amount = amount;
    this->date = date;
}

float Payment::get_amount() const {
    return this->amount;
}

chrono::year_month_day Payment::get_date() const {
    return this->date;
}
