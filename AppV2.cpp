#include <iostream>
#include <conio.h>
#include <iomanip>
#include <limits>
using namespace std;
// Start
void printBanner();
int startingPage();
// Login and Signup
string inputUsername();
string inputPassword();
char inputRole();
bool login(int userCount, string uName, string pass, string usernames[], string passwords[]);
bool signUp(int userCount, string uName, string pass, char role, string usernames[], string passwords[], char roles[]);
// Dashboards
int ownerDashboard(string uName);
int salesManDashboard(string uName);
// Common Options
void printAllBooks(int bookCount, int bookPrice[], int bookQuantity[], char currency, string bookNames[], string authorNames[]);
bool searchBook(string bName, string bookNames[], int bookCount);
// Owner Option
bool addBook(string bName, string auName, int price, int quantity, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount);
bool removeBook(string bName, string auName, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount);
// Validation
int searchArray(string arr[], string object, int userCount);
// Data Structures

main()
{

    // Credentials
    string usernames[100], passwords[100];
    char roles[100];
    int userCount = 0;
    int currentUserIdx = 0;
    // Books
    string bookNames[100];
    string authorNames[100];
    int bookCount = 0, bookPrice[100], bookQuantity[100];
    int currentBookIdx = 0;
    // Global Settings
    char currency = '$';

mainPage:
    system("cls");
    int choice = startingPage();
    if (choice == 3)
    {
        cout << "Exiting..........";
        return 0;
    }
    else if (choice == 1)
    {
    Login:
        system("cls");
        printBanner();
        string uName = inputUsername();
        string pass = inputPassword();
        if (login(userCount, uName, pass, usernames, passwords))
        {
            currentUserIdx = searchArray(usernames, uName, userCount);
            if (roles[currentUserIdx] == 'a')
            {
            DashBoardOwner:
                choice = ownerDashboard(uName);
                if (choice == 11)
                {
                    goto mainPage;
                }
                else if (choice == 1)
                { // Add Book
                    printBanner();
                    string bName, auName;
                    int price, quantity;
                    cout << "Enter name of the book: ";
                    getline(cin, bName);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Enter name of the author: ";
                    getline(cin, auName);
                    cout << "Enter Price: ";
                    cin >> price;
                    cout << "Enter Quantity: ";
                    cin >> quantity;
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
                    goto DashBoardOwner;
                }
                else if (choice == 2)
                { // Remove Book
                    printBanner();
                    string bName, auName;
                    cout << "Enter name of the book: ";
                    getline(cin, bName);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << "Enter name of the author: ";
                    getline(cin, auName);
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
                    goto DashBoardOwner;
                }
                else if (choice == 3)
                { // Search Book
                    printBanner();
                    cout << "Enter the name of the book: ";
                    string bName;
                    getline(cin, bName);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (searchBook(bName, bookNames, bookCount))
                    {
                        int index = searchArray(bookNames, bName, bookCount);
                        cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
                        cout << left << setw(20) << bookNames[index] << setw(20) << authorNames[index] << setw(0) << currency << setw(20) << bookPrice[index] << setw(20) << bookQuantity[index] << endl;
                    }
                    else
                    {
                        cout << "Book Not found" << endl;
                    }
                    cout << "Press any key to return to Dashboard................";
                    getch();
                    goto DashBoardOwner;
                }
                else if (choice == 4)
                {
                    printBanner();
                    printAllBooks(bookCount, bookPrice, bookQuantity, currency, bookNames, authorNames);
                    cout << "Press any key to return to Dashboard................";
                    getch();
                    goto DashBoardOwner;
                }
            }
            else if (roles[currentUserIdx] == 'b')
            {
            DashBoardSalesMan:
                choice = salesManDashboard(uName);
                if (choice == 11)
                {
                    goto mainPage;
                }
                if (choice == 1)
                { // Search Book
                    printBanner();
                    cout << "Enter the name of the book: ";
                    string bName;
                    getline(cin, bName);
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if (searchBook(bName, bookNames, bookCount))
                    {
                        int index = searchArray(bookNames, bName, bookCount);
                        cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
                        cout << left << setw(20) << bookNames[index] << setw(20) << authorNames[index] << setw(0) << currency << setw(20) << bookPrice[index] << setw(20) << bookQuantity[index] << endl;
                    }
                    else
                    {
                        cout << "Book Not found" << endl;
                    }
                    cout << "Press any key to return to Dashboard................";
                    getch();
                }
                if (choice == 3)
                {
                    printBanner();
                    printAllBooks(bookCount, bookPrice, bookQuantity, currency, bookNames, authorNames);
                    cout << "Press any key to return to Dashboard................";
                    getch();
                    goto DashBoardSalesMan;
                }
            }
        }
        else
        {
            cout << "Invalid Credentials." << endl;
            cout << "Press any key to try again..........." << endl;
            getch();
            goto Login;
        }
    }
    else if (choice == 2)
    {
    signUpPage:
        system("cls");
        printBanner();
        string uName = inputUsername();
        string pass = inputPassword();
        char role = inputRole();
        if (signUp(userCount, uName, pass, role, usernames, passwords, roles))
        {
            userCount++;
            cout << "You have been signed up successfully." << endl;
            cout << "Press any key to continue.......";
            getch();
            goto mainPage;
        }
        else
        {
            cout << "Username Already exists." << endl;
            cout << "Press any key to try again...........";
            getch();
            goto signUpPage;
        }
    }
}
void printBanner()
{
    system("cls");
    cout << "___________________________________________________________________" << endl;
    cout << "   ,   ,      ____              _        _" << endl;
    cout << "  /////|     | __ )  ___   ___ | | _____| |__   ___  _ __ " << endl;
    cout << " ///// |     |  _ \\ / _ \\ / _ \\| |/ / __| '_ \\ / _ \\| '_ \\" << endl;
    cout << "|~~~|  |     | |_) | (_) | (_) |   <\\__ \\ | | | (_) | |_) |" << endl;
    cout << "|===|  |     |____/ \\___/ \\___/|_|\\_\\___/_| |_|\\___/| .__/" << endl;
    cout << "|   |  |                                            |_|" << endl;
    cout << "|   |  |" << endl;
    cout << "|   | /" << endl;
    cout << "|===|/" << endl;
    cout << "'---'" << endl;
    cout << "___________________________________________________________________" << endl;
    cout << endl;
}

