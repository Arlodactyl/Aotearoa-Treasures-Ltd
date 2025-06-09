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
protected:
    string username;
    string password;

public:
    string name;
    string surname;
    int age;

    User()
    {
        username = " ";
        password = " ";
        name = " ";
        surname = " ";
        age = 0;
    }

    void setUpPassword()
    {
        cout << "Enter A Password : ";
        getline(cin, password);
        cout << endl;

        while (password == username)
        {
            cout << "\n(Error Message) Please enter a password that doesn't match your Username!\n" << endl;

            cout << "Enter A Password : ";
            getline(cin, password);
            cout << endl;
        }
    }

    void getInformation()
    {
        cout << "Name : ";
        getline(cin, name);
        cout << endl;

        cout << "Surname : ";
        getline(cin, surname);
        cout << endl;

        cout << "Age : ";

        while (true)
        {
            cin >> age;
            cout << endl;

            if (cin.fail() || age < 5 || age > 120)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please enter a valid number : ";
            }
            else
            {
                break;
            }
        }
    }

    void setUsername(string& tempUsername)
    {
        username = tempUsername;
    }

    string getUsername() const
    {
        return username;
    }

    bool checkPassword(string& tempPassword)
    {
        return tempPassword == password;
    }

    void saveToFile(ofstream& file) const
    {
        file << username << ',' << password << ',' << name << ',' << surname << ',' << age << endl;
    }

    bool loadFromLine(string& line)
    {
        stringstream ss(line);
        string username, password, name, surname, stringAge;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, surname, ',');
        getline(ss, stringAge);
        int age = stoi(stringAge);

        this->username = username;
        this->password = password;
        this->name = name;
        this->surname = surname;
        this->age = age;

        return true;
    }
};

// ─────────────────────────────────────────────
// UI Border Helpers
// ─────────────────────────────────────────────
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

// ─────────────────────────────────────────────
// Function Declarations
// ─────────────────────────────────────────────
void saveAllUsers(const vector<User>& users);
void loadAllUsers(vector<User>& users);
bool usernameExists(const vector<User>& users, const string& username);
void mainMenu(vector<User>& users);
void adminMenu(vector<User>& users);
void userLogin(vector<User>& users);

// ─────────────────────────────────────────────
// Main Function
// ─────────────────────────────────────────────
int main()
{
    vector <User> users;
    loadAllUsers(users);
    mainMenu(users);
    saveAllUsers(users);
    return 0;
}

// ─────────────────────────────────────────────
void saveAllUsers(const vector<User>& users)
{
    ofstream file("Users.txt");
    if (file.is_open())
    {
        for (const auto& user : users)
        {
            user.saveToFile(file);
        }
        file.close();
    }
}

void loadAllUsers(vector<User>& users)
{
    ifstream file("Users.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            User user;
            if (user.loadFromLine(line))
            {
                users.push_back(user);
            }
        }
    }
    file.close();
}

// ─────────────────────────────────────────────
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
        case '1':
            cout << "Store Menu..." << endl;
            break;
        case '2':
            userLogin(users);
            break;
        case '3':
            cout << "Exiting Program!" << endl;
            break;
        case '&':
            system("cls");
            adminMenu(users);
            break;
        default:
            system("cls");
            cout << "\n(Error Message) Please enter the correct input\n" << endl;
        }
    } while (option != '3');
}

// ─────────────────────────────────────────────
void adminMenu(vector<User>& users)
{
    string userAdmin = "ADMIN";
    string passAdmin = "PASSWORD";

    char goBack;
    string username;
    string password;

    printStrongBorder("Admin Login");

    do
    {
        printMenuOption("1. Login");
        printMenuOption("2. Back");
        cout << string(30, '=') << endl;

        cout << "Option : ";
        cin >> goBack;
        cin.ignore();
        cout << endl;

        switch (goBack)
        {
        case '1':
            cout << "Username : ";
            getline(cin, username);

            cout << "Password : ";
            getline(cin, password);

            if (username != userAdmin || password != passAdmin)
            {
                system("cls");
                cout << "\n(Error Message) Username or Password incorrect!\n" << endl;
            }
            else
            {
                cout << "Admin Panel..." << endl;
            }
            break;
        case '2':
            break;
        default:
            system("cls");
            cout << "\n(Error Message) Please enter the correct input\n" << endl;
        }
    } while (goBack != '2');
}

// ─────────────────────────────────────────────
bool usernameExists(const vector<User>& users, const string& username)
{
    for (const auto& user : users)
    {
        if (user.getUsername() == username)
        {
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────
void userLogin(vector<User>& users)
{
    char option;

    do
    {
        printStrongBorder("User Login");

        printMenuOption("1. Sign In");
        printMenuOption("2. Register An Account");
        printMenuOption("3. Back");
        cout << string(35, '=') << endl;

        cout << "Option : ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
        {
            string tempUsername, tempPassword;
            bool userFound = false;

            cin.ignore();
            cout << "Username : ";
            getline(cin, tempUsername);
            cout << endl;

            cout << "Password : ";
            getline(cin, tempPassword);
            cout << endl;

            for (User& user : users)
            {
                if (user.getUsername() == tempUsername && user.checkPassword(tempPassword))
                {
                    cout << "Welcome back, " << user.name << endl;
                    userFound = true;
                    break;
                }
            }

            if (!userFound)
            {
                cout << "\n(Error Message) Invalid username or password!\n" << endl;
            }

            break;
        }
        case '2':
        {
            cin.ignore();
            User newUser;
            string username;
            bool exists;

            do
            {
                cout << "Enter A Username : ";
                getline(cin, username);
                cout << endl;

                exists = usernameExists(users, username);

                if (exists)
                {
                    cout << "\n(Error Message) That username is already taken. Please choose another!\n" << endl;
                }
                else
                {
                    break;
                }
            } while (true);

            newUser.setUsername(username);
            newUser.setUpPassword();
            newUser.getInformation();
            users.push_back(newUser);

            cout << "Registration Completed!" << endl;
            break;
        }
        case '3':
            break;
        default:
            system("cls");
            cout << "\n(Error Message) Please enter the correct input\n" << endl;
        }
    } while (option != '3');
}
