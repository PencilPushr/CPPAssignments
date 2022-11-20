#include "Date.h"

extern void printAgeDif(Date& d1, Date& d2){

    //hack
    struct dateptr {
        unsigned int dd;
        unsigned int mm;
        unsigned int yy;
    };

    //creating accessible struct ptrs to the information pointed at in the Date class
    auto *d1ptr = (dateptr *)(&d1);
    auto *d2ptr = (dateptr *)(&d2);


    //getting the "private" variables
    //comparing the biggest of the dates and getting the difference
    unsigned int day = std::max(d1ptr->dd, d2ptr->dd) - std::min(d1ptr->dd, d2ptr->dd);
    unsigned int month = std::max(d1ptr->mm, d2ptr->mm) - std::min(d1ptr->mm, d2ptr->mm);
    unsigned int year = std::max(d1ptr->yy, d2ptr->yy) - std::min(d1ptr->yy, d2ptr->yy);

    //if they are the same age
    if (day == 0 && month == 0 && year == 0){
        std::cout << d1.name << "is the same age as" << d2.name;
    }

    Date older = d1 > d2 ? d1 : d2;
    Date younger = d1 < d2 ? d1 : d2;

    std::cout   << younger.name << " is "
                << year << " year(s) "
                << month << " month(s), and "
                << day << " days younger than " << older.getName();
}

Date::Date() {

    //Y2K
    this->d = 1;
    this->m = 1;
    this->y = 2000;


}

Date::Date(unsigned int day, unsigned int month, unsigned int year) {

    if (year < 1000){
        year = 1000;
        std::cout << "Year can't be less than 1000";
    }
    if (year > 9999){
        year = 9999;
        std::cout << "Year can't be more than 9999";
    }

    //leap year every 4 years, if there is a remainder it is not a leap year
    bool isleapYear = (year % 4 == 0);

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30){
            day = 30;
            std::cout << "These months have only 30 days\n";
        }
    }
    else if (month == 2) {
        if (isleapYear){
            if(day > 29) {
                day = 29;
                std::cout << "Its a leap year, only 29 days in February\n";
            }
        } else {
            if (day > 28) {
                day = 28;
                std::cout << "It's regular year, only 28 days in February\n";
            }
        }
    }
    else {
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

    return (d + (m * 30) + (y*365)) <
        (other.d + (other.m * 30) + (other.y * 30));
}

bool Date::operator>(const Date &other) const {

    return (d + (m * 30) + (y*365)) >
        (other.d + (other.m * 30) + (other.y * 30));
}


//“Day Month Year”, always using a “int string int” format
Date::operator std::string() const {

    std::string s;
    std::string day;

    bool leadZerosD = false;

    if (this->d < 10){
        leadZerosD = true;
    }

    //int day, string month, int year
    s = std::to_string(this->d)  + "/" + monthStr(this->m) + "/" + std::to_string(this-> y);

    if (leadZerosD){
        s.insert(0, "0");
    }

    return s;
}

std::ostream &operator<<(std::ostream &o, const Date &d) {
    return o;
}

/*
 * ---------------------------------------------------------------------------------------------------------------------
 */

std::string Date::getName() const{
    return this->name;
}

void Date::setName(std::string& i_name){
    this->name = i_name;
};

std::string Date::monthStr(unsigned int month) const {
    return this->months[month-1];
}

