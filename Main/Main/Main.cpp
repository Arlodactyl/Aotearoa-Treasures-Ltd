// Aotearoa_Treasures_Ltd_Menu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct User
{
protected: // Private Variables
    string username;
    string password;

public: // Public Variables
    string name;
    string surname;
    int age;

    // Cart here...?

    User() // Default constructor to initialize values
    {
        username = " ";
        password = " ";
        name = " ";
        surname = " ";
        age = 0;
    }

    void setUpPassword() // Function to set Username and Passowrd 
    {
        cout << "Enter A Password : ";
        getline(cin, password); // Getting user input for Password
        cout << endl;

        // Error Handling (Password can't be the same as the username)
        while (password == username)
        {
            cout << "\n(Error Message) Please enter a password that doesn't match your Username!\n" << endl;

            cout << "Enter A Password : ";
            getline(cin, password);
            cout << endl;
        }

    }

    void getInformation() // Funciton for getting the users information
    {
        // Getting Name of User
        cout << "Name : ";
        getline(cin, name);
        cout << endl;
        // Getting Surname of User
        cout << "Surname : ";
        getline(cin, surname);
        cout << endl;
        //Getting Age of User
        cout << "Age : ";

        while (true) // auto while loop
        {
            cin >> age; // user input
            cout << endl;

            if (cin.fail() || age < 5 || age > 120) // if statement, checking for invalid input with .fail(), checking if age is less then 5 or greather then 120
            {
                cin.clear(); // clearing the invalid input value 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ingoring the invalid input, which prevents infinite loops   
                cout << "Invlaid input, please enter a valid number : "; // Error Message
            }
            else
            {
                break; // Valid inpit, existing loop
            }
        }

    }

    void setUsername(string& tempUsername) // Function for setting the users username 
    {
        username = tempUsername;
    }

    string getUsername() const // Function for returning a const value of users username 
    {
        return username;
    }

    bool checkPassword(string& tempPassword) // Function for returning a bool value to check if the password is correct or not
    {
        return tempPassword == password;
    }

    void saveToFile(ofstream& file) const // Function for saving the information in the file
    {
        file << username << ',' << password << ',' << name << ',' << surname << ',' << age << endl;
    }

    bool loadFromLine(string& line) // Function for loading users data from a file
    {
        stringstream ss(line); // Stringstream to break the line into parts
        string username, password, name, surname, stringAge; // Temp variables

        getline(ss, username, ','); // Extracting Username
        getline(ss, password, ','); // Extracting Password
        getline(ss, name, ','); // Extracting Name
        getline(ss, surname, ','); // Extracting Surname
        getline(ss, stringAge); // Extracting Age (Still in a string)
        int age = stoi(stringAge); // stoi (String to integer), this function converts a string into a integer

        // Assigning the values to the member variable of the user
        this->username = username;
        this->password = password;
        this->name = name;
        this->surname = surname;
        this->age = age;

        return true;
    }

};

void saveAllUsers(const vector<User>& users);
void loadAllUsers(vector<User>& users);

bool usernameExists(const vector<User>& users, const string& username);

void mainMenu(vector<User>& users); // Main Menu Function
void adminMenu(vector<User>& users); // Admin Menu
void userLogin(vector<User>& users); // User Login Menu

// Added helper functions for strong borders
void printStrongBorder(const string& title)
{
    int width = title.length() + 10;
    cout << string(width, '#') << endl;
    cout << "##  " << title << string(width - 6 - title.length(), ' ') << "##" << endl;
    cout << string(width, '#') << endl;
}

void printMenuOption(const string& option)
{
    cout << "|| " << option << endl;
}

int main()
{
    vector <User> users; // Storing User inside a vector
    loadAllUsers(users); // Function for loading all users from the file

    mainMenu(users); // Main Menu Function

    saveAllUsers(users); // Function for saving all users to the file
    return 0;
}

void saveAllUsers(const vector<User>& users) // Function for saving all users inside the file
{
    ofstream file("Users.txt"); // Output File 
    if (file.is_open()) // Checking if the file has opened
    {
        for (const auto& user : users) // Using a auto for loop to save all the data in the user to the file
        {
            user.saveToFile(file);
        }

        file.close(); // Closing the file
    }
}

