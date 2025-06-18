// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>      // For numeric_limits
#include <iomanip>     // For setw, left alignment
#include <stdexcept>   // For runtime_error
#include <cstdlib>     // For atoi, atof
#include <algorithm>   // For transform(), all_of
using namespace std;

// Structure Product: holds individual product details
struct Product
{
    string productName; // Name of the product
    double price;       // Price (cosmetic)
    int quantity;       // Quantity in stock
};

// Structure StaffMember: holds staff details with weekly hours
struct StaffMember
{
    string firstName;            // First name of employee
    string lastName;             // Last name of employee
    vector<string> hours;        // Hours for Monday-Sunday (index 0=Mon)
};

// Structure Store: holds store location, its product list, and its roster
struct Store
{
    string storeLocation;               // Store location name
    vector<Product> products;           // List of products
    vector<StaffMember> staffList;      // Roster for this store

    // Loads products from a given file (CSV: name,price,quantity)
    bool loadProductsFromFile(const string& filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "(Error) Failed to open " << filename << " for reading" << endl;
            return false;
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name, priceStr, qtyStr;
            // Parse CSV line
            if (getline(ss, name, ',') && getline(ss, priceStr, ',') && getline(ss, qtyStr))
            {
                Product p;
                p.productName = name;                     // Assign product name
                p.price = atof(priceStr.c_str());         // Convert string to double
                p.quantity = atoi(qtyStr.c_str());        // Convert string to int
                products.push_back(p);                    // Add to vector
            }
        }
        file.close(); // Close file when done
        return true;
    }

    // Saving Products to File
    void saveProductsToFile(const string& filename) const
    {
        ofstream f(filename);
        if (!f.is_open())
        {
            cout << "(Error) Could not open file : " << filename << endl;
            return;
        }
        for (const Product& p : products)
            f << p.productName << "," << p.price << ',' << p.quantity << endl;
        f.close();
    }

    // Displays the list of products in the store
    void displayProducts() const
    {
        cout << "Products in " << storeLocation << endl;
        int idx = 1;
        for (const auto& p : products)
        {
            cout << idx++ << ". " << p.productName
                << " | $:" << p.price
                << " | Stock: " << p.quantity << endl;
        }
    }

    // Managing all products within any store
    void manageProducts()
    {
        char option;
        do
        {
            displayProducts();
            cout << endl;
            cout << "1. Add " << endl;
            cout << "2. Edit" << endl;
            cout << "3. Delete" << endl;
            cout << "4. Back" << endl;
            cout << "Option : ";
            // Input validation
            option = cin.get(); // Reads one character
            char check = cin.get(); // Reads the next character (If there is any)
            // Clearing extra input
            while (check != '\n' && check != EOF) { check = cin.get(); }
            if (check != '\n' || option < '1' || option > '4') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }
            cout << endl;
            switch (option)
            {
            case '1': // Adding Product
            {
                Product p;
                cout << "Enter Product Name : ";
                getline(cin, p.productName);

                for (int i = 0; i < products.size(); i++) // Checking if product already exists!
                {
                    while (p.productName == products[i].productName)
                    {
                        cout << "Product already in stock!" << endl;
                        cout << "Enter Product Name : ";
                        getline(cin, p.productName);
                    }
                }

                cout << "Enter Product Price : ";
                cin >> p.price;
                cout << endl;

                while (p.price < 1) // Error Handling with negative numbers
                {
                    //system("cls");
                    cout << "Invalid Input!\n" << endl;
                    cout << "Enter Product Price : ";
                    cin >> p.price;
                    cout << endl;
                }

                cout << "Enter Product Quantity : ";
                cin >> p.quantity;
                cout << endl;

                while (p.quantity < 1) // Error Handling with negative numbers
                {
                    //system("cls");
                    cout << "Invalid Input!\n" << endl;
                    cout << "Enter Product Quantity : ";
                    cin >> p.quantity;
                    cout << endl;
                }

                products.push_back(p);
                cout << "Product Added" << endl;

                cin.ignore(); // Changed

                break;
            }
            case '2': // Editing Product
            {
                string selectedItem;
                displayProducts();
                cout << "Enter a Product Name to edit " << endl;
                cout << "Item : ";
                getline(cin, selectedItem);
                for (auto& product : products)
                {
                    if (product.productName == selectedItem)
                    {
                        char o;
                        do
                        {
                            cout << "1. Edit Name" << endl;
                            cout << "2. Edit Price" << endl;
                            cout << "3. Edit Quantity" << endl;
                            cout << "4. Back" << endl;
                            cout << "Option : ";
                            o = cin.get();
                            char check2 = cin.get();
                            while (check2 != '\n' && check2 != EOF) { check2 = cin.get(); }
                            if (check2 != '\n' || o < '1' || o > '4') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }
                            cout << endl;
                            switch (o)
                            {
                            case '1': // Edit Name
                            {
                                cout << "Current Name : " << product.productName << endl;
                                cout << "New Name : ";
                                getline(cin, product.productName);

                                for (int i = 0; i < products.size(); i++) // Checking if product already exists!
                                {
                                    while (product.productName == products[i].productName)
                                    {
                                        cout << "Product already in stock!" << endl;
                                        cout << "Enter Product Name : ";
                                        getline(cin, product.productName);
                                    }
                                }
                                cout << endl;
                                break;
                            }
                            case '2': // Edit Price
                            {
                                cout << "Item : [ " << product.productName << " ]\n" << endl;
                                cout << "Current Price : " << product.price << endl;
                                cout << "New Price : ";
                                cin >> product.price;
                                cout << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }
                            case '3': // Edit Quantity
                            {
                                cout << "Item : [ " << product.productName << " ]\n" << endl;
                                cout << "Current Quantity [Stock] : " << product.quantity << endl;
                                cout << "New Quantity [Stock] : ";
                                cin >> product.quantity;
                                cout << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                break;
                            }
                            case '4': // Back
                                break;
                            }
                        } while (o != '4');
                        break;
                    }
                }
                break;
            }
            case '3': // Delete Product
            {
                string selectedItem;
                displayProducts();
                cout << "Enter a Product Item to delete " << endl;
                cout << "Item : ";
                getline(cin, selectedItem);
                for (size_t i = 0; i < products.size(); i++)
                {
                    if (products[i].productName == selectedItem)
                    {
                        cout << "Are you sure you want to delete this product!" << endl;
                        cout << "Item : [ " << products[i].productName << "] ";
                        cout << "Yes | No : ";
                        string strCheck; cin >> strCheck;
                        transform(strCheck.begin(), strCheck.begin(), strCheck.end(), ::tolower);
                        while (strCheck != "yes" && strCheck != "no")
                        {
                            cout << "(Error) : Invalid Input, Try again \n" << endl;
                            cout << "Yes | No : ";
                            cin >> strCheck;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            transform(strCheck.begin(), strCheck.begin(), strCheck.end(), ::tolower);
                        }
                        if (strCheck == "yes")
                        {
                            products.erase(products.begin() + i);
                            cout << "Product Deleted" << endl;
                        }
                        else
                        {
                            cout << "Deletion Cancelled" << endl;
                        }
                        break;
                    }

                    cin.ignore();

                }
                break;
            }
            case '4': // Back
                break;
            }
        } while (option != '4');
    }

    // Searches for products containing the given keyword
    void searchProducts(const string& keyword) const
    {
        cout << "Search results for '" << keyword << "' in " << storeLocation << ":\n";
        bool found = false;
        int idx = 1;
        for (const auto& p : products)
        {
            if (p.productName.find(keyword) != string::npos)
            {
                cout << idx << ". " << p.productName
                    << " | $:" << p.price
                    << " | Stock: " << p.quantity << endl;
                found = true;
            }
            idx++;
        }
        if (!found)
            cout << "(No matching products found)\n";
    }
};

