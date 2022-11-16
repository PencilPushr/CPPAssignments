#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <unordered_map>

#include "Person.h"

namespace numerical_chars {
    inline std::ostream &operator<<(std::ostream &os, char c) {
        return std::is_signed<char>::value ? os << static_cast<int>(c) : os << static_cast<unsigned int>(c);
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

Person AuthenticateUser(char * name, char * password){
    //authenticate users exists by reading file
    //just realised doing this will make our program huge which is what we don't want
    /*
    char* Buf;
    std::ifstream file{ "people.txt" };
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    Buf = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(&Buf[0], size);
     */

    //preprocess
    /*
    int j = 0, i;
    for(i = 0; i < size; i++) {
        while(j > 0 && needle[k] != needle[i]){
            j = 0;
        }
        if(needle[k] == needle[i]){
            pi[i] = ++j;
        }
    }
    //begin matching
    for(i = 0; i < haystack.size(); i++) {
        while(k > 0 && haystack[i] != needle[k]) k = pi[k - 1];
        if(haystack[i] == needle[k]) k++;
        if(k == needle.size()) return i - needle.size() + 1;
    }
    return std::getline(Buf[i - strlen(name) +1]);
    */

    //open file to begin reading
    std::fstream file;
    file.open("people.txt", std::fstream::in);
    char input;
    char * pattern;

    size_t nameSize = strlen(name);
    pattern = new char[nameSize];
    int j = 0, i;

    //preprocess pattern using KMP algorithm, we look for the longest
    for (i = 0; i < nameSize; ++i) {
        //iterate through our pattern
        while (j > 0 && name[j] != name[i]){
            j = 0;
        }
        if (name[j] == name[i]){
            pattern[i] = ++j;
        }
    }

    while (file >> input){
        if (input == name[0]){

        }

    }
    return (Person) nullptr;
}

char * clampedInput(std::istream& istream, int arraySize){

    istream.clear();
    char * temp = new char [arraySize];
    //clamp input to 31, as 32th char needs to be null termination character
    //std::setw() clamps cinput up to x characters
    istream >> std::setw(arraySize - 1) >> temp;

    //null terminate the string
    temp[arraySize] = '\0';

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

    if (inputname[0] == '\0') return false;

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

    if (inputname[0] == '\0') return false;

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

        switch (choice) {
            case 1: {
                char *inputname = clampedInput(std::cin, 64);
                char *inputpasswd = clampedInput(std::cin, 64);

                if (inputname[0] == '\0' || inputpasswd[0] == '\0'){
                    std::cout << "can't have a null name or password\n";
                    break;
                }

                Person *tempPerson = new Person(AuthenticateUser(inputname, inputpasswd));

                //PrintUserInfo(tempPerson);
                std::cout << "Welcome " << tempPerson->getName() << std::endl;
                std::cout << "Your age is " << tempPerson->getAge() << std::endl;
                std::cout << "You were born in " << tempPerson->getBirthPlace() << std::endl;
                std::cout << "You have " << tempPerson->getNumFriends() << std::endl;
                std::cout << "You friends are: \n";



                for (int i = 0; i < tempPerson->getNumFriends(); ++i) {
                    for (int j = 0; j != '\0' ; ++j) {
                        std::cout << " - "
                        << tempPerson->getFriends()[i][j];
                    }
                }




                break;
            }
            case 2: {

                char *inputname = clampedInput(std::cin, 64);
                if (!(isValidalpha(inputname))) {
                    std::cout << "not a valid name\n";
                }

                char *inputpasswd = clampedInput(std::cin, 64);
                if (!(isValidanumeric(inputpasswd))) {
                    std::cout << "not a valid passwd\n";
                }

                uint16_t inputAge;
                std::cin >> std::setw(3) >> inputAge;
                if (inputAge > 255){
                    std::cout << "Cannot have an age greater than 255\n"
                    << "Age has been clamped at 255\n";
                    inputAge = 255; //how has anyone lived this long??
                }

                char *inputBirthPlace = clampedInput(std::cin, 64);
                if (!(isValidalpha(inputBirthPlace))){
                    std::cout << "not a valid passwd\n";
                }

                uint16_t numOfFriends;
                std::cout << "How many friends, please enter a maximum number of 99:";
                std::cin >> std::setw(2) >> numOfFriends;

                //makeFriends
                char **inputFriends = new char*[numOfFriends];
                for (int i = 0; i < numOfFriends; ++i) {
                    inputFriends[i] = new char[32];
                }

                for(int i = 0; i < numOfFriends; ++i){
                    std::cout << "Enter a name less than 31 characters:";
                    inputFriends[i] = clampedInput(std::cin, 32);
                }




                my_file.open("people.txt", std::ios::app);
                if (my_file.fail()){
                    std::cout << "Could not find or open file\n";
                    std::cout << "Sending back to Menu option list";
                    delete inputname;
                    delete inputpasswd;
                    delete inputBirthPlace;
                    for (int i = 0; i < numOfFriends; ++i) {
                        delete[] inputFriends[i];
                    }
                    delete[] inputFriends;
                    break;
                }

                my_file << inputname << ',';
                my_file << inputAge << ',';
                my_file << inputBirthPlace << ',';
                my_file << inputpasswd << ',';
                for (int i = 0; i < numOfFriends; ++i) {
                    my_file << inputFriends[i];

                    //append , between every friend until the end to append a \n char
                    if (i < numOfFriends - 2){
                        my_file << ',';
                    }
                }

                my_file << '\n';

                my_file.close();

                std::cout << "Adding Details\n";

                //freeing variables
                delete inputname;
                delete inputpasswd;
                delete inputBirthPlace;
                for (int i = 0; i < numOfFriends; ++i) {
                    delete[] inputFriends[i];
                }
                delete[] inputFriends;

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
