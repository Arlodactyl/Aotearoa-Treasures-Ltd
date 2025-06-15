// Aotearoa_Treasures_Ltd_Menu.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <algorithm>   // For transform() 
using namespace std;

// Structure Product: holds individual product details
struct Product
{
    string productName; // Name of the product
    double price;       // Price (cosmetic)
    int quantity;       // Quantity in stock
};

// Structure Store: holds store location and its product list
struct Store
{
    string storeLocation;      // Store location name
    vector<Product> products;  // List of products

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
        else
        {
            for (const Product& p : products)
            {
                f << p.productName << "," << p.price << ',' << p.quantity << endl;
            }

            f.close();
        }
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
            cin >> option;
            cout << endl;
            cin.ignore();

            switch (option)
            {
            case '1': // Adding Product
            {
                Product p;
                cout << "Enter Product Name : ";
                getline(cin, p.productName);

                cout << "Enter Product Price : ";
                cin >> p.price;
                cout << endl;

                cout << "Enter Product Quantity : ";
                cin >> p.quantity;
                cout << endl;

                products.push_back(p);
                cout << "Product Added" << endl;
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
                            cin >> option;
                            cout << endl;

                            switch (option)
                            {
                            case '1': // Edit Name
                            {
                                cout << "Current Name : " << product.productName << endl;
                                cout << "New Name : ";
                                getline(cin, product.productName);
                                cout << endl;
                                cin.ignore();
                                break;
                            }
                            case '2': // Edit Price
                            {
                                cout << "Item : [ " << product.productName << " ]\n" << endl;
                                cout << "Current Price : " << product.price << endl;
                                cout << "New Price : ";
                                cin >> product.price;
                                cout << endl;
                                break;
                            }
                            case '3': // Edit Quantity
                            {
                                cout << "Item : [ " << product.productName << " ]\n" << endl;
                                cout << "Current Quantity [Stock] : " << product.quantity << endl;
                                cout << "New Quantity [Stock] : ";
                                cin >> product.quantity;
                                cout << endl;
                                break;
                            }
                            case '4': // Returning to menu
                            {
                                break;
                            }
                            default:
                            {
                                cout << "\n(Error) : Something went wrong try again!\n" << endl;
                                break;
                            }
                            }
                        } while (option != '4');
                    }
                }
                break;
            }
            case '3': // Delete Product
            {
                string selectedItem;
                bool check = false;
                string strCheck;

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
                        cin >> strCheck;
                        cout << endl;

                        transform(strCheck.begin(), strCheck.end(), strCheck.begin(), ::tolower);

                        while (strCheck != "yes" && strCheck != "no")
                        {
                            cout << "(Error) : Invalid Input, Try again \n" << endl;
                            cout << "Yes | No : ";
                            cin >> strCheck;
                            cin.ignore();
                            cout << endl;

                            transform(strCheck.begin(), strCheck.end(), strCheck.begin(), ::tolower);
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

                }
                break;
            }
            case '4': // Returning to menu
            {
                return;
            }
            default:
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
        cout << "Surname: "; getline(cin, surname);
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

    void setUsername(const string& u) { username = u; }
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
void saveAllStores(vector<Store>& stores);
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
void purchaseCart(vector<Store>& stores);
void displayRosterTable(const vector<string>& staff);
void manageRoster(vector<string>& staff);

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

// Displays a clean ASCII table of staff roster
void displayRosterTable(const vector<string>& staff)
{
    const int width = 30;
    cout << '+' << string(width, '-') << '+' << '\n';
    cout << "| " << left << setw(width - 2) << "Current Staff Roster" << " |" << '\n';
    cout << '+' << string(width, '-') << '+' << '\n';
    cout << "| " << left << setw(width - 2) << "Name" << " |" << '\n';
    cout << '+' << string(width, '-') << '+' << '\n';
    for (const auto& s : staff)
    {
        cout << "| " << left << setw(width - 2) << s << " |" << '\n';
    }
    cout << '+' << string(width, '-') << '+' << endl;
}