// Structure CartItem: represents one line in the user's shopping cart
struct CartItem
{
    string productName;  // name of product
    double price;        // unit price
    int quantity;        // quantity chosen
};

// Global cart for the current logged-in session
vector<CartItem> cart;

// Forward declaration of User
struct User;
User* currentUser = nullptr;

// Structure User: holds customer account information
struct User
{
protected:
    string username;
    string password;
public:
    string name;
    string surname;
    int age;
    double totalSpent;   // tracks spending summary

    // Default constructor initializes empty fields
    User() : username(""), password(""), name(""), surname(""), age(0), totalSpent(0.0) {}

    // Prompts for and validates password (cannot match username)
    void setUpPassword()
    {
        cout << "Enter a Password: ";
        getline(cin, password);
        while (password.empty())
        {
            cout << "Invalid, Try again\n" << endl;
            cout << "Enter a Password: "; getline(cin, password);
            cout << endl;
        }
        while (password == username)
        {
            cout << "(Error) Password cannot match username." << endl;
            cout << "Enter a Password: ";
            getline(cin, password);
        }
        cout << endl;
    }

    // Prompts for and validates personal details
    void getInformation()
    {
        cout << "Name: "; getline(cin, name);
        while (name.empty())
        {
            cout << "Invalid, Try again\n" << endl;
            cout << "Enter a Name: "; getline(cin, name);
            cout << endl;
        }
        cout << "Surname: "; getline(cin, surname);
        while (surname.empty())
        {
            cout << "Invalid, Try again\n" << endl;
            cout << "Enter a Surname: "; getline(cin, surname);
            cout << endl;
        }
        cout << "Age: ";
        while (true)
        {
            cin >> age;
            if (cin.fail() || age < 5 || age > 120)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid. Enter age between 5 and 120: ";
            }
            else
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }
        cout << endl;
    }

    void setUsername(const string& u)
    {
        username = u;
    }
    string getUsername() const { return username; }
    bool checkPassword(const string& p) const { return p == password; }

    // Saves user data to a CSV file
    void saveToFile(ofstream& f) const
    {
        f << username << ',' << password << ','
            << name << ',' << surname << ',' << age << ',' << totalSpent << '\n';
    }

    // Loads user data from a CSV line
    bool loadFromLine(const string& line)
    {
        stringstream ss(line);
        string usr, pwd, nm, sn, ag, ts;
        if (!getline(ss, usr, ',') || !getline(ss, pwd, ',') ||
            !getline(ss, nm, ',') || !getline(ss, sn, ',') ||
            !getline(ss, ag, ',') || !getline(ss, ts))
            return false;
        username = usr;
        password = pwd;
        name = nm;
        surname = sn;
        age = stoi(ag);
        totalSpent = stod(ts);
        return true;
    }

    // Records spending amount into summary
    void recordSpending(double amount)
    {
        totalSpent += amount;
    }

    // Displays spending summary for user
    void viewSummary() const
    {
        cout << name << " " << surname << "'s Spending Summary:" << endl;
        cout << "Total spent: $" << totalSpent << "\n\n";
    }
};

