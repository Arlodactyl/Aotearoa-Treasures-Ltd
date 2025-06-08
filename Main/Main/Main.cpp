// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

void mainMenu(); // Main Menu Function
void adminMenu(); // Admin Menu

int main()
{
    mainMenu();

    return 0;
}

void mainMenu()
{
    char option;
    cout << "\t[Aotearoa Inventory System]\n" << endl;

    do
    {
        cout << "1. Store" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        cout << "Option : ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1': // Case 1 goes to store
        {
            // Store menu;
            cout << "Store Menu..." << endl;
            break;
        }
        case '2': // Case 2 goes to login menu
        {
            // Login Menu;
            cout << "Login Menu..." << endl;
            break;
        }
        case '3': // Case 3 exits program
        {
            // Exit
            cout << "Exiting Program!" << endl;
            break;
        }
        case '&': // Special character to get access to Admin Menu (Supplied in the read me file)
        {
            system("cls");
            // Admin login menu
            adminMenu();
            break;
        }
        default:
            system("cls");
            cout << "\n(Error Message) Please enter the correct input\n" << endl;
        }
    } while (option != '3');

}

void adminMenu()
{
    string userAdmin = "ADMIN"; // Default varables
    string passAdmin = "PASSWORD"; // Default varables

    char goBack;
    string username;
    string password;



    cout << "\t[Admin Login]\n" << endl;

    do // Do While loop
    {
        cout << "1. Login" << endl;
        cout << "2 . Back" << endl;
        cout << "Option : ";

        cin >> goBack; // Getting user input
        cin.ignore(); // ingoring the cin operator
        cout << endl;

        switch (goBack) // Switch Case
        {
        case '1': // Login Menu
        {
            cout << "Username : ";
            getline(cin, username); // Getting user input 

            cout << "Password : ";
            getline(cin, password); // Getting user input

            if (username != userAdmin || password != passAdmin) // Check if user input is Correct or Not
            {
                system("cls"); // clearing screen for clear display
                cout << "\n(Error Message) Username or Password incorrected!\n" << endl;
            }
            else
            {
                cout << "Admin Panel..." << endl;
                // Call Admin Panel...
            }
            break;
        }
        case '2': // Exiting Switch case
        {
            break;
        }
        default:
            system("cls"); // Clearing screen for clear display
            cout << "\n(Error Message) Please enter the correct input\n" << endl; // Givng user an error message when wrong
        }




    } while (goBack != '2'); // if goBack == 2 then close the while loop

}