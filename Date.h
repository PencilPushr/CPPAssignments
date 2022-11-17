// header file for C++ assignment 1 exercise 2 2022

/* * *
 * you must not change any of the existing code in this file
 * you may if you wish add extra data members to the class, such as an array
 * holding the numbers of days in each month and/or an array holding the
 * names of the months ("January" etc)
 * 
 * you also may not add any extra member functions or friends
 * 
 * you may change, or add to, the comments below
 * NOTE: the comments there are NOT expected to be the final code comments
 *       they are only extra instructions for you
 * 
 * * */

#ifndef _DATE_H_

#define _DATE_H_

#include <iostream>
#include <string>

class Date
{ private:
    unsigned int d; // 1-31
    unsigned int m; // 1-12
    unsigned int y; // 1000-9999 (must be a 4-digit year)

  public:
    Date();  // initialise members to valid default values, e.g. 1/1/2019
    Date(unsigned int day, unsigned int month, unsigned int year);
        // initialise using arguments
        // use default valid values and output a warning message
        //    if any argument is out of range
        //    or if day is 29, 30 or 31 and month has fewer days

    bool operator<(const Date& other) const;
        // return true if this date is before other, false otherwise
    bool operator>(const Date& other) const;
        // return true if this date is after other, false otherwise

        //it has been marked as explicit, because clion keeps trying to make this into std::basic_string();
    explicit operator std::string() const;
        // return a string of the form "Day Month Year"

        // you can generate a string containing digits using to_string(n)
        //    where n is a variable (or expression) of type int

        // you can use + and += to concatenate strings as in Python

        // expressions such as s + x and s += x are valid 
        //    when s is a string and x is a char or a C-string
        //    (but not when x is a number)

  friend std::ostream& operator<<(std::ostream& o, const Date& d);
      // output date in format dd/mm/yyyy, e.g. 02/11/2019
};


#endif