// Function prototypes
void createStoreFiles();
bool fileExists(const string& fn);
void saveAllStores(const vector<Store>& stores);
void loadAllStores(vector<Store>& stores);
void saveAllUsers(const vector<User>& users);
void loadAllUsers(vector<User>& users);
bool usernameExists(const vector<User>& users, const string& uname);
void mainMenu(vector<User>& users, vector<Store>& stores);
bool userMenu(vector<User>& users, vector<Store>& stores, bool& loggedIn);
void adminMenu(vector<User>& users, vector<Store>& stores);
void userLogin(vector<User>& users, bool& loggedIn);
int selectStoreMenu(const vector<Store>& stores);
void displayStoreDetails(const Store& store);
void printStrongBorder(const string& title);
void printMenuOption(const string& opt);
void addToCart(const Product& p, int qty);
void displayCart();
void clearCart();

void staffMenu(vector<Store>& stores); // Working on...

void purchaseCart(vector<Store>& stores);
void displayWeeklyRoster(const Store& store);            // display full weekly roster for a store
void manageRoster(Store& store);                         // manage staff and schedules for a store

// Draws a border and title for menus
void printStrongBorder(const string& title)
{
    int w = static_cast<int>(title.length()) + 8;
    cout << string(w, '#') << '\n'
        << "## " << title << " ##" << '\n'
        << string(w, '#') << endl;
}

// Prints a single menu option line
void printMenuOption(const string& opt)
{
    cout << "|| " << opt << endl;
}

// Adds qty of a product into the cart (merges if already present)
void addToCart(const Product& p, int qty)
{
    if (qty <= 0) // prevent negative or zero
    {
        cout << "(Error) Quantity must be positive." << endl;
        return;
    }
    for (auto& item : cart)
        if (item.productName == p.productName)
        {
            item.quantity += qty;
            return;
        }
    cart.push_back({ p.productName, p.price, qty });
}

// Displays current cart contents and total
void displayCart()
{
    system("cls");
    printStrongBorder("Your Cart");
    if (cart.empty())
    {
        cout << "(Your cart is empty)\n\n";
        return;
    }
    double total = 0.0;
    int idx = 1;
    for (const auto& item : cart)
    {
        double line = item.price * item.quantity;
        cout << idx++ << ". "
            << item.productName
            << " | Qty: " << item.quantity
            << " | $" << item.price << " each"
            << " | Subtotal: $" << line
            << endl;
        total += line;
    }
    cout << "\nTotal: $" << total << "\n\n";
}

// Clears out the cart
void clearCart()
{
    cart.clear();
    cout << "Cart cleared." << "\n\n";
}

