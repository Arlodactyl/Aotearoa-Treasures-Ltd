// Aotearoa_Treasures_Ltd_Menu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept> // For runtime_error
using namespace std;

struct Product // Structure Product to hold individuals products with details
{
public: // Public Variables

    string productName; // Variable for name of product
    double price; // User's won't be getting charged, only cosmetic 
    int quantity; // Variable for quantity available in stock
};

struct Store // Strucutre Store to hold store information
{
public: // Public Variables

    string storeLocation; // Variable for Store Location
    vector<Product> products; // Varible for list of products 

    bool loadProcutsFromFile(const string& filename) // Loads prudocts from a given file into the store's prodcut list
    {
        // Could have a try catch block...
        ifstream file(filename); // Checking if failed to open file
        if (!file.is_open())
        {
            cout << "(Error) Failed to open " << filename << ".txt for reading" << endl;
            return false;
        }

        string line; // Varaible to store each line from the file
        while (getline(file, line)) // Reading line by line
        {
            stringstream ss(line); // Creating a string stream from the line
            string productName, priceStr, quantityStr; // Temporary variables

            if (getline(ss, productName, ',') && getline(ss, priceStr, ',') && getline(ss, quantityStr))
            {
                Product product; // Creating a new Product object
                product.productName = productName; // Assigning product name
                product.price = atof(priceStr.c_str()); // Converting price from string to a double value
                product.quantity = atoi(quantityStr.c_str()); // Converting quantity fro string to a integer

                products.push_back(product); // Adding the product to the store'ss product list
            }
        }

        file.close(); // Closing the file
        return true;
    }

    void displayProducts() const // Function for displaying the store's products list 
    {
        cout << "Products in " + storeLocation << endl;
        for (const auto& product : products) // Looping throguh all products in the list
        {
            cout << product.productName << " | $:" << product.price << " | Stock : " << product.quantity << endl;
        }
    }
};

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

void createStoreFiles();
bool fileExists(const string& filename);
void loadAllStores(vector<Store>& Stores);
void saveAllUsers(const vector<User>& users);
void loadAllUsers(vector<User>& users);

bool usernameExists(const vector<User>& users, const string& username);

void mainMenu(vector<User>& users, vector<Store>& stores); // Main Menu Function
bool userMenu(vector<User>& users, vector<Store>& stores, bool& checkUserLogin);
void adminMenu(vector<User>& users); // Admin Menu - Add store later....
void userLogin(vector<User>& users, bool& checkUserLogin); // User Login Menu

int selectStoreMenu(const vector<Store>& stores);
void dispalyStoreDetails(const Store& store);

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

int main() // Main Function
{
    createStoreFiles(); // Creating store files
    vector<Store> stores; // Storing Stores inside a vector
    loadAllStores(stores); // Function for loading all stores from the file 

    vector <User> users; // Storing User inside a vector
    loadAllUsers(users); // Function for loading all users from the file

    mainMenu(users, stores); // Main Menu Function

    saveAllUsers(users); // Function for saving all users to the file
    return 0;
}

// Update 10/06/2025 Started

bool fileExists(const string& filename) // Function to check if files exists
{
    ifstream file(filename);
    return file.is_open(); // Returning filename if file opens
}
void createStoreFiles()
{
    vector<string> stores = { "Auckland.txt", "Christchurch.txt", "Wellington.txt" }; // Maually Adding the 3 stores



    for (const auto& storeFile : stores) // Looping throguh each store file 
    {
        ifstream checkFIle(storeFile); // Checking if files already exists
        if (!fileExists(storeFile))
        {
            cout << "Created: ";

            ofstream file(storeFile); // Creating a file
            if (file.is_open()) // Attempting to open the file
            {
                // cout << storeFile << " "; // Checking to see if the files are created (Remove the // for testing)
                file.close(); // Closing file
            }
            else
            {
                cout << "(Error) Could not created file : " << storeFile << endl; // Error Message
            }
        }

    }
    cout << endl;
}
void loadAllStores(vector<Store>& stores) // Function to load all store data into the vector
{
    vector<string> filenames = { "Auckland.txt", "Christchurch.txt", "Wellington.txt" }; // Filesnames to load from
    vector<string> locations = { "Auckland", "Christchurch", "Wellington" }; // Storing store locations

    for (int i = 0; i < filenames.size(); i++) // Looping throguh all store files
    {
        Store store; // Creating a store object
        store.storeLocation = locations[i]; // Assingning store location 
        store.loadProcutsFromFile(filenames[i]); // Loading products from the file
        stores.push_back(store); // Add store to the list
    }
}
void dispalyStoreDetails(const Store& store) // Function to display store details
{
    cout << "Store Details \n" << endl;
    cout << "Location :" << store.storeLocation << endl;
    cout << "Products : " << endl;
    store.displayProducts(); // Function to display all products in the selected store file
    cout << endl;
}
int selectStoreMenu(const vector<Store>& stores) // Function to allow users to select a store from the list
{
    char option; // Variable for user input

    cout << "Select a store" << endl;

    // Displaying the store locations
    cout << "1. " << stores[0].storeLocation << endl;
    cout << "2. " << stores[1].storeLocation << endl;
    cout << "3. " << stores[2].storeLocation << endl;
    cout << "4. " << "Back" << endl;

    cout << "Option : ";
    cin >> option; // Getting user input
    cout << endl;

    switch (option) // Using switch case to go to user option
    {
    case '1': // Case 1, Displays store (Auckland)
    {
        return 0; // Index value is 1
    }
    case '2': // Case 2, Displays Store (Christchurch)
    {
        return 1; // Index value is 2
    }
    case '3': // Case 3, Displays Store (Wellingtion)
    {
        return 2; // Index value is 3
    }
    case '4': // Case 4, Goes back to menu
    {
        // Back
        return -1; // To go back 
    }
    default:
    {
        system("cls"); // Clearing screen
        cout << "\n(Error Message) Please enter the correct input\n" << endl; // Displaying error message
    }
    }


}