// Roster management submenu for Admin
void manageRoster(vector<string>& staff)
{
    char choice;
    do
    {
        system("cls");
        printStrongBorder("Roster Management");
        printMenuOption("1. Add Staff");
        printMenuOption("2. Delete Staff");
        printMenuOption("3. Show All Staff Scheduled");
        printMenuOption("4. Roster Staff Functions");
        printMenuOption("5. Back");
        cout << string(30, '#') << endl;
        cout << "Option: "; cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;
        switch (choice)
        {
        case '1':
        {
            cout << "Enter new staff name: ";
            string name; getline(cin, name);
            if (name.empty())
                cout << "(Error) Name cannot be empty." << endl;
            else
            {
                staff.push_back(name);
                cout << "Added: " << name << endl;
            }
            cout << "\nPress any key to continue...";
            _getch();
        } break;
        case '2':
        {
            if (staff.empty()) cout << "(Error) No staff to delete." << endl;
            else
            {
                cout << "Select staff to delete:" << endl;
                for (size_t i = 0; i < staff.size(); ++i)
                    cout << i + 1 << ". " << staff[i] << endl;
                cout << "Enter number: ";
                int num; cin >> num;
                cin.ignore();
                if (num < 1 || num > static_cast<int>(staff.size()))
                    cout << "(Error) Invalid selection." << endl;
                else
                {
                    cout << "Deleted: " << staff[num - 1] << endl;
                    staff.erase(staff.begin() + (num - 1));
                }
            }
            cout << "\nPress any key to continue...";
            _getch();
        } break;
        case '3':
        {
            system("cls");
            displayRosterTable(staff);
            cout << "\nPress any key to continue...";
            _getch();
        } break;
        case '4':
        {
            system("cls");
            printStrongBorder("Roster Staff Functions");
            cout << "Feature coming soon!" << endl;
            cout << "\nPress any key to continue...";
            _getch();
        } break;
        case '5':
            break;
        default:
            cout << "(Error) Invalid input." << endl;
            cout << "\nPress any key to continue...";
            _getch();
        }
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
void saveAllStores(vector<Store>& stores)
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

// Menu for selecting which store to browse
int selectStoreMenu(const vector<Store>& stores)
{
    system("cls");
    printStrongBorder("Select a Store");
    for (size_t i = 0; i < stores.size(); ++i)
        printMenuOption(to_string(i + 1) + ". " + stores[i].storeLocation);
    printMenuOption("4. Back");
    cout << string(30, '#') << endl;
    cout << "Option: ";
    char opt; cin >> opt;
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

// Main menu shown at startup
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
        printMenuOption("4. Exit");
        cout << string(30, '#') << endl;
        cout << "Option: "; cin >> op;
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
                cout << "\nPress any key to continue...";
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
            cout << "Exiting Program!" << endl;
            break;

        default:
            system("cls");
            cout << "(Error) Invalid input." << endl;
        }
    } while (op != '4');
}

// Customer menu after successful login
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
        cout << "Option: "; cin >> o;
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

                // Search products?
                cout << "Search products? (y/n): ";
                char s; cin >> s; cin.ignore();
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

// Admin menu: login then admin panel
void adminMenu(vector<User>& users, vector<Store>& stores)
{
    char c;
    string usr, pwd;
    do
    {
        system("cls"); printStrongBorder("Admin Login");
        printMenuOption("1. Login"); printMenuOption("2. Back");
        cout << string(30, '#') << endl;
        cout << "Option: "; cin >> c; cin.ignore();
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
                vector<string> staff = { "Alice – Manager","Bob   – Cashier","Charlie – Stock" };
                char a;
                do
                {
                    system("cls"); printStrongBorder("Admin Panel");
                    printMenuOption("1. View Products");
                    printMenuOption("2. Manage Roster");
                    printMenuOption("3. Low Stock Alerts");
                    printMenuOption("4. Back");
                    cout << string(30, '#') << endl;
                    cout << "Option: "; cin >> a; cin.ignore();
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
                            cin >> o;
                            cout << endl;
                            cin.ignore();

                            switch (o)
                            {
                            case '1': // Manage products
                            {
                                stores[idx].manageProducts();
                            }
                            case '2': // Return back 
                            {
                                return;
                            }
                            default:
                                cout << "(Error) Invalid input." << endl;
                                _getch();
                                break;
                            }
                        } while (o != '2');
                    } break;
                    case '2': // Manage staff roster
                        manageRoster(staff);
                        break;
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
                    default:
                        cout << "(Error) Invalid input." << endl;
                        _getch();
                    }
                } while (a != '4');
            }
            break;
        case '2': // Back to main menu
            break;
        default:
            system("cls"); cout << "(Error) Invalid input." << endl;
        }
    } while (c != '2');
}

// Customer login and registration menu
void userLogin(vector<User>& users, bool& loggedIn)
{
    char o;
    do
    {
        system("cls"); printStrongBorder("Customer Login");
        printMenuOption("1. Sign In"); printMenuOption("2. Register An Account"); printMenuOption("3. Back");
        cout << string(35, '#') << endl;
        cout << "Option: "; cin >> o; cin.ignore();
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
        default:
            cout << "(Error) Invalid input." << endl;
        }
    } while (o != '3');
}