// Finalizes purchase: deducts stock and records spending
void purchaseCart(vector<Store>& stores)
{
    if (!currentUser) return;
    if (cart.empty())
    {
        cout << "(Your cart is empty)\n\n";
        return;
    }
    double total = 0.0;
    for (const auto& item : cart)
    {
        for (auto& store : stores)
        {
            for (auto& p : store.products)
            {
                if (p.productName == item.productName)
                {
                    if (item.quantity > p.quantity)
                    {
                        cout << "(Error) Insufficient stock for " << p.productName << "\n";
                    }
                    else
                    {
                        p.quantity -= item.quantity;
                        total += item.price * item.quantity;
                    }
                    break;
                }
            }
        }
    }
    currentUser->recordSpending(total);
    cout << "Purchase complete! Total: $" << total << "\n\n";
    clearCart();
}

// Displays the weekly roster: days and staff with their hours  /Removed const
void displayWeeklyRoster(Store& store)
{
    system("cls");
    printStrongBorder("Weekly Staff Roster - " + store.storeLocation);
    const vector<string> days = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
    for (int d = 0; d < 7; ++d)
    {
        cout << days[d] << ":\n";
        bool any = false;
        for (const auto& m : store.staffList)
        {
            if (d < (int)m.hours.size() && !m.hours[d].empty())
            {
                cout << " - " << m.firstName << " " << m.lastName << " : " << m.hours[d] << "\n";
                any = true;
            }
        }
        if (!any) cout << "   (No one scheduled)\n";
        cout << endl;
    }
    cout << "Press any key to continue...";
    _getch();
}

// Roster management submenu for Admin for a specific store
void manageRoster(Store& store)
{
    char choice;
    const vector<string> days = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
    do
    {
        system("cls");
        printStrongBorder("Roster Management - " + store.storeLocation);
        printMenuOption("1. Add Staff");
        printMenuOption("2. Delete Staff");
        printMenuOption("3. View Weekly Roster");
        printMenuOption("4. Edit Staff");
        printMenuOption("5. Back");
        cout << string(30, '#') << endl;
        cout << "Option: ";

        choice = cin.get();
        char check = cin.get();
        while (check != '\n' && check != EOF) { check = cin.get(); }
        if (check != '\n' || choice < '1' || choice > '5')
        {
            system("cls");
            cout << "(Error) Invalid input." << endl;
            cout << "\nPress any key...";
            _getch();
            continue;
        }

        cout << endl;
        switch (choice)
        {
        case '1': // Add Staff
        {
            StaffMember m;
            m.hours.resize(7);
            string input;

            // get names
            system("cls");
            printStrongBorder("Add Staff - " + store.storeLocation);
            cout << "Enter first name: ";
            getline(cin, m.firstName);
            cout << "Enter last name: ";
            getline(cin, m.lastName);

            // shift entry instructions
            cout << "\nFor each day select:\n";
            cout << " 1 = 09:00-17:00   2 = 22:00-06:00   (leave blank to skip)\n\n";

            // live preview + validation
            for (int i = 0; i < 7; ++i)
            {
                while (true)
                {
                    // DRAW THE TABLE
                    system("cls");
                    printStrongBorder("Add Staff - " + store.storeLocation);
                    cout << "+-------------+------------------+\n";
                    cout << "| Day         | Shift            |\n";
                    cout << "+-------------+------------------+\n";
                    // already-entered rows
                    for (int j = 0; j < i; ++j)
                    {
                        cout << "| " << setw(11) << left << days[j]
                            << " | " << setw(16) << left
                            << (m.hours[j].empty() ? "(none)" : m.hours[j])
                            << " |\n";
                    }
                    // upcoming days
                    for (int j = i; j < 7; ++j)
                    {
                        cout << "| " << setw(11) << left << days[j]
                            << " | " << setw(16) << left << " "
                            << " |\n";
                    }
                    cout << "+-------------+------------------+\n\n";

                    // prompt
                    cout << "Enter shift for " << days[i]
                        << " (1=09:00-17:00, 2=22:00-06:00, blank=skip): ";

                    getline(cin, input);
                    if (input.empty())            // blank → skip
                    {
                        m.hours[i].clear();
                        break;
                    }
                    // only digits allowed
                    if (!all_of(input.begin(), input.end(), ::isdigit))
                    {
                        cout << "\n(Error) Only numbers accepted.  Press any key to retry...";
                        _getch();
                        continue;
                    }
                    int sel = stoi(input);
                    if (sel == 1)
                    {
                        m.hours[i] = "09:00-17:00";
                        break;
                    }
                    else if (sel == 2)
                    {
                        m.hours[i] = "22:00-06:00";
                        break;
                    }
                    else
                    {
                        cout << "\n(Error) Invalid selection.  Press any key to retry...";
                        _getch();
                    }
                }
            }

            // final checks & add
            if (m.firstName.empty() || m.lastName.empty())
                cout << "\n(Error) Name cannot be empty.\n";
            else
            {
                store.staffList.push_back(m);
                cout << "\nAdded: " << m.firstName << " " << m.lastName << endl;
            }
            break;
        }
        case '2': // Delete Staff
        {
            if (store.staffList.empty()) cout << "(Error) No staff to delete.\n";
            else
            {
                cout << "Select staff to delete:\n";
                for (size_t i = 0; i < store.staffList.size(); ++i)
                    cout << i + 1 << ". " << store.staffList[i].firstName << " " << store.staffList[i].lastName << endl;
                cout << "Enter number: ";
                int num; cin >> num; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (num < 1 || num >(int)store.staffList.size())
                    cout << "(Error) Invalid selection.\n";
                else
                {
                    cout << "Deleted: " << store.staffList[num - 1].firstName << " " << store.staffList[num - 1].lastName << endl;
                    store.staffList.erase(store.staffList.begin() + (num - 1));
                }
            }
            break;
        }
        case '3': // View Weekly Roster
            displayWeeklyRoster(store);
            break;
        case '4': // Edit Staff
        {
            if (store.staffList.empty()) { cout << "(Error) No staff to edit.\n"; break; }
            cout << "Select staff to edit:\n";
            for (size_t i = 0; i < store.staffList.size(); ++i)
                cout << i + 1 << ". " << store.staffList[i].firstName << " " << store.staffList[i].lastName << endl;
            cout << "Enter number: ";
            int num; cin >> num; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (num < 1 || num >(int)store.staffList.size())
                cout << "(Error) Invalid selection.\n";
            else
            {
                StaffMember& m = store.staffList[num - 1];
                system("cls");
                printStrongBorder("Edit Staff Hours - " + store.storeLocation);
                cout << "Editing hours for " << m.firstName << " " << m.lastName << ":\n";
                cout << "\nFor each day select:\n";
                cout << " 1 = 09:00-17:00   2 = 22:00-06:00   3 = None  (leave blank to keep current)\n\n";
                for (int i = 0; i < 7; ++i)
                {
                    cout << days[i] << " [" << (m.hours[i].empty() ? "none" : m.hours[i]) << "]: ";
                    string sel;
                    getline(cin, sel);
                    if (sel == "1") m.hours[i] = "09:00-17:00";
                    else if (sel == "2") m.hours[i] = "22:00-06:00";
                    else if (sel == "3") m.hours[i].clear();
                    // blank => keep existing
                }
                cout << "\nUpdated schedule.\n";
            }
            break;
        }
        case '5': // Back
            return;
        }

        cout << "\nPress any key to continue...";
        _getch();

    } while (choice != '5');
}

