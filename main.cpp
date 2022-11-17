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

// getline was implemented from the code that is from these two links
//https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
//https://stackoverflow.com/questions/735126/are-there-alternate-implementations-of-gnu-getline-interface/735472#735472

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAA WHAT THE FuCK
ssize_t getline(char **lineptr, size_t *n, FILE *stream) {

    size_t pos;
    int c;

    //if the address of these are null something bad has happened, return a fail bit
    if (lineptr == NULL || stream == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    c = getc(stream);
    if (c == EOF) {
        return -1;
    }

    //assign buffer if line PTR is null
    if (*lineptr == NULL) {

        //minimum length is 128 chars
        *lineptr = (char *)malloc(128);
        if (*lineptr == NULL) {
            return -1;
        }

        //keeping track of size
        *n = 128;
    }

    pos = 0;

    //iterate until we are at the end of the file (!(EOF))
    while(c != EOF) {
        if (pos + 1 >= *n) {
            //e.g. on the first run (128 + (shifting bits of 128 to the right twice yields == 32))
            size_t new_size = *n + (*n >> 2);

            //if the new size is less than 128, set it to 128
            if (new_size < 128) {
                new_size = 128;
            }

            //allocating new memory for buffer
            char *new_ptr = (char *)(realloc(*lineptr, new_size));

            //if memory allocation fails, return with fail bit
            if (new_ptr == NULL) {
                return -1;
            }

            //update with new size and new memory
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

//needed to print uint8_t Age (otherwise we will print the corresponding ascii char value)
namespace numerical_chars {
    inline std::ostream &operator<<(std::ostream &os, char c) {
        return std::is_signed<char>::value ? os << static_cast<int>(c) :
        os << static_cast<unsigned int>(c);
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

char * AuthenticateUser(char * name, char * password, uint32_t * lengthOfLine){

    //std::fstream throws a failued should I try to use the getline function,
    //I need the getline function.

    //EDIT: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
    // there are many implementations

    //I have rewritten this FUNCTION 6 TIMES!!!!!!!!!!!!!!!!

    //https://pbs.twimg.com/media/Ewm24woWYAM8mBH.jpg

    //I hate C
    //https://en.cppreference.com/w/c/io/FILE
    FILE * file;

    file = fopen("people.txt", "r");
    if (file == NULL)
        exit(EXIT_FAILURE);

    char * line = NULL;
    char * lineForPerson = NULL;
    size_t len = 0;
    ssize_t read;


    //fgets breaks very easily as the bufferlength determines the line length.

    //man page: https://linux.die.net/man/3/getline
    //as it turns out things like getline function in C do not work on non-UNIX systems
    while ((read = getline(&line, &len, file)) != -1) {

        int pos = 0; //position in the line

        if (line[0] == name[0]){
            for (size_t i = 0; line[i] != ',' ; ++i) {

                //check if the name is the same
                if (line[i] != name[i]) break;

                pos++;
            }//if we exit this loop, name must be correct
            int passidx = 0;
            for (; line[pos] != '\n'; ++pos) {
                if (line[pos] != password[passidx++]) break;
            }

            //we have found the user that has the right

            lineForPerson = line;
            fclose(file);
            if (line) free(line);
            lengthOfLine = (uint32_t *)(len);
            return lineForPerson;

        } //otherwise move onto the next line
    }

    fclose(file);
    if (line) free(line);
    return lineForPerson;

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
                    free(inputname);
                    free(inputpasswd);
                    std::cout << "can't have a null name or password\n";
                    break;
                }

                uint32_t lengthOfLine = 0;

                //read file into a string that we can break up into Person attributes
                char * UserLine = AuthenticateUser(inputname, inputpasswd, &lengthOfLine);
                if (UserLine == nullptr){
                    free(UserLine);
                    std::cout << "No user exists\n";
                    break;
                }

                size_t friendssize = lengthOfLine >> 1;

                //break up the string into counterparts;
                uint8_t l_age;
                char * birthPlace = new char[63];
                char ** friends = new char*[32];

                for (int i = 0; i < lengthOfLine; ++i) {
                    friends[i] = new char[friendssize];
                }
                friends[friendssize][32] = '\0';

                int idx = 0;
                int idy = 0;
                bool skippedAge = false;

                for (int i = 0; i < lengthOfLine; ++i) {
                    //skip first item which is name to get to age and birth place
                    if (UserLine[i] != ',') ++i;
                    //need to move off the comma and get age
                    ++i;

                    if (UserLine[i] != ','){
                        l_age = UserLine[i];
                    }
                    ++i;

                    //we are now on birthplace
                    if(UserLine[i] != ','){
                        birthPlace[idx++] = UserLine[i];
                    }
                    idx = 0;
                    ++i;

                    //skip password
                    if(UserLine[i] != ','){
                        ++i;
                    }
                    ++i;

                    //now at friends
                    while(UserLine[i] != '\n' || UserLine[i] != '\0'){
                        for (int j = 0; j < 32; ++j) {
                            friends[idx++][j] = UserLine[i];
                            friends[idx][32] = '\0';
                            if (friends[idx][j] == ','){
                                char * buffer = new char[j+1];

                                for (int k = 0; k < j; ++k) {
                                    buffer[k] = friends[idx][k];
                                }

                                delete friends[idx];
                                friends[idx] = buffer;
                                friends[idx][j+1] = '\0';
                            }
                        }
                    }
                }

                Person * tempPerson = new Person(reinterpret_cast<std::string &>(inputname), l_age,
                                                 reinterpret_cast<std::string &>(birthPlace),
                                                 reinterpret_cast<std::string &>(inputpasswd));
                for (int i = 0; i < friendssize; ++i) {
                    tempPerson->makeAFriend(reinterpret_cast<std::string &>(friends[i]));
                }

                //PrintUserInfo(tempPerson);
                std::cout << "\nWelcome " << inputname << std::endl;
                std::cout << "\nYour age is ";
                numerical_chars::operator<<(std::cout, tempPerson->getAge()) << std::endl;
                std::cout << "\nYou were born in " << tempPerson->getBirthPlace() << std::endl;
                std::cout << "\nYou have " << tempPerson->getNumFriends() << std::endl;
                std::cout << "\nYou friends are: \n";

                for (int i = 0; i < tempPerson->getNumFriends(); ++i) {
                    char * friendToPrint = new char[63];
                    for (int j = 0; tempPerson->getFriends()[i][j] != '\0' ; ++j) {
                        std::cout << " - " << tempPerson->getFriends()[i][j];
                    }
                }

                free(tempPerson);

                break;
            }
            case 2: {

                std::cout << "Enter Name (Max 31 char):";
                char *inputname = clampedInput(std::cin, 32);
                if (!(isValidalpha(inputname))) {
                    std::cout << "not a valid name\n";
                }
                std::cout << "\n";

                std::cout << "Enter Password (Max 31 char):";
                char *inputpasswd = clampedInput(std::cin, 32);
                if (!(isValidanumeric(inputpasswd))) {
                    std::cout << "not a valid passwd\n";
                }
                std::cout << "\n";

                std::cout << "Enter age (Max 255)";
                uint16_t inputAge;
                std::cin >> std::setw(3) >> inputAge;
                if (inputAge > 255){
                    std::cout << "Cannot have an age greater than 255\n"
                    << "Age has been clamped at 255\n";
                    inputAge = 255; //how has anyone lived this long??
                }
                std::cout << "\n";

                std::cout << "Enter Birth Place (Max 31 char):";
                char *inputBirthPlace = clampedInput(std::cin, 32);
                if (!(isValidalpha(inputBirthPlace))){
                    std::cout << "not a valid passwd\n";
                }
                std::cout << '\n';

                uint16_t numOfFriends;
                std::cout << "Number of friends to register, please enter at maximum 99:";
                std::cin >> std::setw(2) >> numOfFriends;
                std::cout << '\n';

                //makeFriends
                char **inputFriends = new char*[numOfFriends];
                for (int i = 0; i < numOfFriends; ++i) {
                    inputFriends[i] = new char[32];
                }

                //no need to do this operation if we don't have any friends
                if (numOfFriends != 0){
                    for(int i = 0; i < numOfFriends; ++i){
                        std::cout << "Enter a name less than 31 characters:";
                        inputFriends[i] = clampedInput(std::cin, 32);
                        std::cout << "\n";
                    }
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

                if(numOfFriends != 0) {
                    for (int i = 0; i < numOfFriends; ++i) {
                        my_file << inputFriends[i];

                        //append , between every friend until the end to append a \n char
                        if (i < numOfFriends - 2) {
                            my_file << ',';
                        }
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