void loadAllUsers(vector<User>& users) // Funciton for loading all the users information from the file
{
    ifstream file("Users.txt"); // Input File 
    {
        if (file.is_open()) // Checking if the file has opened
        {
            string line; // Using a string variales to gather the information
            while (getline(file, line))
            {
                User user;
                if (user.loadFromLine(line)) // Checking if sussceful in getting the information
                {
                    users.push_back(user); // Pushing back the users information into the vector
                }
            }
        }
        file.close(); // Closing the file
    }
}

void mainMenu(vector<User>& users)
{
    char option;
    printStrongBorder("Aotearoa Inventory System");

    do
    {
        printMenuOption("1. Store");
        printMenuOption("2. Login");
        printMenuOption("3. Exit");
        cout << string(30, '=') << endl;

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
            userLogin(users);
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
            adminMenu(users);
            break;
        }
        default:
            system("cls");
            cout << "\n(Error Message) Please enter the correct input\n" << endl;
        }
    } while (option != '3');

}

void adminMenu(vector<User>& users)
{
    string userAdmin = "ADMIN"; // Default varables
    string passAdmin = "PASSWORD"; // Default varables

    char goBack;
    string username;
    string password;

    printStrongBorder("Admin Login");

    do // Do While loop
    {
        printMenuOption("1. Login");
        printMenuOption("2. Back");
        cout << string(30, '=') << endl;

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

bool usernameExists(const vector<User>& users, const string& username) // Function for checking if username exists
{
    for (const auto& user : users) // Auto for loop for users
    {
        if (user.getUsername() == username) // Checking if the temperary username is the same with any other username in the system
        {
            return true; // Returning true if its found one
        }
    }

    return false; // Returning false if not
}

void userLogin(vector<User>& users) // User Login Menu
{
    char option;

    do // Do while loop 
    {
        printStrongBorder("User Login");

        printMenuOption("1. Sign In");
        printMenuOption("2. Register An Account");
        printMenuOption("3. Back");
        cout << string(35, '=') << endl;

        cout << "Option : ";
        cin >> option; // Getting user's input
        cout << endl;

        switch (option)
        {
        case '1': // Sign in Case
        {
            string tempUsername, tempPassword;
            bool userFound = false;

            cin.ignore(); // Ignoring cin input
            cout << "Username : ";
            getline(cin, tempUsername); // Getting users input for username
            cout << endl;

            cout << "Password : ";
            getline(cin, tempPassword); // Getting users input for password
            cout << endl;

            for (User& user : users) // Auto for loop to read all users data
            {
                if (user.getUsername() == tempUsername && user.checkPassword(tempPassword)) // Checking if users has entered the same values for a user
                {
                    cout << "Welcome back, " << user.name << endl; // Giving the user a welcome back message if loged in
                    userFound = true; // User found is set to true

                    // Taking them to the store......
                    break; // Breaking loop
                }
            }

            if (!userFound) // If User hasn't been found then give error message
            {
                cout << "\n(Error Message) Invalid username or password!\n" << endl; // Error message
            }

            break; // Breaking switch case

        }
        case '2': // Sign up case
        {
            cin.ignore(); // Ignoring cin input

            User newUser; // User class
            string username; // Temperary username variable
            bool exists;

            do // Do while loop
            {
                cout << "Enter A Username : ";
                getline(cin, username); // Geting user input for Username
                cout << endl;

                exists = usernameExists(users, username); // Checking for the same usernames, if so

                if (exists)
                {
                    cout << "\n(Error Message) That username is already taken. Please choose another!\n" << endl; // Error message
                }
                else
                {
                    break; // Breaking out of while loop
                }
            } while (true); // True by default until broken or false

            newUser.setUsername(username); // Setting the usernames into the users member value
            newUser.setUpPassword(); // Setting the users password, which is stored in the users member value
            newUser.getInformation(); // Getting the users information and storing into the users member values
            users.push_back(newUser); // Pushing back into the vector switch for storing

            cout << "Registation Completed!" << endl; // Displaying a message to let the user know they created an account
            break; // Breaking out of switch case
        }
        case '3': // Case 3 - Go back
        {
            // Going back to main menu
            break; // Breaking out of case
        }
        default:

            system("cls"); // Clearing screen for clear display
            cout << "\n(Error Message) Please enter the correct input\n" << endl; // Givng user an error message when wrong
        }
    } while (option != '3'); // Keep loop while option doesn't equal 3 (3. Go back)

}
