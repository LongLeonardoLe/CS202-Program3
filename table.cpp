/*****************************************************************************
 *
 * Name: Long Le
 * PSU ID: 923532743
 *
 * File: table.h
 * Purpose: implemetation for 2 classes: node, binaryTree
 *
 * **************************************************************************/

#include "table.h"

/************************* class node **********************/

//default constructor
node::node()
{
    this->height = 1;
    this->left = NULL;
    this->right = NULL;
}

//copy constructor
node::node(const node& src)
    : linkedList(src)
{
    this->height = src.height;
    this->left = NULL;
    this->right = NULL;
}

node::node(const linkedList& src)
    : linkedList(src)
{
    this->height = 1;
    this->left = NULL;
    this->right = NULL;
}

//destructor
node::~node()
{
    this->left = NULL;
    this->right = NULL;
}

//go left and right functions
node*& node::goLeft()
{
    return this->left;
}

node*& node::goRight()
{
    return this->right;
}

//connect to the left and the right
void node::connectLeft(node*& n)
{
    this->left = n;
}

void node::connectRight(node*& n)
{
    this->right = n;
}

//operator > <
/*bool node::operator>(const node& p) const
{
    return linkedList::operator>(p);
}

bool node::operator<(const node& p) const
{
    return linkedList::operator<(p);
}
*/
//calculate the height
void node::calHeight()
{
    //both left and right are null
    if (!this->left && !this->right)
    {
        this->height = 1;
        return;
    }

    //if left or right is null
    if (!this->left && this->right)
    {
        this->height = this->right->height+1;
        return;
    }
    else if (this->left && !this->right)
    {
        this->height = this->left->height+1;
        return;
    }

    //if both left and right are not null
    if (this->left->height > this->right->height)
    {
        this->height = this->left->height+1;
        return;
    }
    else this->height = this->right->height+1;
}

//operator +=
node& node::operator+=(person& p)
{
    linkedList::operator+=(p);
    return *this;
}

//rotate functions
node* node::rotateLeft()
{
    node* tmp = this->right->left;
    node* tmp1 = this->right;
    tmp1->left = this;
    this->right = tmp;
    this->calHeight();
    return tmp1;
}

node* node::rotateRight()
{
    node* tmp = this->left->right;
    node* tmp1 = this->left;
    tmp1->right = this;
    this->left = tmp;
    this->calHeight();
    return tmp1;
}

//calculate the balance factor
int node::balanceFactor()
{
    if (this->left && this->right)
        return this->left->height - this->right->height;
    else
    {
        if (!this->left)
            return 0 - this->right->height;
        else if (!this->right)
            return this->left->height;
        return 0;
    }
}

/************************* class binaryTree ***************************/

//default constructor
binaryTree::binaryTree()
{
    this->root = NULL;
}

//copy constructor
binaryTree::binaryTree(const binaryTree& src)
{
    this->copyTree(this->root, src.root);
}

//destructor
binaryTree::~binaryTree()
{
    this->deleteAll(this->root);
    this->root = NULL;
}

//copy tree
void binaryTree::copyTree(node*& root, node* src)
{
    if (!src)
        return;

    root = new node(*src);
    this->copyTree(root->goLeft(), src->goRight());
    this->copyTree(root->goRight(), src->goRight());
}

//delete all nodes
void binaryTree::deleteAll(node*& root)
{
    if (!root)
        return;

    this->deleteAll(root->goLeft());
    this->deleteAll(root->goRight());
    delete root;
}

//display from the left to the right
void binaryTree::displayLNR(std::ostream& out, node* root) const
{
    if (!root)
        return;

    this->displayLNR(out, root->goLeft());
    out << *root;
    this->displayLNR(out, root->goRight());
}

//operator <<
std::ostream& operator<<(std::ostream& out, binaryTree& b)
{
    b.displayLNR(out, b.root);
    return out;
}

//add a new person to the tree
void binaryTree::addPerson(node*& root, person& p)
{
    if (!root)
    {
        root = new node();
        *root+=p;
        return;
    }
    int tmp = root->compare(p);
    if (tmp > 0)
        this->addPerson(root->goLeft(), p);
    else if (tmp < 0)
        this->addPerson(root->goRight(), p);
    else 
    {
        *root+=p;
        return;
    }

    root->calHeight();

    if (root->balanceFactor()>1)
    {
        if (root->goLeft()->compare(p)>0)
            root = root->rotateRight();
        else
        {
            root = root->goLeft()->rotateLeft();
            root = root->rotateRight();
        }
    }
    else if (root->balanceFactor()<-1)
    {
        if (root->goRight()->compare(p)<0)
            root = root->rotateLeft();
        else
        {
            root = root->goRight()->rotateRight();
            root = root->rotateLeft();
        }
    }
}

//operator +=
binaryTree& binaryTree::operator+=(person& p)
{
    this->addPerson(this->root, p);
    return *this;
}

//generate the tree from a file
void binaryTree::generate()
{
    std::ifstream fin;
    fin.open("data.txt");
    if (fin.is_open())
    {
        do
        {
            person tmp;
            fin >> tmp;
            *this+=tmp;
            fin.ignore(1000,'\n');
        } while (!fin.eof() && fin);
    }
    fin.close();
}

//search last name
node* binaryTree::searchLastName(node*& root, const char* lastName) const
{
    if (!root)
        return NULL;

    if (*root == lastName)
        return root;
    if (*root < lastName)
        return this->searchLastName(root->goRight(), lastName);
    return this->searchLastName(root->goLeft(), lastName);
}

//search a person
bool binaryTree::search(const char* lastName, const char* firstName)
{
    node* tmp = this->searchLastName(this->root, lastName);
    if (tmp==NULL)
    {
        delete tmp;
        return false;
    }
    if (tmp->searchByFirstName(firstName)==true)
    {
        delete tmp;
        return true;
    }
    return false;
}

