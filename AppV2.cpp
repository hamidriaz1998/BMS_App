#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <windows.h>
using namespace std;
// User Interface
void printBanner(int X, int &Y);
void startingPage(int X, int &Y);
void ownerDashboard(string uName, int X, int &Y);
void salesManDashboard(string uName, int X, int &Y);
string setcolor(unsigned short color);
void gotoxy(short int, short int);
void mygotoxy(int X, int &Y);
int getScreenWidth();
// Login and Signup
string inputUsername(int X, int &Y);
string inputPassword(int X, int &Y);
char inputRole(int X, int &Y);
bool login(int userCount, string uName, string pass, string usernames[], string passwords[]);
bool signUp(int userCount, string uName, string pass, char role, string usernames[], string passwords[], char roles[], int earnings[], string currency[]);
// Common Options
void printAllBooks(int bookCount, int bookPrice[], int bookQuantity[], string currency, string bookNames[], string authorNames[], int X, int &Y);
bool searchBook(string bName, string bookNames[], int bookCount);
// Owner Options
bool addBook(string bName, string auName, int price, int quantity, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int &bookCount);
bool removeBook(string bName, string auName, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount);
bool incrementQuantity(string bName, int quantity, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount);
bool changePrice(string bName, int price, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount);
void printAllUsers(int userCount, string usernames[], string passwords[], char roles[], int earnings[], string currency[], int X, int &Y);
bool removeUser(string uName, string usernames[], string passwords[], char roles[], int userCount);
bool updateUser(string uName, string pass, char role, string usernames[], string passwords[], char roles[], int userCount);
// Salesman Options
bool placeOrder(string bName, int quantity, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount);
void printAllOrders(int orderCount, string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], string currency, int X, int &Y);
void clearOrderArrays(string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], int &orderCount);
// Validation
int searchArray(string arr[], string object, int userCount);
int getNum(string, int, int &);
string getRole(char roleChar);
string getValidatedInput(string prompt, int X, int &Y);
bool currencyCheck(string currency);
int strToInt(string);
bool checkInt(string);
bool checkComma(string);
int countOccurences(string s, char c);
// File Handling
string readField(string line, int field);
void storeCredentials(string usernames[], string passwords[], char roles[], int earnings[], string currency[], int userCount);
void storeBooks(string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount);
void loadCredentials(string usernames[], string passwords[], char roles[], int earnings[], string currency[], int &userCount);
void loadBooks(string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int &bookCount);
// Error Handling
void myGetLine(string &s);
// Colors
const int black = 0, blue = 1, green = 2, cyan = 3, red = 4, magenta = 5, brown = 6, lightwhite = 7, darkwhite = 8, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, lightmagenta = 13, yellow = 14, white = 15;
main()
{

    // Data Structures
    // Credentials
    string usernames[100], passwords[100];
    char roles[100];
    int earnings[100];
    string currency[100];
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
    // Coordinates for printing
    int X = (getScreenWidth() - 82) / 2; // X coordinate for printing at center of screen
    int Y = 0;

    while (true) // Main Loop
    {
        system("cls");
        startingPage(X, Y);
        int choice = getNum("Your choice (1-3): ", X, Y);
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
                printBanner(X, Y);
                string uName = inputUsername(X, Y);
                string pass = inputPassword(X, Y);
                if (login(userCount, uName, pass, usernames, passwords))
                {
                    // Added this because it would not return to mainPage if I choose option 11.
                    loginPage = false;
                    currentUserIdx = searchArray(usernames, uName, userCount);
                    if (roles[currentUserIdx] == 'a')
                    {
                        while (true) // Owner Dashboard
                        {
                            ownerDashboard(uName, X, Y);
                            choice = getNum("Your choice (1-14): ", X, Y);
                            if (choice == 14)
                            { // Logout
                                break;
                            }
                            else if (choice == 1)
                            { // Add Book
                                printBanner(X, Y);
                                string bName, auName;
                                int price, quantity;
                                bName = getValidatedInput("Enter name of the book: ", X, Y);
                                auName = getValidatedInput("Enter name of the author: ", X, Y);
                                price = getNum("Enter price: ", X, Y);
                                quantity = getNum("Enter quantity: ", X, Y);
                                if (addBook(bName, auName, price, quantity, bookNames, authorNames, bookPrice, bookQuantity, bookCount))
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Book Added to the catalog" << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book already exists" << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 2)
                            { // Remove Book
                                printBanner(X, Y);
                                string bName, auName;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter name of the book: ";
                                setcolor(white);
                                myGetLine(bName);
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter name of the author: ";
                                setcolor(white);
                                myGetLine(auName);
                                if (removeBook(bName, auName, bookNames, authorNames, bookPrice, bookQuantity, bookCount))
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Book removed successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book does not exist." << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 3)
                            { // Search Book
                                printBanner(X, Y);
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter the name of the book: ";
                                setcolor(white);
                                string bName;
                                myGetLine(bName);
                                if (searchBook(bName, bookNames, bookCount))
                                {
                                    int index = searchArray(bookNames, bName, bookCount);
                                    mygotoxy(X, Y);
                                    setcolor(green);
                                    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
                                    setcolor(white);
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << left << setw(20) << bookNames[index] << setw(20) << authorNames[index] << setw(0) << currency[currentUserIdx] << setw(20) << bookPrice[index] << setw(20) << bookQuantity[index] << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book Not found" << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 4)
                            { // PrintAllBooks
                                printBanner(X, Y);
                                printAllBooks(bookCount, bookPrice, bookQuantity, currency[currentUserIdx], bookNames, authorNames, X, Y);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 5)
                            {
                                // Change Price
                                printBanner(X, Y);
                                string bName;
                                int price;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter name of the book: ";
                                setcolor(white);
                                myGetLine(bName);
                                price = getNum("Enter new price: ", X, Y);
                                if (changePrice(bName, price, bookNames, bookPrice, bookQuantity, bookCount))
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Price changed successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book does not exist." << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 6)
                            {
                                // Increment Quantity
                                printBanner(X, Y);
                                string bName;
                                int quantity;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter name of the book: ";
                                setcolor(white);
                                myGetLine(bName);
                                quantity = getNum("Enter quantity to add: ", X, Y);
                                if (incrementQuantity(bName, quantity, bookNames, bookPrice, bookQuantity, bookCount))
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Quantity incremented successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book does not exist." << endl;
                                    setcolor(white);
                                }
                            }
                            else if (choice == 7)
                            { // Add user
                                printBanner(X, Y);
                                string uName, pass;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter username of the user to add: ";
                                setcolor(white);
                                cin >> uName;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter password: ";
                                cin >> pass;
                                setcolor(white);
                                if (signUp(userCount, uName, pass, 'b', usernames, passwords, roles, earnings, currency))
                                {
                                    userCount++;
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "User added successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "User already exists." << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 8)
                            { // Remove user
                                printBanner(X, Y);
                                string uName;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter username of the user to remove: ";
                                cin >> uName;
                                setcolor(white);
                                if (removeUser(uName, usernames, passwords, roles, userCount))
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "User removed successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "User does not exist." << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 9)
                            { // List all users
                                printBanner(X, Y);
                                printAllUsers(userCount, usernames, passwords, roles, earnings, currency, X, Y);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 10)
                            { // Update user
                                printBanner(X, Y);
                                string uName, pass;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter username of the user to update: ";
                                cin >> uName;
                                setcolor(white);
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter new password: ";
                                cin >> pass;
                                setcolor(white);
                                if (updateUser(uName, pass, 'b', usernames, passwords, roles, userCount))
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "User updated successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "User does not exist." << endl;
                                    setcolor(white);
                                }
                            }
                            else if (choice == 11)
                            { // Check total earnings
                                printBanner(X, Y);
                                int total = 0;
                                for (int i = 0; i < userCount; i++)
                                {
                                    total += earnings[i];
                                }
                                mygotoxy(X, Y);
                                setcolor(lightmagenta);
                                cout << "Total Earnings: " << currency[currentUserIdx] << total << endl;
                                setcolor(white);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 12)
                            { // Change Currency Type
                                printBanner(X, Y);
                                gotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter new currency type ('$' or '\x9C'): ";
                                string newCurrency;
                                cin >> newCurrency;
                                setcolor(white);
                                if (currencyCheck(newCurrency))
                                {
                                    currency[currentUserIdx] = newCurrency;
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Currency type changed successfully.       " << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Invalid currency type.                 " << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 13)
                            { // Change Password
                                printBanner(X, Y);
                                string newPass;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter new password: ";
                                cin >> newPass;
                                setcolor(white);
                                passwords[currentUserIdx] = newPass;
                                mygotoxy(X, Y);
                                setcolor(lightgreen);
                                cout << "Password changed successfully." << endl;
                                setcolor(white);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else
                            {
                                // Invalid Input
                                mygotoxy(X, Y);
                                setcolor(lightred);
                                cout << "Invalid Input." << endl;
                                setcolor(white);
                                mygotoxy(X, Y);
                                cout << "Press any key to try again..........." << endl;
                                getch();
                            }
                        }
                    }
                    else if (roles[currentUserIdx] == 'b')
                    {
                        while (true) // Salesman Dashboard
                        {
                            salesManDashboard(uName, X, Y);
                            choice = getNum("Your choice (1-11): ", X, Y);
                            if (choice == 11)
                            { // Logout
                                break;
                            }
                            if (choice == 1)
                            { // Search Book
                                printBanner(X, Y);
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter the name of the book: ";
                                setcolor(white);
                                string bName;
                                myGetLine(bName);
                                if (searchBook(bName, bookNames, bookCount))
                                {
                                    int index = searchArray(bookNames, bName, bookCount);
                                    mygotoxy(X, Y);
                                    setcolor(green);
                                    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
                                    setcolor(white);
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << left << setw(20) << bookNames[index] << setw(20) << authorNames[index] << setw(0) << currency[currentUserIdx] << setw(20) << bookPrice[index] << setw(20) << bookQuantity[index] << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book Not found" << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 2)
                            { // Check availablity of a Book
                                printBanner(X, Y);
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter the name of the book: ";
                                setcolor(white);
                                string bName;
                                myGetLine(bName);
                                if (searchBook(bName, bookNames, bookCount))
                                {
                                    int index = searchArray(bookNames, bName, bookCount);
                                    if (bookQuantity[index] == 0)
                                    {
                                        mygotoxy(X, Y);
                                        setcolor(lightred);
                                        cout << bookNames[index] << " is out of stock." << endl;
                                        setcolor(white);
                                    }
                                    else
                                    {
                                        mygotoxy(X, Y);
                                        setcolor(lightgreen);
                                        cout << bookQuantity[index] << " copies of " << bookNames[index] << " are available." << endl;
                                        setcolor(white);
                                    }
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book Not found" << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 3)
                            { // List all Books
                                printBanner(X, Y);
                                printAllBooks(bookCount, bookPrice, bookQuantity, currency[currentUserIdx], bookNames, authorNames, X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 4)
                            { // Place Customer Order
                                printBanner(X, Y);
                                string bName;
                                int quantity;
                                char more = 'y';
                                while (more == 'y')
                                {
                                    mygotoxy(X, Y);
                                    setcolor(yellow);
                                    cout << "Enter name of the book: ";
                                    setcolor(white);
                                    myGetLine(bName);
                                    setcolor(yellow);
                                    quantity = getNum("Enter quantity: ", X, Y);
                                    setcolor(white);
                                    if (placeOrder(bName, quantity, bookNames, bookPrice, bookQuantity, bookCount))
                                    {
                                        orderBookNames[orderCount] = bName;
                                        orderBookQuantity[orderCount] = quantity;
                                        int index = searchArray(bookNames, bName, bookCount);
                                        orderBookPrice[orderCount] = bookPrice[index];
                                        orderBookAuthorNames[orderCount] = authorNames[index];
                                        orderCount++;
                                        mygotoxy(X, Y);
                                        setcolor(lightgreen);
                                        cout << "Order placed successfully." << endl;
                                        setcolor(white);
                                    }
                                    else
                                    {
                                        mygotoxy(X, Y);
                                        setcolor(lightred);
                                        cout << "Order could not be placed." << endl;
                                        setcolor(white);
                                    }
                                    mygotoxy(X, Y);
                                    setcolor(yellow);
                                    cout << "Do you want to place another order? (y/n): ";
                                    cin >> more;
                                    setcolor(white);
                                }
                            }
                            else if (choice == 5)
                            { // View Customer Order
                                printBanner(X, Y);
                                printAllOrders(orderCount, orderBookNames, orderBookAuthorNames, orderBookQuantity, orderBookPrice, currency[currentUserIdx], X, Y);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 6)
                            { // Finalize Order
                                printBanner(X, Y);
                                int total = 0;
                                for (int i = 0; i < orderCount; i++)
                                {
                                    total += orderBookPrice[i] * orderBookQuantity[i];
                                }
                                earnings[currentUserIdx] += total;
                                clearOrderArrays(orderBookNames, orderBookAuthorNames, orderBookQuantity, orderBookPrice, orderCount);
                                mygotoxy(X, Y);
                                setcolor(lightgreen);
                                cout << "Order Finalized. Total amount to be paid is " << currency[currentUserIdx] << total << endl;
                                mygotoxy(X, Y);
                                cout << "Thanks for shopping with us." << endl;
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                mygotoxy(X, Y);
                                setcolor(white);
                                getch();
                            }
                            else if (choice == 7)
                            { // Total Earnings
                                printBanner(X, Y);
                                mygotoxy(X, Y);
                                setcolor(lightmagenta);
                                cout << "Total Earnings: " << currency[currentUserIdx] << earnings[currentUserIdx] << endl;
                                setcolor(white);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 8)
                            { // Return a Book
                                printBanner(X, Y);
                                string bName;
                                int quantity;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter name of the book: ";
                                setcolor(white);
                                myGetLine(bName);
                                quantity = getNum("Enter quantity: ", X, Y);
                                int index = searchArray(bookNames, bName, bookCount);
                                if (index != -1)
                                {
                                    bookQuantity[index] += quantity;
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Book returned successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Book does not exist." << endl;
                                    setcolor(white);
                                }
                            }
                            else if (choice == 9)
                            { // Change Currency Type
                                printBanner(X, Y);
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter new currency type ('$' or '\x9C'): ";
                                string newCurrency;
                                cin >> newCurrency;
                                setcolor(white);
                                if (currencyCheck(newCurrency))
                                {
                                    currency[currentUserIdx] = newCurrency;
                                    mygotoxy(X, Y);
                                    setcolor(lightgreen);
                                    cout << "Currency type changed successfully." << endl;
                                    setcolor(white);
                                }
                                else
                                {
                                    mygotoxy(X, Y);
                                    setcolor(lightred);
                                    cout << "Invalid currency type." << endl;
                                    setcolor(white);
                                }
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else if (choice == 10)
                            { // Change Password
                                printBanner(X, Y);
                                string newPass;
                                mygotoxy(X, Y);
                                setcolor(yellow);
                                cout << "Enter new password: ";
                                cin >> newPass;
                                setcolor(white);
                                passwords[currentUserIdx] = newPass;
                                mygotoxy(X, Y);
                                setcolor(lightgreen);
                                cout << "Password changed successfully." << endl;
                                setcolor(white);
                                mygotoxy(X, Y);
                                cout << "Press any key to return to Dashboard................";
                                getch();
                            }
                            else
                            {
                                // Invalid Input
                                mygotoxy(X, Y);
                                setcolor(lightred);
                                cout << "Invalid Input." << endl;
                                setcolor(white);
                                mygotoxy(X, Y);
                                cout << "Press any key to try again..........." << endl;
                                getch();
                            }
                        }
                    }
                }
                else
                {
                    // Invalid Credentials
                    mygotoxy(X, Y);
                    setcolor(lightred);
                    cout << "Invalid Credentials." << endl;
                    setcolor(white);
                    mygotoxy(X, Y);
                    cout << "Press any key to try again..........." << endl;
                    getch();
                }
            }
        }
        else if (choice == 2)
        { // Sign Up
            while (true)
            {
                printBanner(X, Y);
                string uName = inputUsername(X, Y);
                string pass = inputPassword(X, Y);
                char role = inputRole(X, Y);
                if (role == 'a' && countOccurences(roles, 'a') == 1)
                {
                    mygotoxy(X, Y);
                    setcolor(lightred);
                    cout << "Only one admin is allowed." << endl;
                    setcolor(white);
                    mygotoxy(X, Y);
                    cout << "Press any key to try again...........";
                    getch();
                    continue;
                }
                if (signUp(userCount, uName, pass, role, usernames, passwords, roles, earnings, currency))
                {
                    userCount++;
                    mygotoxy(X, Y);
                    setcolor(lightgreen);
                    cout << "You have been signed up successfully." << endl;
                    setcolor(white);
                    mygotoxy(X, Y);
                    cout << "Press any key to continue.......";
                    getch();
                    break;
                }
                else
                {
                    mygotoxy(X, Y);
                    setcolor(lightred);
                    cout << "Username Already exists." << endl;
                    setcolor(white);
                    mygotoxy(X, Y);
                    cout << "Press any key to try again...........";
                    getch();
                }
            }
        }
        else
        {
            // Invalid Input
            mygotoxy(X, Y);
            setcolor(lightred);
            cout << "Invalid Input." << endl;
            setcolor(white);
            mygotoxy(X, Y);
            cout << "Press any key to try again..........." << endl;
            getch();
        }
    }
}
// Start of function definitions
// User Interface function Start
void printBanner(int X, int &Y)
{
    setcolor(cyan);
    system("cls");
    Y = 0;
    mygotoxy(X, Y);
    cout << "__________________________________________________________________________________";
    mygotoxy(X, Y);
    cout << "|   ,   ,      ____              _        _                                       |";
    mygotoxy(X, Y);
    cout << "|  /////|     | __ )  ___   ___ | | _____| |__   ___  _ __                        |";
    mygotoxy(X, Y);
    cout << "| ///// |     |  _ \\ / _ \\ / _ \\| |/ / __| '_ \\ / _ \\| '_ \\                       |";
    mygotoxy(X, Y);
    cout << "||~~~|  |     | |_) | (_) | (_) |   <\\__ \\ | | | (_) | |_) |                      |";
    mygotoxy(X, Y);
    cout << "||===|  |     |____/ \\___/ \\___/|_|\\_\\___/_| |_|\\___/| .__/                       |";
    mygotoxy(X, Y);
    cout << "||   |  |                                            |_|                          |";
    mygotoxy(X, Y);
    cout << "||   |  |                                                                         |";
    mygotoxy(X, Y);
    cout << "||   | /                                                                          |";
    mygotoxy(X, Y);
    cout << "||===|/                                                                           |";
    mygotoxy(X, Y);
    cout << "|'---'                                                                            |";
    mygotoxy(X, Y);
    cout << "|_________________________________________________________________________________|";
    setcolor(white);
    Y++;
}
void startingPage(int X, int &Y)
{
    printBanner(X, Y);
    setcolor(lightblue);
    mygotoxy(X, Y);
    cout << "Welcome" << endl;
    mygotoxy(X, Y);
    cout << "Choose one of the following......" << endl;
    mygotoxy(X, Y);
    cout << "1. Login" << endl;
    mygotoxy(X, Y);
    cout << "2. Sign Up" << endl;
    mygotoxy(X, Y);
    cout << "3. Exit" << endl;
    setcolor(white);
    Y++;
}
void ownerDashboard(string uName, int X, int &Y)
{
    printBanner(X, Y);
    setcolor(lightblue);
    mygotoxy(X, Y);
    cout << "Logged in as " << uName << " (Admin)" << endl;
    mygotoxy(X, Y);
    cout << "Choose one of the following: " << endl;
    mygotoxy(X, Y);
    cout << "1. Add a new Book" << endl;
    mygotoxy(X, Y);
    cout << "2. Remove a Book" << endl;
    mygotoxy(X, Y);
    cout << "3. Search for a Book" << endl;
    mygotoxy(X, Y);
    cout << "4. List All Books" << endl;
    mygotoxy(X, Y);
    cout << "5. Change Book Price" << endl;
    mygotoxy(X, Y);
    cout << "6. Change Book Quantity" << endl;
    mygotoxy(X, Y);
    cout << "7. Add a new user" << endl;
    mygotoxy(X, Y);
    cout << "8. Remove an existing user" << endl;
    mygotoxy(X, Y);
    cout << "9. List All users" << endl;
    mygotoxy(X, Y);
    cout << "10. Update user information" << endl;
    mygotoxy(X, Y);
    cout << "11. Check total earnings" << endl;
    mygotoxy(X, Y);
    cout << "12. Change Currency Type" << endl;
    mygotoxy(X, Y);
    cout << "13. Change Password" << endl;
    mygotoxy(X, Y);
    cout << "14. Logout" << endl;
    setcolor(white);
    Y++;
}
void salesManDashboard(string uName, int X, int &Y)
{
    printBanner(X, Y);
    setcolor(lightblue);
    mygotoxy(X, Y);
    cout << "Logged in as " << uName << " (Salesman)" << endl;
    mygotoxy(X, Y);
    cout << "Choose one of the following: " << endl;
    mygotoxy(X, Y);
    cout << "1. Search for a Book" << endl;
    mygotoxy(X, Y);
    cout << "2. Check availablity of a Book" << endl;
    mygotoxy(X, Y);
    cout << "3. List all Books" << endl;
    mygotoxy(X, Y);
    cout << "4. Place Customer Order" << endl;
    mygotoxy(X, Y);
    cout << "5. View Customer Order" << endl;
    mygotoxy(X, Y);
    cout << "6. Finalize Order" << endl;
    mygotoxy(X, Y);
    cout << "7. Total Earnings" << endl;
    mygotoxy(X, Y);
    cout << "8. Return a Book" << endl;
    mygotoxy(X, Y);
    cout << "9. Change Currency Type" << endl;
    mygotoxy(X, Y);
    cout << "10. Change Password" << endl;
    mygotoxy(X, Y);
    cout << "11. Logout" << endl;
    setcolor(white);
    Y++;
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}
void gotoxy(short int x, short int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void mygotoxy(int X, int &Y)
{
    gotoxy(X, Y);
    Y++;
}
int getScreenWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    return columns;
}
// User Interface function End
// Login/Signup function Start
string inputUsername(int X, int &Y)
{
    string username;
    username = getValidatedInput("Username: ", X, Y);
    return username;
}
string inputPassword(int X, int &Y)
{
    string password;
    while (true)
    {
        mygotoxy(X, Y);
        setcolor(yellow);
        cout << "Password: ";
        cin >> password;
        setcolor(white);
        if (password.length() < 4)
        {
            mygotoxy(X, Y);
            setcolor(red);
            cout << "Password must be atleast 4 characters long." << endl;
            setcolor(white);
            mygotoxy(X, Y);
            cout << "Press any key to try again..................." << endl;
            getch();
        }
        else if (checkComma(password))
        {
            mygotoxy(X, Y);
            setcolor(red);
            cout << "Password cannot contain comma (,)" << endl;
            setcolor(white);
            mygotoxy(X, Y);
            cout << "Press any key to try again..................." << endl;
            getch();
        }
        else
        {
            return password;
        }
    }
}
char inputRole(int X, int &Y)
{
    while (true)
    {
        string role;
        mygotoxy(X, Y);
        setcolor(yellow);
        cout << "Choose Role ('a' for Admin and 'b' for Salesman): ";
        cin >> role;
        setcolor(white);
        if (role == "a" || role == "b")
        {
            return role[0];
        }
        else
        {
            mygotoxy(X, Y);
            setcolor(red);
            cout << "Invalid Input." << endl;
            setcolor(white);
            mygotoxy(X, Y);
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
bool signUp(int userCount, string uName, string pass, char role, string usernames[], string passwords[], char roles[], int earnings[], string currency[])
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
void printAllBooks(int bookCount, int bookPrice[], int bookQuantity[], string currency, string bookNames[], string authorNames[], int X, int &Y)
{
    mygotoxy(X, Y);
    setcolor(green);
    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
    setcolor(white);
    for (int i = 0; i < bookCount; i++)
    {
        if (bookNames[i] == "")
        {
            continue;
        }
        mygotoxy(X, Y);
        setcolor(lightgreen);
        cout << left << setw(20) << bookNames[i] << setw(20) << authorNames[i] << setw(0) << currency << setw(20) << bookPrice[i] << setw(20) << bookQuantity[i] << endl;
        setcolor(white);
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
bool incrementQuantity(string bName, int quantity, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount)
{
    int index = searchArray(bookNames, bName, bookCount);
    if (index != -1)
    {
        bookQuantity[index] += quantity;
        return true;
    }
    return false;
}
bool changePrice(string bName, int price, string bookNames[], int bookPrice[], int bookQuantity[], int bookCount)
{
    int index = searchArray(bookNames, bName, bookCount);
    if (index != -1)
    {
        bookPrice[index] = price;
        return true;
    }
    return false;
}
void printAllUsers(int userCount, string usernames[], string passwords[], char roles[], int earnings[], string currency[], int X, int &Y)
{
    mygotoxy(X, Y);
    setcolor(green);
    cout << left << setw(20) << "Username" << setw(20) << "Password" << setw(20) << "Role" << setw(20) << "Earnings" << endl;
    setcolor(white);
    for (int i = 0; i < userCount; i++)
    {
        if (usernames[i] == "")
        {
            continue;
        }
        mygotoxy(X, Y);
        setcolor(lightgreen);
        cout << left << setw(20) << usernames[i] << setw(20) << passwords[i] << setw(20) << getRole(roles[i]) << setw(0) << currency[i] << setw(20) << earnings[i] << endl;
        setcolor(white);
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
void printAllOrders(int orderCount, string orderBookNames[], string orderBookAuthorNames[], int orderBookQuantity[], int orderBookPrice[], string currency, int X, int &Y)
{
    mygotoxy(X, Y);
    setcolor(green);
    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
    setcolor(white);
    for (int i = 0; i < orderCount; i++)
    {
        if (orderBookNames[i] == "")
        {
            continue;
        }
        mygotoxy(X, Y);
        setcolor(lightgreen);
        cout << left << setw(20) << orderBookNames[i] << setw(20) << orderBookAuthorNames[i] << setw(0) << currency << setw(20) << orderBookPrice[i] << setw(20) << orderBookQuantity[i] << endl;
        setcolor(white);
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
int getNum(string prompt, int X, int &Y)
{
    string num;
    while (true)
    {
        setcolor(yellow);
        mygotoxy(X, Y);
        cout << prompt;
        cin >> num;
        setcolor(white);
        if (checkInt(num))
        {
            return strToInt(num);
        }
        else
        {
            setcolor(red);
            mygotoxy(X, Y);
            cout << "Invalid Input." << endl;
            setcolor(white);
            mygotoxy(X, Y);
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
string getValidatedInput(string prompt, int X, int &Y)
{
    while (true)
    {
        string input;
        setcolor(yellow);
        mygotoxy(X, Y);
        cout << prompt;
        myGetLine(input);
        setcolor(white);
        if (checkComma(input))
        {
            mygotoxy(X, Y);
            setcolor(red);
            cout << "Input cannot contain comma (,)" << endl;
            setcolor(white);
            mygotoxy(X, Y);
            cout << "Press any key to try again..................." << endl;
            getch();
        }
        else
        {
            return input;
        }
    }
}
bool currencyCheck(string currency)
{
    if (currency == "$" || currency == "\x9C")
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
bool checkComma(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == ',')
        {
            return true;
        }
    }
    return false;
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
void storeCredentials(string usernames[], string passwords[], char roles[], int earnings[], string currency[], int userCount)
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
        f << bookNames[i] << "," << authorNames[i] << "," << bookPrice[i] << "," << bookQuantity[i];
        if (i != bookCount - 1)
        {
            f << endl;
        }
    }
    f.close();
}
void loadCredentials(string usernames[], string passwords[], char roles[], int earnings[], string currency[], int &userCount)
{
    string line;
    fstream f;
    f.open("credentials.txt", ios::in);
    if (f.fail())
    {
        cout << "Error opening file." << endl;
        exit(1);
    }
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
    if (f.fail())
    {
        cout << "Error opening file." << endl;
        exit(1);
    }
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
// File Handling Functions End
// Error Handling Functions Start
void myGetLine(string &s)
{
    cin.clear();
    cin.sync();
    getline(cin >> ws, s);
}