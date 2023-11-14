#include <iostream>
#include <conio.h>
using namespace std;
// Start
void printBanner();
int startingPage();
// Login and Signup
string inputUsername();
string inputPassword();
char inputRole();
bool login();
void signUp();
// Validation
int searchArray(string arr[], string object);
// Data Structures
string usernames[], passwords[];
char roles[];
int userCount = 0;
main()
{
    int choice = startingPage();
    if (choice == 3)
    {
        cout << "Exiting..........";
        return 0;
    }
    else if (choice == 1)
    {
        printBanner();
        string username = inputUsername();
        string password = inputPassword();
        char role = inputRole();
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
    cout << "Role:\ta)Admin\tb)Salesman";
    cin >> role;
    return role;
}
bool login()
{
    printBanner();
    string username = inputUsername();
    string password = inputPassword();
    int index = searchArray(usernames, username);
    if (username == usernames[index] && password == passwords[index])
    {
        return true;
    }
    return false;
}

void signUp()
{
    printBanner();
    usernames[userCount] = inputUsername();
    passwords[userCount] = inputPassword();
    roles[userCount] = inputRole();
    userCount++;
    cout << "You have been signed up" << endl;
    cout << "Press any key to continue.......";
    getch();
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