// Checks if a username already exists (to enforce uniqueness)
bool usernameExists(const vector<User>& users, const string& uname)
{
    for (const auto& u : users)
        if (u.getUsername() == uname)
            return true;
    return false;
}

// Main entry point
int main()
{
    system("color 02");               // Changed Text color (Green)
    createStoreFiles();               // Ensure store files exist
    vector<Store> stores;
    loadAllStores(stores);            // Load data for each store

    vector<User> users;
    loadAllUsers(users);              // Load existing users

    mainMenu(users, stores);          // Launch main menu loop

    saveAllUsers(users);              // Save users on exit
    saveAllStores(stores);            // Save stores on exit
    return 0;
}

// Creates store files if they don't exist (blank initial files)
void createStoreFiles()
{
    vector<string> files = { "Auckland.txt", "Christchurch.txt", "Wellington.txt" };
    for (const auto& fn : files)
    {
        if (!fileExists(fn))
        {
            cout << "Created: " << fn << endl;
            ofstream f(fn);
            if (f.is_open()) f.close();
            else cout << "(Error) Could not create file: " << fn << endl;
        }
    }
    cout << endl;
}

// Checks if a file exists (openable)
bool fileExists(const string& fn)
{
    ifstream f(fn);
    return f.is_open();
}

// Load all stores and their products
void loadAllStores(vector<Store>& stores)
{
    vector<string> filenames = { "Auckland.txt", "Christchurch.txt", "Wellington.txt" };
    vector<string> locations = { "Auckland", "Christchurch", "Wellington" };
    for (size_t i = 0; i < filenames.size(); ++i)
    {
        Store s;
        s.storeLocation = locations[i];
        s.loadProductsFromFile(filenames[i]);
        stores.push_back(s);
    }
}

// Saves all stores and their products to a file on exit
void saveAllStores(const vector<Store>& stores)
{
    for (const Store& s : stores)
    {
        string filename = s.storeLocation + ".txt";
        s.saveProductsToFile(filename);
    }
}

