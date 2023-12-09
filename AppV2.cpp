#include <iostream>
#include <conio.h>              // write setcolor function and gotoxy function. also move the location of dashboard functions with printBanner function
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;
// User Interface
void printBanner();
void startingPage();
void ownerDashboard(string uName);
void salesManDashboard(string uName);
string setcolor(unsigned short color);
void gotoxy(short int,short int);
// Login and Signup
string inputUsername();
string inputPassword();
char inputRole();
bool login(int userCount, string uName, string pass, string usernames[], string passwords[]);
bool signUp(int userCount, string uName, string pass, char role, string usernames[], string passwords[], char roles[], int earnings[], char currency[]);
// Common Options
void printAllBooks(int bookCount, int bookPrice[], int bookQuantity[], char currency, string bookNames[], string authorNames[]);
bool searchBook(string bName, string bookNames[], int bookCount);
// Owner Options
bool addBook(string bName, string auName, int price, int quantity, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int &bookCount);
bool removeBook(string bName, string auName, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount);
void printAllUsers(int userCount, string usernames[], string passwords[], char roles[]);
bool removeUser(string uName, string usernames[], string passwords[], char roles[], int userCount);
bool updateUser(string uName, string pass, char role, string usernames[], string passwords[], char roles[], int userCount);
// Salesman Options
bool placeOrder(string bName, int quantity, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount);
void printAllOrders(int orderCount, string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], char currency);
void clearOrderArrays(string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], int &orderCount);
// Validation
int searchArray(string arr[], string object, int userCount);
int getNum(string);
string getRole(char roleChar);
bool currencyCheck(char currency);
int strToInt(string);
bool checkInt(string);
int countOccurences(string s, char c);
// File Handling
string readField(string line, int field);
void storeCredentials(string usernames[], string passwords[], char roles[], int earnings[], char currency[], int userCount);
void storeBooks(string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount);
void loadCredentials(string usernames[], string passwords[], char roles[], int earnings[], char currency[], int &userCount);
void loadBooks(string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int &bookCount);
// Error Handling
void myGetLine(string &s);
main()
{

    // Data Structures
    // Credentials
    string usernames[100], passwords[100];
    char roles[100];
    int earnings[100];
    char currency[100];
    int userCount = 0;
    int currentUserIdx = 0;
    // Books
    string bookNames[100];
    string authorNames[100];
    int bookCount = 0, bookPrice[100], bookQuantity[100];
    int currentBookIdx = 0;
    // Orders (Only used at runtime)
    string orderBookNames[100];
    string orderBookAuthorNames[100];
    int orderBookQuantity[100];
    int orderBookPrice[100];
    int orderCount = 0;
    // Load data
    loadCredentials(usernames, passwords, roles, earnings, currency, userCount);
    loadBooks(bookNames, authorNames, bookPrice, bookQuantity, bookCount);

    while (true) // Main Loop
    {
        system("cls");
        startingPage();
        int choice = getNum("Your choice (1-3): ");
        if (choice == 3)
        {
            cout << "Exiting..........";
            // Saving data locally
            storeCredentials(usernames, passwords, roles, earnings, currency, userCount);
            storeBooks(bookNames, authorNames, bookPrice, bookQuantity, bookCount);
            return 0;
        }
        else if (choice == 1)
        {
            bool loginPage = true;
            while (loginPage) // Login Page
            {
                system("cls");
                printBanner();
                string uName = inputUsername();
                string pass = inputPassword();
                if (login(userCount, uName, pass, usernames, passwords))
                {
                    // Added this because it would not return to mainPage if I choose option 11.
                    loginPage = false;
                    currentUserIdx = searchArray(usernames, uName, userCount);
                    if (roles[currentUserIdx] == 'a')
                    {
                        while (true) // Owner Dashboard
                        {
                            ownerDashboard(uName);
                            choice = getNum("Your choice (1-12): ");
                            if (choice == 12)
                            { // Logout
                                break;
                            }
                            else if (choice == 1)
                            { // Add Book
                                printBanner();
                                string bName, auName;
                                int price, quantity;
                                cout << "Enter name of the book: ";
                                myGetLine(bName);
                                cout << "Enter name of the author: ";
                                myGetLine(auName);
                                price = getNum("Enter price: ");
                                quantity = getNum("Enter quantity: ");
                                if (addBook(bName, auName, price, quantity, bookNames, authorNames, bookPrice, bookQuantity, bookCount))
                                {
                                    cout << "Book Added to the catalog" << endl;
                                }
                                else
                                {
                                    cout << "Book already exists" << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 2)
                            { // Remove Book
                                printBanner();
                                string bName, auName;
                                cout << "Enter name of the book: ";
                                myGetLine(bName);
                                cout << "Enter name of the author: ";
                                myGetLine(auName);
                                if (removeBook(bName, auName, bookNames, authorNames, bookPrice, bookQuantity, bookCount))
                                {
                                    cout << "Book removed successfully." << endl;
                                }
                                else
                                {
                                    cout << "Book does not exist." << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 3)
                            { // Search Book
                                printBanner();
                                cout << "Enter the name of the book: ";
                                string bName;
                                myGetLine(bName);
                                if (searchBook(bName, bookNames, bookCount))
                                {
                                    int index = searchArray(bookNames, bName, bookCount);
                                    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
                                    cout << left << setw(20) << bookNames[index] << setw(20) << authorNames[index] << setw(0) << currency[currentUserIdx] << setw(20) << bookPrice[index] << setw(20) << bookQuantity[index] << endl;
                                }
                                else
                                {
                                    cout << "Book Not found" << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 4)
                            { // PrintAllBooks
                                printBanner();
                                printAllBooks(bookCount, bookPrice, bookQuantity, currency[currentUserIdx], bookNames, authorNames);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 5)
                            { // Add user
                                printBanner();
                                string uName, pass;
                                cout << "Enter username of the user to add: ";
                                cin >> uName;
                                cout << "Enter password: ";
                                cin >> pass;
                                if (signUp(userCount, uName, pass, 'b', usernames, passwords, roles, earnings, currency))
                                {
                                    userCount++;
                                    cout << "User added successfully." << endl;
                                }
                                else
                                {
                                    cout << "User already exists." << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 6)
                            { // Remove user
                                printBanner();
                                string uName;
                                cout << "Enter username of the user to remove: ";
                                cin >> uName;
                                if (removeUser(uName, usernames, passwords, roles, userCount))
                                {
                                    cout << "User removed successfully." << endl;
                                }
                                else
                                {
                                    cout << "User does not exist." << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 7)
                            { // List all users
                                printBanner();
                                printAllUsers(userCount, usernames, passwords, roles);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 8)
                            { // Update user
                                printBanner();
                                string uName, pass;
                                cout << "Enter username of the user to update: ";
                                cin >> uName;
                                cout << "Enter new password: ";
                                cin >> pass;
                                if (updateUser(uName, pass, 'b', usernames, passwords, roles, userCount))
                                {
                                    cout << "User updated successfully." << endl;
                                }
                                else
                                {
                                    cout << "User does not exist." << endl;
                                }
                            }
                            else if (choice == 9)
                            { // Check total earnings
                                printBanner();
                                int total = 0;
                                for (int i = 0; i < userCount; i++)
                                {
                                    total += earnings[i];
                                }
                                cout << "Total Earnings: " << currency[currentUserIdx] << total << endl;
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 10)
                            {   // Change Currency Type
                                printBanner();
                                cout << "Enter new currency type ('$', '€' or '¥'): ";
                                char newCurrency;
                                cin >> newCurrency;
                                if (currencyCheck(newCurrency))
                                {
                                    currency[currentUserIdx] = newCurrency;
                                    cout << "Currency type changed successfully." << endl;
                                }
                                else
                                {
                                    cout << "Invalid currency type." << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 11)
                            {   // Change Password
                                printBanner();
                                string newPass;
                                cout << "Enter new password: ";
                                cin >> newPass;
                                passwords[currentUserIdx] = newPass;
                                cout << "Password changed successfully." << endl;
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else
                            {
                                // Invalid Input
                                cout << "Invalid Input." << endl;
                                cout << "Press any key to try again..........." << endl;
                                getch();
                            }
                        }
                    }
                    else if (roles[currentUserIdx] == 'b')
                    {
                        while (true) // Salesman Dashboard
                        {
                            salesManDashboard(uName);
                            choice = getNum("Your choice (1-11): ");
                            if (choice == 11)
                            { // Logout
                                break;
                            }
                            if (choice == 1)
                            { // Search Book
                                printBanner();
                                cout << "Enter the name of the book: ";
                                string bName;
                                myGetLine(bName);
                                if (searchBook(bName, bookNames, bookCount))
                                {
                                    int index = searchArray(bookNames, bName, bookCount);
                                    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
                                    cout << left << setw(20) << bookNames[index] << setw(20) << authorNames[index] << setw(0) << currency[currentUserIdx] << setw(20) << bookPrice[index] << setw(20) << bookQuantity[index] << endl;
                                }
                                else
                                {
                                    cout << "Book Not found" << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 2)
                            { // Check availablity of a Book
                                printBanner();
                                cout << "Enter the name of the book: ";
                                string bName;
                                myGetLine(bName);
                                if (searchBook(bName, bookNames, bookCount))
                                {
                                    int index = searchArray(bookNames, bName, bookCount);
                                    if (bookQuantity[index] == 0)
                                    {
                                        cout << bookNames[index] << " is out of stock." << endl;
                                    }
                                    else
                                    {
                                        cout << bookQuantity[index] << " copies of " << bookNames[index] << " are available." << endl;
                                    }
                                }
                                else
                                {
                                    cout << "Book Not found" << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 3)
                            { // List all Books
                                printBanner();
                                printAllBooks(bookCount, bookPrice, bookQuantity, currency[currentUserIdx], bookNames, authorNames);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 4)
                            { // Place Customer Order
                                printBanner();
                                string bName;
                                int quantity;
                                char more = 'y';
                                while (more == 'y')
                                {
                                    cout << "Enter name of the book: ";
                                    myGetLine(bName);
                                    quantity = getNum("Enter quantity: ");
                                    if (placeOrder(bName, quantity, bookNames, bookPrice, bookQuantity, bookCount))
                                    {
                                        orderBookNames[orderCount] = bName;
                                        orderBookQuantity[orderCount] = quantity;
                                        int index = searchArray(bookNames, bName, bookCount);
                                        orderBookPrice[orderCount] = bookPrice[index];
                                        orderBookAuthorNames[orderCount] = authorNames[index];
                                        orderCount++;
                                        cout << "Order placed successfully." << endl;
                                    }
                                    else
                                    {
                                        cout << "Order could not be placed." << endl;
                                    }
                                    cout << "Do you want to place another order? (y/n): ";
                                    cin >> more;
                                }
                            }
                            else if (choice == 5)
                            { // View Customer Order
                                printBanner();
                                printAllOrders(orderCount, orderBookNames, orderBookAuthorNames, orderBookQuantity, orderBookPrice, currency[currentUserIdx]);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 6)
                            { // Finalize Order
                                printBanner();
                                int total = 0;
                                for (int i = 0; i < orderCount; i++)
                                {
                                    total += orderBookPrice[i] * orderBookQuantity[i];
                                }
                                earnings[currentUserIdx] += total;
                                clearOrderArrays(orderBookNames, orderBookAuthorNames, orderBookQuantity, orderBookPrice, orderCount);
                                cout << "Order Finalized. Total amount to be paid is " << currency[currentUserIdx] << total << endl;
                                cout << "Thanks for shopping with us." << endl;
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 7)
                            { // Total Earnings
                                printBanner();
                                cout << "Total Earnings: " << currency[currentUserIdx] << earnings[currentUserIdx] << endl;
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 8)
                            { // Return a Book
                                printBanner();
                                string bName;
                                int quantity;
                                cout << "Enter name of the book: ";
                                myGetLine(bName);
                                quantity = getNum("Enter quantity: ");
                                int index = searchArray(bookNames, bName, bookCount);
                                if (index != -1)
                                {
                                    bookQuantity[index] += quantity;
                                    cout << "Book returned successfully." << endl;
                                }
                                else
                                {
                                    cout << "Book does not exist." << endl;
                                }
                            }
                            else if (choice == 9)
                            { // Change Currency Type
                                printBanner();
                                cout << "Enter new currency type ('$', '£' or '¥'): ";
                                char newCurrency;
                                cin >> newCurrency;
                                if (currencyCheck(newCurrency))
                                {
                                    currency[currentUserIdx] = newCurrency;
                                    cout << "Currency type changed successfully." << endl;
                                }
                                else
                                {
                                    cout << "Invalid currency type." << endl;
                                }
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 10)
                            { // Change Password
                                printBanner();
                                string newPass;
                                cout << "Enter new password: ";
                                cin >> newPass;
                                passwords[currentUserIdx] = newPass;
                                cout << "Password changed successfully." << endl;
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else
                            {
                                // Invalid Input
                                cout << "Invalid Input." << endl;
                                cout << "Press any key to try again..........." << endl;
                                getch();
                            }
                        }
                    }
                }
                else
                {
                    // Invalid Credentials
                    cout << "Invalid Credentials." << endl;
                    cout << "Press any key to try again..........." << endl;
                    getch();
                }
            }
        }
        else if (choice == 2)
        { // Sign Up
            while (true)
            {
                system("cls");
                printBanner();
                string uName = inputUsername();
                string pass = inputPassword();
                char role = inputRole();
                if (role == 'a' && countOccurences(roles, 'a') == 1)
                {
                    cout << "Only one admin is allowed." << endl;
                    cout << "Press any key to try again...........";
                    getch();
                    continue;
                }
                if (signUp(userCount, uName, pass, role, usernames, passwords, roles, earnings, currency))
                {
                    userCount++;
                    cout << "You have been signed up successfully." << endl;
                    cout << "Press any key to continue.......";
                    getch();
                    break;
                }
                else
                {
                    cout << "Username Already exists." << endl;
                    cout << "Press any key to try again...........";
                    getch();
                }
            }
        }
        else
        {
            // Invalid Input
            cout << "Invalid Input." << endl;
            cout << "Press any key to try again..........." << endl;
            getch();
        }
    }
}
                                    // Start of function definitions
                                    // User Interface function Start
void printBanner()
{
    system("cls");
    cout << "__________________________________________________________________________________" << endl;
    cout << "|   ,   ,      ____              _        _                                       |" << endl;
    cout << "|  /////|     | __ )  ___   ___ | | _____| |__   ___  _ __                        |" << endl;
    cout << "| ///// |     |  _ \\ / _ \\ / _ \\| |/ / __| '_ \\ / _ \\| '_ \\                       |" << endl;
    cout << "||~~~|  |     | |_) | (_) | (_) |   <\\__ \\ | | | (_) | |_) |                      |" << endl;
    cout << "||===|  |     |____/ \\___/ \\___/|_|\\_\\___/_| |_|\\___/| .__/                       |" << endl;
    cout << "||   |  |                                            |_|                          |" << endl;
    cout << "||   |  |                                                                         |" << endl;
    cout << "||   | /                                                                          |" << endl;
    cout << "||===|/                                                                           |" << endl;
    cout << "|'---'                                                                            |" << endl;
    cout << "|_________________________________________________________________________________|" << endl;
    cout << endl;
}
void startingPage()
{
    printBanner();
    cout << "Welcome" << endl;
    cout << "Choose one of the following......" << endl;
    cout << "1. Login" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Exit" << endl;
}
void ownerDashboard(string uName)
{
    printBanner();
    cout << "Logged in as " << uName << " (Admin)" << endl;
    cout << "Choose one of the following: " << endl;
    cout << "1. Add a new Book" << endl;
    cout << "2. Remove a Book" << endl;
    cout << "3. Search for a Book" << endl;
    cout << "4. List All Books" << endl;
    cout << "5. Add a new user" << endl;
    cout << "6. Remove an existing user" << endl;
    cout << "7. List All users" << endl;
    cout << "8. Update user information" << endl;
    cout << "9. Check total earnings" << endl;
    cout << "10. Change Currency Type" << endl;
    cout << "11. Change Password" << endl;
    cout << "12. Logout" << endl;
}
void salesManDashboard(string uName)
{
    printBanner();
    cout << "Logged in as " << uName << " (Salesman)" << endl;
    cout << "Choose one of the following: " << endl;
    cout << "1. Search for a Book" << endl;
    cout << "2. Check availablity of a Book" << endl;
    cout << "3. List all Books" << endl;
    cout << "4. Place Customer Order" << endl;
    cout << "5. View Customer Order" << endl;
    cout << "6. Finalize Order" << endl;
    cout << "7. Total Earnings" << endl;
    cout << "8. Return a Book" << endl;
    cout << "9. Change Currency Type" << endl;
    cout << "10. Change Password" << endl;
    cout << "11. Logout" << endl;
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
                                    // User Interface function End
                                    // Login/Signup function Start
string inputUsername()
{
    string username;
    cout << "Username: ";
    cin >> username;
    return username;
}
string inputPassword()
{
    string password;
    cout << "Password: ";
    cin >> password;
    return password;
}
char inputRole()
{
    while (true)
    {
        char role;
        cout << "Choose Role ('a' for Admin and 'b' for Salesman): ";
        cin >> role;
        if (role == 'a' || role == 'b')
        {
            return role;
        }
        else
        {
            cout << "Invalid Input." << endl;
            cout << "Press any key to try again..................." << endl;
            getch();
        }
    }
}
bool login(int userCount, string uName, string pass, string usernames[], string passwords[])
{

    int index = searchArray(usernames, uName, userCount);
    if (index == -1)
    {
        return false;
    }
    if (uName == usernames[index] && pass == passwords[index])
    {
        return true;
    }
    return false;
}
bool signUp(int userCount, string uName, string pass, char role, string usernames[], string passwords[], char roles[], int earnings[], char currency[])
{
    bool isSignedUp = false;
    int index = searchArray(usernames, uName, userCount);
    if (index == -1)
    {
        usernames[userCount] = uName;
        passwords[userCount] = pass;
        roles[userCount] = role;
        earnings[userCount] = 0;
        currency[userCount] = '$';
        isSignedUp = true;
    }
    return isSignedUp;
}
                                    // Login/Signup function End
                                    // Common Options Start
void printAllBooks(int bookCount, int bookPrice[], int bookQuantity[], char currency, string bookNames[], string authorNames[])
{
    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
    for (int i = 0; i < bookCount; i++)
    {
        if (bookNames[i] == "")
        {
            continue;
        }
        cout << left << setw(20) << bookNames[i] << setw(20) << authorNames[i] << setw(0) << currency << setw(20) << bookPrice[i] << setw(20) << bookQuantity[i] << endl;
    }
}
bool searchBook(string bName, string bookNames[], int bookCount)
{
    int index = searchArray(bookNames, bName, bookCount);
    if (index != -1)
    {
        return true;
    }
    return false;
}
                                    // Common Options End
                                    // Owner Options Start
bool addBook(string bName, string auName, int price, int quantity, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int &bookCount)
{
    int index = searchArray(bookNames, bName, bookCount);
    if (index == -1)
    {
        authorNames[bookCount] = auName;
        bookNames[bookCount] = bName;
        bookPrice[bookCount] = price;
        bookQuantity[bookCount] = quantity;
        bookCount++;
        return true;
    }
    else
    {
        bookQuantity[index] += quantity;
        return false;
    }
}
bool removeBook(string bName, string auName, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount)
{ // Book might exist but it will still say that it does not if author doesn't match
    int index = searchArray(bookNames, bName, bookCount);
    if (index != -1)
    {
        if (authorNames[index] == auName)
        {
            bookNames[index] = "";
            authorNames[index] = "";
            bookPrice[index] = 0;
            bookQuantity[index] = 0;
            return true;
        }
    }
    return false;
}
void printAllUsers(int userCount, string usernames[], string passwords[], char roles[])
{
    cout << left << setw(20) << "Username" << setw(20) << "Password" << setw(20) << "Role" << endl;
    for (int i = 0; i < userCount; i++)
    {
        if (usernames[i] == "")
        {
            continue;
        }
        cout << left << setw(20) << usernames[i] << setw(20) << passwords[i] << setw(20) << getRole(roles[i]) << endl;
    }
}
bool removeUser(string uName, string usernames[], string passwords[], char roles[], int userCount)
{
    int index = searchArray(usernames, uName, userCount);
    if (index != -1)
    {
        usernames[index] = "";
        passwords[index] = "";
        roles[index] = ' ';
        return true;
    }
    return false;
}
bool updateUser(string uName, string pass, char role, string usernames[], string passwords[], char roles[], int userCount)
{
    int index = searchArray(usernames, uName, userCount);
    if (index != -1)
    {
        usernames[index] = uName;
        passwords[index] = pass;
        roles[index] = role;
        return true;
    }
    return false;
}

                                    // Owner Options End
                                    // Salesman Options Start

bool placeOrder(string bName, int quantity, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount)
{
    int index = searchArray(bookNames, bName, bookCount);
    if (index != -1)
    {
        if (bookQuantity[index] >= quantity)
        {
            bookQuantity[index] -= quantity;
            return true;
        }
    }
    return false;
}
void printAllOrders(int orderCount, string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], char currency)
{
    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
    for (int i = 0; i < orderCount; i++)
    {
        if (orderBookNames[i] == "")
        {
            continue;
        }
        cout << left << setw(20) << orderBookNames[i] << setw(20) << orderBookAuthorNames[i] << setw(0) << currency << setw(20) << orderBookPrice[i] << setw(20) << orderBookQuantity[i] << endl;
    }
}
void clearOrderArrays(string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], int &orderCount)
{
    for (int i = 0; i < orderCount; i++)
    {
        orderBookNames[i] = "";
        orderBookAuthorNames[i] = "";
        orderBookQuantity[i] = 0;
        orderBookPrice[i] = 0;
    }
    orderCount = 0;
}
                                    // Salesman Options End
                                    // Validation Functions Start

// If object is not in array it will return -1, that can be used to add a condition that it does not exist.
int searchArray(string arr[], string object, int arrLength)
{
    for (int i = 0; i < arrLength; i++)
    {
        if (arr[i] == object)
        {
            return i;
        }
    }
    return -1;
}
int getNum(string prompt)
{
    string num;
    while (true)
    {
        cout << prompt;
        cin >> num;
        if (checkInt(num))
        {
            return strToInt(num);
        }
        else
        {
            cout << "Invalid Input." << endl;
            cout << "Press any key to try again..................." << endl;
            getch();
        }
    }
}
string getRole(char roleChar)
{
    if (roleChar == 'a')
    {
        return "Admin";
    }
    else if (roleChar == 'b')
    {
        return "Salesman";
    }
    else
    {
        return "Unknown";
    }
}
bool currencyCheck(char currency)
{
    if (currency == '$' || currency == '£' || currency == '¥')
    {
        return true;
    }
    return false;
}
int strToInt(string s)
{

    int result = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        result = result * 10 + (s[i] - '0');
    }
    return result;
}
bool checkInt(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            return false;
        }
    }
    return true;
}
int countOccurences(string s, char c)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == c)
        {
            count++;
        }
    }
    return count;
}
                                    // Validation Functions End
                                    // File Handling Functions Start
string readField(string line, int field)
{
    int count = 0;
    string result = "";
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] != ',')
        {
            result += line[i];
        }
        else
        {
            count++;
            if (count == field)
            {
                return result;
            }
            result = "";
        }
    }
}
void storeCredentials(string usernames[], string passwords[], char roles[], int earnings[], char currency[], int userCount)
{
    fstream f;
    f.open("credentials.txt", ios::out);
    for (int i = 0; i < userCount; i++)
    {
        f << usernames[i] << ',' << passwords[i] << "," << roles[i] << "," << earnings[i] << "," << currency[i];
        if (i != userCount - 1)
        {
            f << endl;
        }
    }
    f.close();
}
void storeBooks(string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount)
{
    fstream f;
    f.open("books.txt", ios::out);
    for (int i = 0; i < bookCount; i++)
    {
        f << bookNames[i] << "," << authorNames[i] << "," << bookPrice[i] << "," << bookQuantity[i] << ",";
        if (i != bookCount - 1)
        {
            f << endl;
        }
    }
    f.close();
}
void storeOrders(string orderBookNames[], string orderBookAuthorNames[], int orderBookPrice[], int orderBookQuantity[], int orderCount)
{
    fstream f;
    f.open("orders.txt", ios::out);
    for (int i = 0; i < orderCount; i++)
    {
        f << orderBookNames[i] << "," << orderBookAuthorNames[i] << "," << orderBookPrice[i] << "," << orderBookQuantity[i];
        if (i != orderCount - 1)
        {
            f << endl;
        }
    }
    f.close();
}
void loadCredentials(string usernames[], string passwords[], char roles[], int earnings[], char currency[], int &userCount)
{
    string line;
    fstream f;
    f.open("credentials.txt", ios::in);
    int i = 0;
    while (!f.eof())
    {
        getline(f, line);
        usernames[i] = readField(line, 1);
        passwords[i] = readField(line, 2);
        roles[i] = readField(line, 3)[0];
        earnings[i] = strToInt(readField(line, 4));
        currency[i] = readField(line, 5)[0];
        i++;
    }
    userCount = i;
}
void loadBooks(string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int &bookCount)
{
    string line;
    fstream f;
    f.open("books.txt", ios::in);
    int i = 0;
    while (!f.eof())
    {
        getline(f, line);
        bookNames[i] = readField(line, 1);
        authorNames[i] = readField(line, 2);
        bookPrice[i] = strToInt(readField(line, 3));
        bookQuantity[i] = strToInt(readField(line, 4));
        i++;
    }
    bookCount = i;
}
void loadOrders(string orderBookNames[], string orderBookAuthorNames[], int orderBookPrice[], int orderBookQuantity[], int &orderCount)
{
    string line;
    fstream f;
    f.open("orders.txt", ios::in);
    int i = 0;
    while (!f.eof())
    {
        getline(f, line);
        orderBookNames[i] = readField(line, 1);
        orderBookAuthorNames[i] = readField(line, 2);
        orderBookPrice[i] = strToInt(readField(line, 3));
        orderBookQuantity[i] = strToInt(readField(line, 4));
        i++;
    }
    orderCount = i;
}
                                    // File Handling Functions End
                                    // Error Handling Functions Start
void myGetLine(string &s)
{
    cin.clear();
    cin.sync();
    getline(cin >> ws, s);
}