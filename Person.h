//
// Created by averagejoe on 10/31/22.

#ifndef ASSIGNMENTS_PERSON_H
#define ASSIGNMENTS_PERSON_H
//strcpy is a depreciated function but I want to disable the warning it throws
//yes, this is bad practice.
#pragma warning(disable : 4996)
#include <string>
#include <cstring>


/*
 * Person that includes the following private members: name, age, place of
 * birth, password, and friends (in the plural sense).
 * You must think of data types to those variables that take the LEAST amount of space in memory.
 *
 */


//we are looking to use types that use the LEAST amount of space
//therefore char which takes up 1 byte seems most effect.
//apply the malloc() or calloc() methods to dynamically allocate the memory and allow for writing.

class Person {
private:

    //upon further research, a CHAR* in C++ will throw a segmentation fault as we may try to write to read only memory
    // see p_password for why, once allocated pointers can only be realloc()'d.
    // must be assigned const instead.
    const char* p_name;

    //unsigned char as we cannot have someone age of 255+
    //uint8_t is equivelant of an unsigned char
    uint8_t age;

    const char* p_place_of_birth;

    const char* p_password;

    char** p_friends;
    uint8_t ROWS = 32;
    uint8_t COLS = 16;
    uint8_t numOfFriends = 0;  //trying to add to friends without knowing how large the 2d pointer array is, is an impossible task


    

//Using std::string in constructor to ensure null termination for char ptr's/char arrays
//as they are references they will not take up any additional space when reassigned.
public:
    Person(std::string& name, unsigned char age, std::string& birthplace, std::string& password);
    Person(const Person& person);
    ~Person();
    //I am using char arrays as they depreciate into pointers
    const char* getName();
    unsigned char getAge() const;
    const char* getBirthPlace();
    uint8_t getNumFriends();
    void InitialiseFriends();
    void makeAFriend(std::string (&newFriend) [10]);
    char** getFriends();

};


#endif //ASSIGNMENTS_PERSON_H
