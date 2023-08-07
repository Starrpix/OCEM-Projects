#include <iostream>
#include <string>
#include <iomanip> // for setw() to set width for the tables
#include <cstdlib> // for rand() function

using namespace std;

const int MAX_DONORS = 100;

class User {
public:
    string email;
    string password;
    string name;
    string location;
    bool isBloodDonor;

    User() : isBloodDonor(false) {}
    virtual ~User() {}

    virtual void registerUser() = 0;
    virtual bool login() = 0;

    void printTableHeader() {
        cout << "+---------+------------------+----------------+--------------+" << endl;
        cout << "| Donor ID|       Name       |  Blood Group   |   Location   |" << endl;
        cout << "+---------+------------------+----------------+--------------+" << endl;
    }

    void printTableRow(int id, const string& name, const string& bloodGroup, const string& location) {
        cout << "| " << setw(8) << id << " | " << setw(16) << name << " | " << setw(14) << bloodGroup << " | " << setw(12) << location << " |" << endl;
    }

    void printTableFooter() {
        cout << "+---------+------------------+----------------+--------------+" << endl;
    }
};

class Blood_Donator : public User {
public:
    int d_id;
    int d_amt;
    string db_group;

    static Blood_Donator donors[MAX_DONORS];
    static Blood_Donator* loggedInUser; // Session cookie-like variable (PHP imitation)

    void saveToDonorArray() {
        for (int i = 0; i < MAX_DONORS; i++) {
            if (donors[i].d_id == 0) {
                donors[i] = *this;
                break;
            }
        }
    }

    void registerUser() override {
        cout << "\nRegister" << endl;
        cout << "To register for an account, please enter the information requested below." << endl;
        cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "First Name:" << endl;
        cin >> name;
        cout << "Blood Group:" << endl;
        cin >> db_group;
        if (db_group == "A+" || db_group == "B+" || db_group == "AB+" || db_group == "O+" || db_group == "A-" || db_group == "B-" || db_group == "AB-" || db_group == "O-") {
            cout << "Entered Blood Group is " << db_group << endl;
        } else {
            cout << "Enter selected Blood Group: A+ B+ AB+ O+ A- B- AB- O-" << endl;
            return;
        }
        cout << "Location:" << endl;
        cin >> location;
        cout << "Enter E-mail:" << endl;
        cin >> email;

        for (int i = 0; i < MAX_DONORS; i++) {
            if (donors[i].email == email) {
                cout << "User with the same email already exists. Logging in..." << endl;
                loggedInUser = &donors[i]; // Set the loggedInUser pointer
                return;
            }
        }

        cout << "Enter Password:" << endl;
        cin >> password;
        d_id = rand() % 10000;
        saveToDonorArray();
        isBloodDonor = true;
        loggedInUser = this; // Set the loggedInUser pointer
        cout << "Registration Successful" << endl;
    }

    bool login() override {
        string l_email;
        string l_password;
        cout << "\nLogin" << endl;
        cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        cout << "Enter E-mail:" << endl;
        cin >> l_email;
        cout << "Enter Password:" << endl;
        cin >> l_password;
        for (int i = 0; i < MAX_DONORS; i++) {
            if (donors[i].email == l_email && donors[i].password == l_password) {
                cout << "You have logged in to " << l_email << " Account" << endl;
                loggedInUser = &donors[i]; // Set the loggedInUser pointer
                return true;
            }
        }
        cout << "Invalid Login. Please try again." << endl;
        loggedInUser = nullptr; // Clear the loggedInUser pointer
        return false;
    }

    void searchDonorsByBloodGroup(const string& bloodGroup) {
        if (loggedInUser == nullptr) {
            cout << "Please log in first" << endl;
            return;
        }

        bool found = false;
        printTableHeader();
        for (int i = 0; i < MAX_DONORS; i++) {
            if (donors[i].d_id != 0 && donors[i].db_group == bloodGroup) {
                printTableRow(donors[i].d_id, donors[i].name, donors[i].db_group, donors[i].location);
                found = true;
            }
        }
        printTableFooter();

        if (!found) {
            cout << "No Donors found for Blood Group " << bloodGroup << endl;
        }
    }
};

Blood_Donator Blood_Donator::donors[MAX_DONORS] = {};
Blood_Donator* Blood_Donator::loggedInUser = nullptr; // Initialize the loggedInUser pointer

int main() {
    Blood_Donator* obj = new Blood_Donator;

    while (true) {
        cout << "\nBlood Bank Tracker\n\n";
        cout << "Choose an option:" << endl;
        cout << "1. Register as a Blood Donor" << endl;
        cout << "2. Login" << endl;
        cout << "3. Search Donors" << endl;
        cout << "4. Exit" << endl;
        cout << "5. Logout" << endl<<endl;


        int choice;
        cin >> choice;

        if (choice == 1) {
            delete obj;
            obj = new Blood_Donator;
            obj->registerUser();
        } else if (choice == 2) {
            if (obj != nullptr) {
                delete obj;
            }
                obj = new Blood_Donator;
            if(obj->login()){
                cout << "You have successfully logged in." << endl;
                           } else {
                               cout << "Login failed. Please try again." << endl;
            }
            
        } else if (choice == 3) {
            if (Blood_Donator::loggedInUser != nullptr) {
                cout << "A. Search by Blood Group" << endl;
                char subChoice;
                cin >> subChoice;
                if (subChoice == 'A' || subChoice == 'a') {
                    string bloodGroup;
                    cout << "Enter the blood group to search:";
                    cin >> bloodGroup;
                    Blood_Donator::loggedInUser->searchDonorsByBloodGroup(bloodGroup);
                }
                   else {
                    cout << "Invalid Choice." << endl;
                }
            } else {
                cout << "Please log in first" << endl;
            }
        } else if (choice == 4) {
            cout << "Exiting Program" << endl;
            delete obj;
            break;
        }
        else if (choice == 5) {
            if (Blood_Donator::loggedInUser != nullptr) {
                cout << "Logging out..." << endl;
                Blood_Donator::loggedInUser = nullptr;
            } else {
                cout << "You are not logged in." << endl;
            }
        }
        
        else {
            cout << "Invalid Choice." << endl;
        }

        if (Blood_Donator::loggedInUser != nullptr) {
            cout << "Welcome, " << Blood_Donator::loggedInUser->name << "!" << endl;
        }

        cout << "Press enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}