// // Update 12/06/2025 Ended

void saveAllUsers(const vector<User>& users) // Function for saving all users inside the file
{
    try {
        ofstream file("Users.txt"); // Output File 
        if (!file.is_open()) // Checking if the file has opened
        {
            throw runtime_error("Failed to open Users.txt for writing.");
        }

        for (const auto& user : users) // Using a auto for loop to save all the data in the user to the file
        {
            user.saveToFile(file);
        }

        file.close(); // Closing the file
    }
    catch (const exception& e) {
        cerr << "\n(Error) Could not save users: " << e.what() << endl;
    }
}
void loadAllUsers(vector<User>& users) // Funciton for loading all the users information from the file
{
    try {
        ifstream file("Users.txt"); // Input File 
        if (!file.is_open()) // Checking if the file has opened
        {
            throw runtime_error("Failed to open Users.txt for reading.");
        }

        string line; // Using a string variales to gather the information
        while (getline(file, line))
        {
            User user;
            if (user.loadFromLine(line)) // Checking if sussceful in getting the information
            {
                users.push_back(user); // Pushing back the users information into the vector
            }
        }

        file.close(); // Closing the file
    }
    catch (const exception& e) {
        cerr << "\n(Error) Could not load users: " << e.what() << endl;
    }
}

void mainMenu(vector<User>& users, vector<Store>& stores)
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
        {
            int selectStore; // Varaible for selected store

            do
            {
                selectStore = selectStoreMenu(stores); // Function to select store 

                if (selectStore == -1)
                {
                    // Going back 
                    break;
                }

                dispalyStoreDetails(stores[selectStore]); // Displaying the store

            } while (true);
        }
        case '2':
        {
            bool checkUserLogin = false;
            // Login Menu;
            userLogin(users, checkUserLogin);
            while (checkUserLogin)
            {
                userMenu(users, stores, checkUserLogin);
            }
            break;
        }
        case '3':
        {
            cout << "Exiting Program!" << endl;
            break;
        }
        case '&':
        {
            system("cls");
            // Admin login menu
            adminMenu(users);
            break;
        }
        default:
            system("cls");
            cout << "\n(Error Message) Please enter the correct input\n" << endl;
            break;
        }
    } while (option != '3');

}
bool userMenu(vector<User>& users, vector<Store>& stores, bool& checkUserLogin)
{
    char option;

    do
    {
        cout << "User Menu\n" << endl;

        cout << "1. Store" << endl;
        cout << "2. Account" << endl;
        cout << "3. Sign out" << endl;

        cout << "option : ";
        cin >> option;
        cout << endl;

        switch (option)
        {
        case '1':
        {
            // Store menu;

            int selectStore; // Varaible for selected store

            do
            {
                selectStore = selectStoreMenu(stores); // Function to select store 

                if (selectStore == -1)
                {
                    // Going back 
                    break;
                }

                dispalyStoreDetails(stores[selectStore]); // Displaying the store

            } while (true);

            break;
        }
        case '2':
        {
            cout << "Account details";
            // Display account information with weekly and fornitly and monthly spendings!
            break;
        }
        case '3':
        {
            checkUserLogin = false;
            // Bool variable
           // mainMenu(users, stores);
            return 0;
        }
        default:
            cout << "Error" << endl; // Change the error message later...
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
void userLogin(vector<User>& users, bool& checkUserLogin) // User Login Menu
{
    char option;

    do // Do while loop 
    {

        if (checkUserLogin) // Checking if signed in already
        {
            break;
        }

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

                    checkUserLogin = true;
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

.
// able to edit the products and it contains prices or something...
// 
