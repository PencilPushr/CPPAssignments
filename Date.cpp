#include <Date.h>

Date::Date() {

    //Y2K
    this->d = 1;
    this->m = 1;
    this->y = 2000;

}


//could just use <chrono> or<ctime> library, but I thought it would be fun to answer it this way
Date::Date(unsigned int day, unsigned int month, unsigned int year) {

    //leap year every 4 years, if there is a remainder it is not a leap year
    bool isleapYear = (year % 4 == 0);

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30){
            day = 30;
            std::cout << "These months have only 30 days\n";
        }
    } else if (month == 2) {
        if (isleapYear){
            if(day > 29) day = 29; std::cout << "Its a leap year, only 29 days in February\n";
        } else {
            if (day > 28) day = 28; std::cout << "It's regular year, only 28 days in February\n";
        }
    } else {
        if (day > 31){
            day = 31;
            std::cout << "Only 31 days in this month\n";
        }
    }


    this->d = day;
    this->m = month;
    this->y = year;



}

bool Date::operator<(const Date &other) const {
    return false;
}

bool Date::operator>(const Date &other) const {
    return false;
}

Date::operator std::string() const {
    return std::string();
}

std::ostream &operator<<(std::ostream &o, const Date &d) {
    //return <#initializer#>;
}