#include "Payment.h"
#include <chrono>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;
using std::chrono::year_month_day;

Payment::Payment(float amount, year_month_day date) {
    this->amount = amount;
    this->date = date;
}

float Payment::get_amount() const {
    return this->amount;
}

year_month_day Payment::get_date() const {
    return this->date;
}

// Helper functions for JSON operations
namespace {

    using namespace std::chrono;

    string date_to_string(const year_month_day& date)  {
        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(4) << (int)date.year() << "-"
            << std::setw(2) << (unsigned)date.month() << "-"
            << std::setw(2) << (unsigned)date.day();
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

std::string Payment::toString() const {
    return to_string(this->amount) + date_to_string(this->date);
}

void to_json(json& j, const Payment& p) {
    j = json{
        {"amount", p.get_amount()},
        {"date", date_to_string(p.get_date())}
    };
}

void from_json(const json& j, Payment& p) {
    const float amount = j.at("amount").get<float>();
    const string date_string = j.at("date").get<string>();
    p = Payment(amount, string_to_date(date_string));

}
