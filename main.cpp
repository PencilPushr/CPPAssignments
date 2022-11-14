#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

#include "Person.h"

namespace numerical_chars {
    inline std::ostream &operator<<(std::ostream &os, char c) {
        return std::is_signed<char>::value ? os << static_cast<int>(c)
                                           : os << static_cast<unsigned int>(c);
    }

    inline std::ostream &operator<<(std::ostream &os, signed char c) {
        return os << static_cast<int>(c);
    }

    inline std::ostream &operator<<(std::ostream &os, unsigned char c) {
        return os << static_cast<unsigned int>(c);
    }
}


void DisplayMenuOptions()
{

    std::cout << "Please select a number for the option of:\n";
    std::cout << "\n";
    std::cout << "1 - Login\n";
    std::cout << "2 - Register\n";
    std::cout << "3 - Exit\n";
    std::cout << "Option: ";
}

/*
int getChoice() {

    int choice = 0;
    while ((std::isdigit(choice) == false) && choice < 4 && choice > 0){
        std::cin.clear();
        std::cin >> choice;
    }
}
 */

/*
void trimString(char (&str)[64]){
    size_t size = strlen(str);
    char * newbuffer = new char[size];
    for (int i = 0; i < size; ++i) {
        newbuffer[i] = str[i];
    }
    //always causes an error
    delete(*str);

    *str = *newbuffer;
}
 */

char * clampedInput(std::istream& istream){

    istream.clear();
    char * temp = new char [64];
    //clamp input to 63, as 64th char needs to be null termination character
    //std::setw() clamps cinput up to x characters
    istream >> std::setw(63) >> temp;

    //null terminate the string
    temp[64] << '\0';
    //trimStrin(temp); doesn't work

    //trim the string
    size_t size = strlen(temp);
    char * newbuffer = new char[size];
    for (int i = 0; i < size; ++i) {
        newbuffer[i] = temp[i];
    }

    delete[] temp;
    temp = newbuffer;

    return temp;

}

bool isValidalpha(char * inputname){
    //make sure name is alpha characters and nothing else
    size_t len = strlen(inputname);
    for (int i = 0; i < len; ++i) {
        if (isalpha(inputname[i])){
            return true;
        }
    }
    return false;
}

bool isValidanumeric(char * inputname){
    //make sure name is alpha characters and nothing else
    size_t len = strlen(inputname);
    for (int i = 0; i < len; ++i) {
        if (isalnum(inputname[i])){
            return true;
        }
    }
    return false;
}

int main() {

    std::fstream my_file;
    my_file.open("people.txt", std::ios::out);
    if (!my_file) {
        std::cout << "File not created!\n";
    }
    else {
        std::cout << "File created successfully!\n";
        my_file.close();
    }

    bool exit = false;

    while(!exit){
        int choice = 0;
        DisplayMenuOptions();
        std::cin >> choice;

        /*
        size_t len = strlen(reinterpret_cast<const char *>(choice));
        if (len > 1 || (std::isdigit(choice) == false)){
            choice = getChoice();
        }
         */

        switch (choice) {
            case 1: {
                char *inputname = clampedInput(std::cin);
                char *inputpasswd = clampedInput(std::cin);

                //authenticate users exists by reading file
                char* Buf;
                std::ifstream file{ "people.txt" };
                file.seekg(0, std::ios::end);
                int size = file.tellg();
                Buf = new char[size];
                file.seekg(0, std::ios::beg);
                file.read(&Buf[0], size);

                //if matching entry -> user is authenticated
                Person* tempPerson = new Person(Buf[0], Buf[1]...etc.);
                //NOT FINISHED

                //PrintUserInfo(tempPerson);
                std::cout << "Welcome " << tempPerson->getName();
                std::cout << "Your age is " << tempPerson->getAge();
                std::cout << "You were born in " << tempPerson->getBirthPlace();
                std::cout << "You have " << tempPerson->getNumFriends();
                std::cout << "You friends are"



                break;
            }
            case 2: {

                char *inputname = clampedInput(std::cin);
                if (!(isValidalpha(inputname))) {
                    std::cout << "not a valid name\n";
                }

                char *inputpasswd = clampedInput(std::cin);
                if (!(isValidanumeric(inputpasswd))) {
                    std::cout << "not a valid passwd\n";
                }

                uint16_t inputAge;
                std::cin >> std::setw(3) >> inputAge;
                if (inputAge > 255){
                    std::cout << "Cannot have an age greater than 255\n"
                    << "Age has been clamped at 255\n";
                    inputAge = 255;
                }

                char *inputBirthPlace = clampedInput(std::cin);
                if (!(isValidalpha(inputBirthPlace))){
                    std::cout << "not a valid passwd\n";
                }

                char **inputFriends =


                std::cout << "Adding Details\n";

                //freeing variables
                delete inputname;
                delete inputpasswd;
                delete inputBirthPlace;
                delete[] input

                break;
            }
            case 3:
                std::cout << "Exiting program\n";
                exit = true;
                break;

            default:
                std::cout << "Invalid character or error encountered\n";
                std::cout << "Please enter: 1, 2 or 3.\n";
                std::cout << "\n";
                //flush IO flags and clear the bits from std::cin
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                break;
        }
    }

    return 0;
}
