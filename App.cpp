#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;
// Start
void printBanner();
int startingPage();
// Login and Signup
int currentUserIdx = 0;
string inputUsername();
string inputPassword();
char inputRole();
bool login();
void signUp();
// Dashboards
int ownerDashboard();
int salesManDashboard();
// Common Options
void printAllBooks();
void searchBook();
// Owner Option
void addBook();
void removeBook();
// Validation
int searchArray(string arr[], string object);
// Data Structures
// Books
string bookName[100];
string authorName[100];
int bookCount = 0, bookPrice[100], bookQuantity[100];
int currentBookIdx = 0;
// Credentials
string usernames[100], passwords[100];
char roles[100];
int userCount = 0;
// Global Settings
char currency = '$';

main()
{
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
        if (login())
        {
            if (roles[currentUserIdx] == 'a')
            {
            DashBoardOwner:
                choice = ownerDashboard();
                if (choice == 11)
                {
                    goto mainPage;
                }
                else if (choice == 1)
                {
                    addBook();
                    cout << "Press any key to continue.............";
                    getch();
                    goto DashBoardOwner;
                }
                else if (choice == 2)
                {
                    removeBook();
                    cout << "Press any key to continue.............";
                    getch();
                    goto DashBoardOwner;
                }
                else if (choice == 4)
                {
                    printAllBooks();
                    cout << "Press any key to return to Dashboard................";
                    getch();
                    goto DashBoardOwner;
                }
            }
            else if (roles[currentUserIdx] == 'b')
            {
            DashBoardSalesMan:
                choice = salesManDashboard();
                if (choice == 11)
                {
                    goto mainPage;
                }
                if (choice == 3)
                {
                    printAllBooks();
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
        signUp();
        goto mainPage;
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
    cout << "Role: \t a) Admin \t b) Salesman" << endl;
    cin >> role;
    return role;
}
bool login()
{
    system("cls");
    printBanner();
    string username = inputUsername();
    string password = inputPassword();
    int index = searchArray(usernames, username);
    if (index == -1)
    {
        return false;
    }
    currentUserIdx = index;
    if (username == usernames[index] && password == passwords[index])
    {
        return true;
    }
    return false;
}

void signUp()
{
    system("cls");
    printBanner();
    usernames[userCount] = inputUsername();
    passwords[userCount] = inputPassword();
    roles[userCount] = inputRole();
    userCount++;
    cout << "You have been signed up" << endl;
    cout << "Press any key to continue.......";
    getch();
}

int ownerDashboard()
{
    printBanner();
    cout << "Logged in as " << usernames[currentUserIdx] << " (Owner)" << endl;
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

int salesManDashboard()
{
    printBanner();
    cout << "Logged in as " << usernames[currentUserIdx] << " (Salesman)" << endl;
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

void printAllBooks()
{
    printBanner();
    cout << left << setw(20) << "Book Name" << setw(20) << "Author Name" << setw(20) << currency << "Price" << endl;
    for (int i = 0; i < bookCount; i++)
    {
        if (bookName[i] == "")
        {
            continue;
        }
        cout << left << setw(20) << bookName[i] << setw(20) << authorName[i] << setw(20) << bookPrice[i] << endl;
    }
}

void addBook()
{
    printBanner();
    string name, author;
    int price;
    cout << "Enter name of the book: ";
    getline(cin, name);
    cout << "Enter name of the author: ";
    getline(cin, author);
    cout << "Enter Price: ";
    cin >> price;
    int index = searchArray(bookName, name);
    if (index == -1)
    {
        bookName[bookCount] = name;
        authorName[bookCount] = author;
        bookPrice[bookCount] = price;
    }
    else if (author != authorName[index])
    {
        bookName[bookCount] = name;
        authorName[bookCount] = author;
        bookPrice[bookCount] = price;
    }
    else
    {
        cout << "Book already exists" << endl;
    }
    bookCount++;
}

void removeBook()
{
    printBanner();
    string name, author;
    cout << "Enter name of the book: ";
    getline(cin, name);
    cout << "Enter name of the author: ";
    getline(cin, author);
    int index = searchArray(bookName, name);
    if (index != -1 && author == authorName[index])
    {
        bookName[index] = "";
        authorName[index] = "";
        bookPrice[index] = 0;
        bookQuantity = 0;
    }
    else
    {
        cout << "Book does not exist" << endl;
    }
}

// If object is not in array it will return -1, that can be used to add a condition that it does not exist.
int searchArray(string arr[], string object)
{
    for (int i = 0; i <= userCount; i++)
    {
        if (arr[i] == object)
        {
            return i;
        }
    }
    return -1;
}