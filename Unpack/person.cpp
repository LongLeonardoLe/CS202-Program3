/***************************************************************************
 *
 * Name: Long Le
 * PSU ID: 923532743
 *
 * File: person.cpp
 * Purpose: implementation for 3 classes: person, personNode, linkedList
 *
 * ************************************************************************/

#include "person.h"

/*----------------------- class person ----------------------------*/

//default constructor
person::person()
{
    this->lastName = NULL;
    this->firstName = NULL;
    this->phone = NULL;
    this->email = NULL;
    this->address = NULL;
}

//copy constructor
person::person(const person& src)
{
    this->lastName = new char[strlen(src.lastName)+1];
    strcpy(this->lastName, src.lastName);      
    this->firstName = new char[strlen(src.firstName)+1];
    strcpy(this->firstName, src.firstName);
    this->phone = new char[strlen(src.phone)+1];
    strcpy(this->phone, src.phone);
    this->email = new char[strlen(src.email)+1];
    strcpy(this->email, src.email);
    this->address = new char[strlen(src.address)+1];
    strcpy(this->address, src.address);
}

//destructor
person::~person()
{
    delete this->lastName;
    delete this->firstName;
    delete this->phone;
    delete this->email;
    delete this->address;
}

//assignment operator
person& person::operator=(const person& src)
{
    if (this == &src)
        return *this;

    this->lastName = new char[strlen(src.lastName)+1];
    strcpy(this->lastName, src.lastName);      
    this->firstName = new char[strlen(src.firstName)+1];
    strcpy(this->firstName, src.firstName);
    this->phone = new char[strlen(src.phone)+1];
    strcpy(this->phone, src.phone);
    this->email = new char[strlen(src.email)+1];
    strcpy(this->email, src.email);
    this->address = new char[strlen(src.address)+1];
    strcpy(this->address, src.address);

    return *this;
}

//extraction operator
std::ostream& operator<<(std::ostream& out, const person& p)
{
    out << p.firstName << " " << p.lastName << "\n";
    out << "Phone: " << p.phone << "\n";
    out << "Email: " << p.email << "\n";
    out << "Address: " << p.address << "\n";
    return out;
}

//insertion operator: the inputs have to be in the following order:
//last name, first name, phone, email, address
std::istream& operator>>(std::istream& in, person& p)
{
    p.lastName = new char[256];
    in.getline(p.lastName, 256, '\n');
    p.firstName = new char[256];
    in.getline(p.firstName, 256, '\n');
    p.phone = new char[256];
    in.getline(p.phone, 256, '\n');
    p.email = new char[256];
    in.getline(p.email, 256, '\n');
    p.address = new char[256];
    in.getline(p.address, 256, '\n');
    return in;
}

//compare 2 person
bool person::compareName(const char* lastName, const char* firstName) const
{
    if (strcmp(this->lastName, lastName)==0 && strcmp(this->firstName, firstName)==0)
        return true;
    return false;
}

//compare function first name
//-1 if last names are different
//0 if same last name but smaller first name
//1 if same last name and *this >= p. In this case, b > a
int person::compare(const person& p) const
{
    if (strcmp(this->lastName, p.lastName)!=0)
        return -1;
    if (strcmp(this->firstName, p.firstName)<0)
        return 0;
    return 1;
}

char* person::getLastName() const
{
    return this->lastName;
}

/*----------------------- class personNode ------------------------*/
//default constructor
personNode::personNode()
{
    this->next = NULL;
}

personNode::personNode(const person& src)
    : person(src)
{
    this->next = NULL;
}

//copy constructor
personNode::personNode(const personNode& src)
    : person(src)
{
    this->next = NULL;
}

//destructor
personNode::~personNode()
{
    this->next = NULL;
    delete this->next;
}

//go to the next node
personNode*& personNode::goNext()
{
    return this->next;
}

//connect to another node
void personNode::connectNext(personNode*& n)
{
    this->next = n;
}

//assignment operator
personNode& personNode::operator=(const personNode& n)
{
    this->person::operator=(n);
    this->next = NULL;
    return *this;
}