int startingPage()
{
    printBanner();
    cout << "Welcome" << endl;
    cout << "Choose one of the following......" << endl;
    cout << "1. Login" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Exit" << endl;
    cout << "Your choice (1 or 2): ";
    int choice;
    cin >> choice;
    return choice;
}

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
    char role;
    cout << "Choose Role ('a' for Admin and 'b' for Salesman): ";
    cin >> role;
    return role;
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

bool signUp(int userCount, string uName, string pass, char role, string usernames[], string passwords[], char roles[])
{
    bool isSignedUp = false;
    int index = searchArray(usernames, uName, userCount);
    if (index == -1)
    {
        usernames[userCount] = uName;
        passwords[userCount] = pass;
        roles[userCount] = role;
        isSignedUp = true;
    }
    return isSignedUp;
}

int ownerDashboard(string uName)
{
    printBanner();
    cout << "Logged in as " << uName << " (Owner)" << endl;
    cout << "Choose one of the following: " << endl;
    cout << "1. Add a new Book" << endl;
    cout << "2. Remove a Book" << endl;
    cout << "3. Search for a Book" << endl;
    cout << "4. List All Books" << endl;
    cout << "5. Add a new user" << endl;
    cout << "6. Remove an existing user" << endl;
    cout << "7. Search for a user" << endl;
    cout << "8. Update a user's details" << endl;
    cout << "9. Manage Discounts" << endl;
    cout << "10. Settings" << endl;
    cout << "11. Logout" << endl;
    cout << "Your Choice (1-11): ";
    int choice;
    cin >> choice;
    return choice;
}

int salesManDashboard(string uName)
{
    printBanner();
    cout << "Logged in as " << uName << " (Salesman)" << endl;
    cout << "Choose one of the following: " << endl;
    cout << "1. Search for a Book" << endl;
    cout << "2. Check availablity" << endl;
    cout << "3. List all Books" << endl;
    cout << "4. Place Customer Order" << endl;
    cout << "5. View Customer Order" << endl;
    cout << "6. Finalize Order" << endl;
    cout << "7. Check Balance" << endl;
    cout << "8. Sales Target" << endl;
    cout << "9. Return a Book" << endl;
    cout << "10. Settings" << endl;
    cout << "11. Logout" << endl;
    cout << "Your Choice (1-11): ";
    int choice;
    cin >> choice;
    return choice;
}

void printAllBooks(int bookCount, int bookPrice[], int bookQuantity[], char currency, string bookNames[], string authorNames[])
{
    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
    for (int i = 0; i <= bookCount; i++)
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

bool addBook(string bName, string auName, int price, int quantity, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount)
{
    int index = searchArray(bookNames, bName, bookCount);
    if (index == -1 || auName != authorNames[index])
    {
        bookNames[bookCount] = bName;
        authorNames[bookCount] = auName;
        bookPrice[bookCount] = price;
        bookQuantity[bookCount] = quantity;
        return true;
    }
    return false;
    bookCount++;
}

bool removeBook(string bName, string auName, string bookNames[], string authorNames[], int bookPrice[], int bookQuantity[], int bookCount)
{ // Book might exist but it will still say that it does not if author doesn't match
    int index = searchArray(bookNames, bName, bookCount);
    if (index != -1 && auName == authorNames[index])
    {
        bookNames[index] = "";
        authorNames[index] = "";
        bookPrice[index] = 0;
        bookQuantity[index] = 0;
        return true;
    }
    return false;
}

// If object is not in array it will return -1, that can be used to add a condition that it does not exist.
int searchArray(string arr[], string object, int arrLength)
{
    for (int i = 0; i <= arrLength; i++)
    {
        if (arr[i] == object)
        {
            return i;
        }
    }
    return -1;
}