// Displays details for a selected store
void displayStoreDetails(const Store& store)
{
    system("cls");
    printStrongBorder("Store Details");
    cout << "Location: " << store.storeLocation << endl
        << "Products:" << endl;
    store.displayProducts();
    cout << endl;
}

// Menu for selecting which store to browse                         /// Has input validation
int selectStoreMenu(const vector<Store>& stores)
{
    system("cls");
    printStrongBorder("Select a Store");
    for (size_t i = 0; i < stores.size(); ++i)
        printMenuOption(to_string(i + 1) + ". " + stores[i].storeLocation);
    printMenuOption("4. Back");
    cout << string(30, '#') << endl;
    cout << "Option: ";
    char opt = cin.get();
    char check = cin.get();
    while (check != '\n' && check != EOF) { check = cin.get(); }
    if (check != '\n' || opt < '1' || opt > '4') { system("cls"); cout << "(Error) Invalid input." << endl; return -1; }
    cout << endl;
    switch (opt)
    {
    case '1': return 0;
    case '2': return 1;
    case '3': return 2;
    case '4': return -1;
    default:
        system("cls");
        cout << "(Error) Invalid input." << endl;
        return -1;
    }
}

// Saves all users to file on exit
void saveAllUsers(const vector<User>& users)
{
    try
    {
        ofstream f("Users.txt");
        if (!f.is_open()) throw runtime_error("Failed to open Users.txt");
        for (const auto& u : users)
            u.saveToFile(f);
        f.close();
    }
    catch (const exception& e)
    {
        cerr << "(Error) " << e.what() << endl;
    }
}

// Loads all existing users from file
void loadAllUsers(vector<User>& users)
{
    try
    {
        ifstream f("Users.txt");
        if (!f.is_open()) throw runtime_error("Failed to open Users.txt");
        string line;
        while (getline(f, line))
        {
            User u;
            if (u.loadFromLine(line)) users.push_back(u);
        }
        f.close();
    }
    catch (const exception& e)
    {
        cerr << "(Error) " << e.what() << endl;
    }
}

// Main menu shown at startup                                       /// Has input validation
void mainMenu(vector<User>& users, vector<Store>& stores)
{
    char op;
    do
    {
        system("cls");
        printStrongBorder("Aotearoa Inventory System");
        printMenuOption("1. Store");
        printMenuOption("2. Customer Login");
        printMenuOption("3. Admin Login");
        printMenuOption("4. Staff Login");
        printMenuOption("5. Exit");
        cout << string(30, '#') << endl;
        cout << "Option: ";

        op = cin.get();
        char check = cin.get();
        while (check != '\n' && check != EOF) { check = cin.get(); }
        if (check != '\n' || op < '1' || op > '5') { system("cls"); cout << "(Error) Invalid input." << endl; }

        cout << endl;
        switch (op)
        {
        case '1': // Browse stores without login
        {
            int idx;
            do
            {
                idx = selectStoreMenu(stores);
                if (idx < 0) break;
                displayStoreDetails(stores[idx]);
                // Search products?
                cout << "Search products? (y/n): ";
                char s;

                s = cin.get();
                char check = cin.get();
                while (check != '\n' && check != EOF) { check = cin.get(); }
                if (check != '\n' || s < 'y' || s > 'n') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }

                if (s == 'y' || s == 'Y')
                {
                    cout << "Enter keyword: ";
                    string kw; getline(cin, kw);
                    stores[idx].searchProducts(kw);
                }

                // Add to cart prompt
                cout << "Enter product number to add to cart (0 = back): ";
                int choice; cin >> choice;
                if (choice > 0 && choice <= static_cast<int>(stores[idx].products.size()))
                {
                    cout << "Quantity to add: ";
                    int qty; cin >> qty;
                    addToCart(stores[idx].products[choice - 1], qty);
                    cout << "\nAdded to cart! Press any key to continue...";
                }
                else
                {
                    cout << "\nPress any key to continue...";
                }
                _getch();
            } while (true);
        } break;
        case '2': // Customer login flow
        {
            bool loggedIn = false;
            userLogin(users, loggedIn);
            while (loggedIn)
                if (!userMenu(users, stores, loggedIn)) break;
        } break;
        case '3': // Admin login flow
            adminMenu(users, stores);
            break;
        case '4':
        {
            staffMenu(stores);
            break;
        }
        case '5':
            cout << "Exiting Program!" << endl;
            break;
        default:
            system("cls");
            cout << "(Error) Invalid input." << endl;
        }
    } while (op != '5');
}
// User menu: login then user panel
bool userMenu(vector<User>& users, vector<Store>& stores, bool& loggedIn)
{
    char o;
    do
    {
        system("cls"); printStrongBorder("User Menu");
        printMenuOption("1. Store");
        printMenuOption("2. View Cart");
        printMenuOption("3. Purchase Cart");
        printMenuOption("4. Account");
        printMenuOption("5. Sign out");
        cout << string(30, '#') << endl;
        cout << "Option: ";

        o = cin.get();
        char check = cin.get();
        while (check != '\n' && check != EOF) { check = cin.get(); }
        if (check != '\n' || o < '1' || o > '5') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }

        cout << endl;
        switch (o)
        {
        case '1': // View/browse stores
        {
            int idx;
            do
            {
                idx = selectStoreMenu(stores);
                if (idx < 0) break;
                displayStoreDetails(stores[idx]);
                cout << "Search products? (y/n): ";
                char s; s = cin.get();
                char check = cin.get();
                while (check != '\n' && check != EOF) { check = cin.get(); }
                if (check != '\n' || s < 'y' || s > 'n')
                {
                    system("cls");
                    cout << "(Error) Invalid input." << endl;
                    cout << "\nPress any key...";
                    _getch();
                    continue;
                }

                if (s == 'y' || s == 'Y')
                {
                    cout << "Enter keyword: ";
                    string kw; getline(cin, kw);
                    stores[idx].searchProducts(kw);
                }
                cout << "Enter product number to add to cart (0 = back): ";
                int choice; cin >> choice; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (choice > 0 && choice <= (int)stores[idx].products.size())
                {
                    cout << "Quantity to add: ";
                    int qty; cin >> qty; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    addToCart(stores[idx].products[choice - 1], qty);
                    cout << "\nAdded to cart! Press any key to continue...";
                }
                else
                {
                    cout << "\nPress any key to continue...";
                }
                _getch();
            } while (true);
        } break;

        case '2': // View Cart
            displayCart();
            cout << "Press any key to continue...";
            _getch();
            break;

        case '3': // Purchase Cart
            purchaseCart(stores);
            cout << "Press any key to continue...";
            _getch();
            break;

        case '4': // Account details / spending summary
            system("cls"); printStrongBorder("Account Details");
            if (currentUser) currentUser->viewSummary();
            cout << "Press any key to continue...";
            _getch();
            break;

        case '5': // Sign out
            loggedIn = false;
            clearCart();  // wipe cart for next session
            currentUser = nullptr;
            return false;

        default:
            cout << "(Error) Invalid input." << endl;
        }

    } while (o != '5');

    return false;
}

