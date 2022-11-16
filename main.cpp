#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

//C imports :(
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include "Person.h"

//why we have a typdef of intptr_t ssize_t;
//https://stackoverflow.com/questions/1464174/size-t-vs-uintptr-t
typedef intptr_t ssize_t;

//understanding the getline implementation vv
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/getdelim.html
//https://www.gnu.org/savannah-checkouts/gnu/libc/manual/html_node/Line-Input.html
// code is from here vv
//https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface/735472#735472

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAA WHAT THE FuCK
ssize_t getline(char **lineptr, size_t *n, FILE *stream) {

    size_t pos;
    int c;

    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    if (*lineptr == NULL) {
        *lineptr = (char *)malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }
        *n = 128;
    }

    pos = 0;
    while(c != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n + (*n >> 2);

            //if the line we are reading in is greater than 128 we need to increase the size of our buffer
            if (new_size < 128) {
                new_size = 128;
            }

            //allocating new memory for buffer
            char *new_ptr = (char *)(realloc(*lineptr, new_size));

            //if memory allocation fails, return with fail bit
            if (new_ptr == NULL) {
                return -1;
            }
            *n = new_size;
            *lineptr = new_ptr;
        }

        ((unsigned char *)(*lineptr))[pos ++] = c;

        //'\n' signifies we are at the end of the line
        if (c == '\n') {

            //break and return the current line buffer
            break;
        }
        c = getc(stream);
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

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

    //std::fstream throws a failued should I try to use the getline function,
    //I need the getline function.
    //I have rewritten this program 5 TIMES!!!!!!!!!!!!!!!!

    //https://pbs.twimg.com/media/Ewm24woWYAM8mBH.jpg

    //I hate C
    //https://en.cppreference.com/w/c/io/FILE
    FILE * file;

    file = fopen("/etc/motd", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    //as it turns out things like getline function in C do not work on non-UNIX systems
    //NOTE: fgets breaks very easily as the bufferlength determines the line length.
    while ((read = getline(&line, &len, file)) != -1) {
        read
    }

    fclose(file);
    if (line)
        free(line);
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
