/*****************************************************************************
 *
 * Name: Long Le
 * PSU ID: 923532743
 *
 * File: table.h
 * Purpose: header file for 2 classes: node, binaryTree
 *
 * **************************************************************************/

#ifndef TABLE_H
#define TABLE_H
#include "person.h"

//the class node is used for the BST later. It inherits from the class
//linkedList. Besides, it has 2 pointers to left and the right.
class node : public linkedList
{
    public:
        node();
        node(const node& src);
        node(const linkedList& src);
        ~node();
        node*& goLeft();
        node*& goRight();
        void connectLeft(node*& n);
        void connectRight(node*& n);
        void calHeight();
        int balanceFactor();
        node* rotateLeft();
        node* rotateRight();

        //operators
        //bool operator>(const char* lastName) const;
        //bool operator<(const char* lastName) const;
        node& operator=(const node& n);
        node& operator+=(person& p);

    private:
        int height;
        node *left, *right;
};

//the class binaryTree is also an AVL tree. The tree will be automatically
//balanced when a new person added. 
class binaryTree
{
    public:
        binaryTree();
        binaryTree(const binaryTree& src);
        ~binaryTree();
        friend std::ostream& operator<<(std::ostream& out, binaryTree& b);
        void generate();
        binaryTree& operator+=(person& p);
        bool search(const char* lastName, const char* firstName);

    private:
        node* root;

        node* searchLastName(node*& root, const char* lastName) const;
        void addPerson(node*& root, person& p);
        void copyTree(node*& root, node* src);
        void deleteAll(node*& root);
        void displayLNR(std::ostream& out, node* root) const;
};

#endif