// Admin menu: login then admin panel                               /// Has input valdation
void adminMenu(vector<User>& users, vector<Store>& stores)
{
    char c;
    string usr, pwd;
    do
    {
        system("cls"); printStrongBorder("Admin Login");
        printMenuOption("1. Login"); printMenuOption("2. Back");
        cout << string(30, '#') << endl;
        cout << "Option: ";

        c = cin.get();
        char check = cin.get();
        while (check != '\n' && check != EOF) { check = cin.get(); }
        if (check != '\n' || c < '1' || c > '2') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }

        cout << endl;
        switch (c)
        {
        case '1': // Admin authentication
            cout << "Username: "; getline(cin, usr);
            cout << "Password: "; getline(cin, pwd);
            if (usr != "ADMIN" || pwd != "PASSWORD")
            {
                system("cls");
                cout << "(Error) Admin credentials incorrect." << endl;
                cout << "\nPress any key to retry..."; _getch();
            }
            else
            {
                currentUser = nullptr; // admin has no spending summary
                char a;
                do
                {
                    system("cls"); printStrongBorder("Admin Panel");
                    printMenuOption("1. View Products");
                    printMenuOption("2. Manage Roster");
                    printMenuOption("3. Low Stock Alerts");
                    printMenuOption("4. Back");
                    cout << string(30, '#') << endl;
                    cout << "Option: ";

                    a = cin.get();
                    char chk = cin.get();
                    while (chk != '\n' && chk != EOF) { chk = cin.get(); }
                    if (chk != '\n' || a < '1' || a > '4') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }

                    cout << endl;
                    switch (a)
                    {
                    case '1': // Browse store products
                    {
                        int idx;
                        char o;
                        do
                        {
                            idx = selectStoreMenu(stores);
                            if (idx < 0) break;
                            displayStoreDetails(stores[idx]);
                            cout << "1. Edit Products" << endl;
                            cout << "2. Back" << endl;
                            cout << "Option : ";
                            o = cin.get();
                            char chk2 = cin.get();
                            while (chk2 != '\n' && chk2 != EOF) { chk2 = cin.get(); }
                            if (chk2 != '\n' || o < '1' || o > '2') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }
                            cout << endl;
                            if (o == '1') stores[idx].manageProducts();
                        } while (o != '2');
                    } break;

                    case '2': // Manage staff roster
                    {
                        // Let admin pick which store first
                        int idx = selectStoreMenu(stores);
                        if (idx >= 0) {
                            // Then open that store's roster manager
                            manageRoster(stores[idx]);
                        }
                        break;
                    }

                    case '3': // Low stock notification
                        system("cls"); printStrongBorder("Low Stock Alerts");
                        for (const auto& store : stores)
                        {
                            cout << "Store: " << store.storeLocation << endl;
                            bool any = false;
                            int idx = 1;
                            for (const auto& p : store.products)
                            {
                                if (p.quantity < 5)
                                {
                                    cout << idx << ". " << p.productName << " (Stock: " << p.quantity << ")\n";
                                    any = true;
                                }
                                idx++;
                            }
                            if (!any) cout << "All items above threshold." << endl;
                            cout << endl;
                        }
                        cout << "Press any key to continue...";
                        _getch();
                        break;

                    case '4': // Back to main menu
                        break;
                    }
                } while (a != '4');
            }
            break;

        case '2': // Back to main menu
            break;
        }
    } while (c != '2');
}

