#include "table.h"

int main()
{
    std::cout << "--------------------------------";
    std::cout << " Program 3 ";
    std::cout << "--------------------------------\n";
    std::cout << "Do you want to input manually or from the existed file? (M/F): ";
    char response;
    std::cin >> response;
    std::cin.ignore(1000,'\n');

    binaryTree b;

    while (toupper(response)!='F' && toupper(response)!='M')
    {
        std::cout << "Invalid input. Input again (M/F): ";
        std::cin >> response;
        std::cin.ignore(1000,'\n');
    }

    if (toupper(response)=='F')
        b.generate();
    else
    {
        do
        {
            std::cout << "Input information in this order: last name, first name, phone number, email, address:\n";
            person tmp;
            std::cin >> tmp;
            b+=tmp;
            std::cout << "\nDo you want to add another person? (Y/N): ";
            std::cin >> response;
            std::cin.ignore(1000,'\n');
        } while (toupper(response)=='Y');
    }
    
    std::cout << "The data is ready. Menu:\n1.Search\n2.Display all data\n0.Exit\n";
    int choice;

    do
    {
        std::cout << "\nYour option: ";
        std::cin >> choice;
        while (choice!=1 && choice!=0 && choice!=2)
        {
            std::cout << "Invalid option. Your option: ";
            std::cin >> choice;
        }
        switch (choice)
        {
            case 1:
                {
                    std::cin.ignore(1000,'\n');
                    std::cout << "\nLast name: ";
                    char* lastName = new char[256];
                    char* firstName = new char[256];
                    std::cin.getline(lastName, 256, '\n');
                    std::cout << "First name: ";
                    std::cin.getline(firstName, 256, '\n');
                    if (b.search(lastName, firstName)==false)
                        std::cout << "No matched result.\n";
                    delete lastName;
                    delete firstName;
                    break;
                }
            case 2:
                {
                    std::cout << "Information of all people in the table:\n\n" << b;
                    break;
                }
             default:
                 break;
        }
    } while (choice!=0);

    return 0;
}

