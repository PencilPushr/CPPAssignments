//
// Created by averagejoe on 10/31/22.
//
#pragma warning(disable : 4996)

#include "Person.h"

Person::Person(std::string& name, unsigned char age, std::string& birthplace, std::string& password) {
    this->p_name = name.c_str();
    this->age = age;
    this->p_place_of_birth = birthplace.c_str();
    this->p_password = password.c_str();
}

Person::Person(const Person& other) {
    p_name = other.p_name;
    age = other.age;
    p_place_of_birth = other.p_place_of_birth;
    p_password = other.p_password;
    p_friends = other.p_friends;
}

Person::~Person(){
    for (size_t i = 0; i < ROWS; i++)
    {
        delete(this->p_friends[i]);
    }
    delete(this->p_friends);
    delete((char*)this->p_name);
    delete((char*)this->p_place_of_birth);
    delete((char*)this->p_password);
}

const char *Person::getName() {
    return p_name;
}

unsigned char Person::getAge() const {
    return age;
}

const char *Person::getBirthPlace() {
    return p_place_of_birth;
}

uint8_t Person::getNumFriends() {
    return numOfFriends;
}

void Person::InitialiseFriends() {


    //after talking with Dr. Barros, simply using the keyword "new" would work just as well. No need for calloc.
    this->p_friends = new char*[ROWS];
    for(int i = 0; i < ROWS; i++)
        p_friends[i] = (char *)malloc(COLS * sizeof(char));

}

void Person::makeAFriend(std::string(&newFriend)[10]) {

    if (numOfFriends == 0){
        Person::InitialiseFriends();
    }

    strcpy(this->p_friends[numOfFriends + 1], newFriend->c_str());
    this->numOfFriends++;

    //if we have a number of friends greater/equal to the possible storage of friends
    //resize the array.
    if (this->numOfFriends >= COLS) {
        //allocating a buffer (double the size) for friends to be incorporated into
        char** newBuffer = new char* [this->numOfFriends * 2];
        for (int i = 0; i < this->numOfFriends; i++) {
            newBuffer[i] = p_friends[i]; }
        //free the memory it occupies
        delete[] p_friends;
        //allocate new buffer
        this->p_friends = newBuffer;
    }

}

char **Person::getFriends() {
    return this->p_friends;
}