// Customer login and registration menu                             /// Has Input validation
void userLogin(vector<User>& users, bool& loggedIn)
{
    char o;
    do
    {
        system("cls"); printStrongBorder("Customer Login");
        printMenuOption("1. Sign In"); printMenuOption("2. Register An Account"); printMenuOption("3. Back");
        cout << string(35, '#') << endl;
        cout << "Option: ";

        o = cin.get();
        char check = cin.get();
        while (check != '\n' && check != EOF) { check = cin.get(); }
        if (check != '\n' || o < '1' || o > '3') { system("cls"); cout << "(Error) Invalid input." << endl; continue; }

        cout << endl;
        switch (o)
        {
        case '1': // Sign in flow
        {
            string u, p;
            cout << "Username: "; getline(cin, u);
            cout << "Password: "; getline(cin, p);
            bool found = false;
            for (auto& x : users)
            {
                if (x.getUsername() == u && x.checkPassword(p))
                {
                    system("cls");
                    cout << "Welcome back, " << x.name << "!" << endl;
                    loggedIn = true;
                    currentUser = &x;
                    found = true;
                    return;
                }
            }
            if (!found)
            {
                cout << "(Error) Invalid credentials." << endl;
                cout << "\nPress any key to retry...";
                _getch();
            }
        } break;
        case '2': // Registration flow
        {
            User nu;
            string uname;
            bool ex;
            do
            {
                cout << "Enter a Username: "; getline(cin, uname);
                while (uname.empty())
                {
                    cout << "Invalid, Try again\n" << endl;
                    cout << "Enter a Username: "; getline(cin, uname);
                    cout << endl;
                }
                ex = usernameExists(users, uname);
                if (ex) cout << "(Error) Username taken." << endl;
            } while (ex);
            nu.setUsername(uname);
            nu.setUpPassword();
            nu.getInformation();
            users.push_back(nu);
            cout << "Registration completed!" << endl;
            cout << "\nPress any key to continue...";
            _getch();
        } break;
        case '3': // Back to main menu
            return;
        }
    } while (o != '3');
}

void staffMenu(vector<Store>& stores)
{
    char o;

    system("cls"); printStrongBorder("Admin Login");
    printMenuOption("1. Login"); printMenuOption("2. Back");
    cout << string(30, '#') << endl;
    cout << "Option: ";

    o = cin.get();
    char check = cin.get();
    while (check != '\n' && check != EOF) { check = cin.get(); }
    if (check != '\n' || o < '1' || o > '2')
    {
        system("cls");
        cout << "(Error) Invalid input." << endl;
        cout << "Press any key...";
        _getch();
    }


    switch (o)
    {
    case '1':
    {
        do
        {
            string username;
            string password;

            cout << "Username : ";
            getline(cin, username);

            cout << "Password : ";
            getline(cin, password);

            if (username != "STAFF" && password != "PASSWORD")
            {
                system("cls");
                cout << "Invalid Login...!" << endl;
                cout << "Press Any Key..." << endl;
                _getch();
                break;
            }

            system("cls"); printStrongBorder("Staff Roster");

            int idx = selectStoreMenu(stores);
            displayWeeklyRoster(stores[idx]);

            break;
        } while (true);

        break;
    }
    case '2':
    {
        break;
    }
    default:
        cout << "Invalid Input Try agian!\n" << endl;
        break;
    }
}