#include <iostream>
#include <conio.h>
using namespace std;
// Start
void printBanner();
int startingPage();
// Login and Signup
int currentIdx = 0;
string inputUsername();
string inputPassword();
char inputRole();
bool login();
void signUp();
// Dashboards
int ownerDashboard();
int salesManDashboard();
// Validation
int searchArray(string arr[], string object);
// Data Structures
string usernames[100], passwords[100];
char roles[100];
int userCount = 0;
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
            if (roles[currentIdx] == 'a')
            {
                choice = ownerDashboard();
                if (choice == 11)
                {
                    goto mainPage;
                }
            }
            else if (roles[currentIdx] == 'b')
            {
                choice = salesManDashboard();
                if (choice==11)
                {
                    goto mainPage;
                }
            }
        }
        else
        {
            cout << "Invalid Credentials." << endl;
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
    currentIdx = index;
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
    cout << "Logged in as " << usernames[currentIdx] << " (Owner)" << endl;
    cout << "Choose one of the following: " << endl;
    cout << "1. Add a new Book" << endl;
    cout << "2. Remove a Book" << endl;
    cout << "3. Search for a Book" << endl;
    cout << "4. Update a Book's details" << endl;
    cout << "5. Add a new user" << endl;
    cout << "6. Remove an existing user" << endl;
    cout << "7. Search for a user" << endl;
    cout << "8. Update an user's details" << endl;
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
    cout << "Logged in as " << usernames[currentIdx] << " (Salesman)" << endl;
    cout << "Choose one of the following: " << endl;
    cout << "1. Search for a Book" << endl;
    cout << "2. Check availablity" << endl;
    cout << "3. Browse all Available Books" << endl;
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