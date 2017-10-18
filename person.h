/***************************************************************************
 *
 * Name: Long Le
 * PSU ID: 923532743
 *
 * File: person.h
 * Purpose: header file of 3 classes: person, personNode, linkedList
 *
 * ************************************************************************/

#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>
#include <cstring>

//class person contains all information of a person about his/her name and contact
class person
{
    public:
        person();
        person(const person& src);
        ~person();
        person& operator=(const person& src);
        friend std::ostream& operator<<(std::ostream& out, const person& p);
        friend std::istream& operator>>(std::istream& in, person& p);
        bool compareName(const char*, const char*) const;
        int compare(const person& p) const;
        char* getLastName() const;

    private:
        char *lastName, *firstName, *phone, *email, *address;
};

//class personNode inherits from the person class with a pointer to the next
//node. This class will be used as a node in the linked list 
class personNode : public person
{
    public:
        personNode();
        personNode(const person& src);
        personNode(const personNode& src);
        ~personNode();
        personNode*& goNext();
        void connectNext(personNode*& n);
        personNode& operator=(const personNode& n);

    private:
        personNode *next;
};

//class linkedList has a head pointer of a linked list of people who have
//the same last name and the list is sorted by people's first name
class linkedList
{
    public:
        linkedList();
        linkedList(const linkedList& src);
        ~linkedList();
        linkedList& operator=(const linkedList& l);

        linkedList& operator+=(person& p);
        friend linkedList operator+(const linkedList& l, const person& p);
        friend linkedList operator+(const person& p, const linkedList& l);
        friend std::ostream& operator<<(std::ostream& out, linkedList& l);
        bool operator>(const char*& lastName) const;
        bool operator<(const char*& lastName) const;
        bool operator==(const char*& lastName) const;
        bool operator!=(const char*& lastName) const;
        int compare(person& p);
        bool searchByFirstName(const char* firstName) const;

    private:
        personNode* head;
        char* lastName;

        int search(personNode* head, const char* firstName) const;
        void copyList(personNode*& des, personNode* src);
        void deleteAll(personNode*& head);
        void addNode(personNode*& head, personNode*& p);
        void displayAll(std::ostream& out, personNode*& head) const;
};

#endif