/*----------------------- class linkedList -------------------------*/
linkedList::linkedList()
{
    this->head = NULL;
    this->lastName = NULL;
}

//copy constructor
linkedList::linkedList(const linkedList& src)
{
    this->copyList(this->head, src.head);
    this->lastName = new char[strlen(src.lastName)+1];
    strcpy(this->lastName, src.lastName);
}

//function to copy
void linkedList::copyList(personNode*& des, personNode* src)
{
    if (!src)
        return;
    des = new personNode(*src);
    this->copyList(des->goNext(), src->goNext());
}

//destructor
linkedList::~linkedList()
{
    this->deleteAll(this->head);
    delete this->lastName;
    this->lastName = NULL;
}

//delete all nodes
void linkedList::deleteAll(personNode*& head)
{
    if (!head)
        return;
    personNode* cur = head;
    head = head->goNext();
    delete cur;
    this->deleteAll(head);
}

//display all nodes
void linkedList::displayAll(std::ostream& out, personNode*& head) const
{
    if (!head)
        return;
    out << *head << std::endl;
    this->displayAll(out,head->goNext());
}

//assignment operator
linkedList& linkedList::operator=(const linkedList& l)
{
    if (this == &l)
        return *this;
    if (head != NULL)
        this->deleteAll(this->head);
    this->copyList(this->head, l.head);
    this->lastName = new char[strlen(l.lastName)+1];
    strcpy(this->lastName, l.lastName);
    return *this;
}

//add a new node
void linkedList::addNode(personNode*& head, personNode*& p)
{
    if (!head->goNext())
    { 
        head->goNext() = new personNode(*p);
        return;
    }

    // if the node is smaller than the next node
    if (p->compare(*head->goNext())==0)
    {
        p->connectNext(head->goNext());
        head->connectNext(p);
        return;
    }
    addNode(head->goNext(), p);
}

//+= operator. use only when the same last name
linkedList& linkedList::operator+=(person& p)
{
    if (!this->head)
    {
        this->head = new personNode(p);
        this->lastName = new char[strlen(p.getLastName())+1];
        strcpy(this->lastName, p.getLastName());
        return *this;
    }

    personNode *n = new personNode(p);
    if (n->compare(*this->head)==0)
    {
        n->connectNext(this->head);
        this->head = n;
        return *this;
    }
    this->addNode(this->head, n);
    return *this;
}

//<< operator
std::ostream& operator<<(std::ostream& out, linkedList& l)
{
    out << "List of people have the last name " << l.lastName << ":\n";
    l.displayAll(out, l.head);
    return out;
}

//operators > <
bool linkedList::operator>(const char*& lastName) const
{
    if (strcmp(this->lastName, lastName)>0)
        return true;
    return false;
}

bool linkedList::operator<(const char*& lastName) const
{
    if (strcmp(this->lastName, lastName)<0)
        return true;
    return false;
}

//operator == !=
bool linkedList::operator==(const char*& lastName) const
{
    if (strcmp(this->lastName, lastName)==0)
        return true;
    return false;
}

bool linkedList::operator!=(const char*& lastName) const
{
    if (strcmp(this->lastName, lastName)!=0)
        return true;
    return false;
}

//compare the last name to another person
//1: this > person
//-1: this < person
//0: this == person
int linkedList::compare(person& p)
{
    if (strcmp(this->lastName, p.getLastName())>0)
        return 1;
    else if (strcmp(this->lastName, p.getLastName())<0)
        return -1;
    else return 0;
}

//search recursive
int linkedList::search(personNode* head, const char* firstName) const
{
    int count = 0;
    if (!head)
        return count;

    if (head->compareName(this->lastName, firstName)==true)
    {
        std::cout << *head;
        count++;
    }
    return this->search(head->goNext(), firstName);
}

//search by first name
bool linkedList::searchByFirstName(const char* firstName) const
{
    if (this->search(this->head, firstName)==0)
        return true;
    return false;
}

