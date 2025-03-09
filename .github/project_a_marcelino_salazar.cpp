#include <iostream> //this is the input/output library. it is required to use cout & cin objects which are from istream and ostream classes.
#include <fstream> //this is the file library. it is used to read from files and write to files using ifstream & ofstream classes
#include <sstream> //this is the string stream library. it is used to split and parse strings using stringstream class.
#include <string> //this is the string library for string class.
#include "SortTracker.h"

using namespace std; //tells compiler to make all classes, objects and functions available from std.

class Clients { //here I added a class to hold structs
public:
//here I create multiple structs to where the last struct is nested with the previous 3. This is critical for menu options.
    struct ClientData {
        int id;
        int age;
        string job;
        string marital;
        string education;

        void print() const {
            cout << "ID Number: " << id << endl;
            cout << "Age: " << age << endl;
            cout << "Occupation: " << job << endl;
            cout << "Marital Status: " << marital << endl;
            cout << "Education: " << education << endl;
            cout << "-----------------------" << endl;
        }
    };

    struct ClientBankData {
        string defaulted; //could not use default since it is a keyword.
        int balance;
        string housing;
        string loan;
        
        void print() const {
            cout << "Default record: " << defaulted << endl;
            cout << "Average yearly balance: " << balance << endl;
            cout << "Housing Loans: " << housing << endl;
            cout << "Personal Loans: " << loan << endl;
            cout << "-----------------------" << endl;
        }
    };

    struct CampaignData {    
        string contact;
        int day;
        string month;
        int duration;
        int campaign;
        int pdays;
        int previous;
        string poutcome;
        string y;

        void print() const {
            cout << "Current Result: " << y << endl;
            cout << "Contact Type: " << contact << endl;
            cout << "Last day of the week contacted: " << day << endl;
            cout << "Last month contacted: " << month << endl;
            cout << "Call duration (sec): " << duration << endl;
            cout << "Days since last day contacted: " << pdays << endl;
            cout << "Number of contacts: " << previous << endl;
            cout << "Previous Result: " << poutcome << endl;
            cout << "-----------------------" << endl;
        }
    };

    struct AllClientData { //this struct is nested with previous 3 structs.
        ClientData clientInfo;
        ClientBankData clientBankInfo;
        CampaignData campaignInfo;
        
        void print() const {
            cout << "Client Information: " << endl;
            cout << "" << endl;
            clientInfo.print();
            cout << "Client Bank Information: " << endl;
            cout << "" << endl;
            clientBankInfo.print();
            cout << "Campaign Information: " << endl;
            cout << "" << endl;
            campaignInfo.print();
        }
    };

private:
    AllClientData* clientFile; //this declares a pointer named "clientFile".
    int capacity;

    //this function divides the array into low and high
    int Partition(AllClientData* clientBalance, int lowIndex, int highIndex, SortTracker& tracker) {
        int pivot = clientBalance[lowIndex + (highIndex - lowIndex) / 2].clientBankInfo.balance;

        while (true) {
            while (tracker.IsLT(pivot, clientBalance[lowIndex].clientBankInfo.balance)) {
                lowIndex++;
            }
            while (tracker.IsLT(clientBalance[highIndex].clientBankInfo.balance, pivot)) {
                highIndex--;
            }

            if (lowIndex >= highIndex) {
                return highIndex;
            }

            swap(clientBalance[lowIndex], clientBalance[highIndex]);
            lowIndex++;
            highIndex--;
        }
    }
    //this function impllments the partition function and recursively sorts the array by balance
    void QuickSort(AllClientData* clients, int lowIndex, int highIndex, SortTracker& tracker) {
        if (lowIndex >= highIndex) return;

        int partitionIndex = Partition(clients, lowIndex, highIndex, tracker);
        QuickSort(clients, lowIndex, partitionIndex, tracker);
        QuickSort(clients, partitionIndex + 1, highIndex, tracker);
    }

public:
    Clients() { //this constructor calls Clients object parameter in main body and assigns it to cap and capacity
        loadfile();
    }

    ~Clients() { //this destructor deallocates memory from the dynnamic array to prevent memory leaks.
        delete[] clientFile;
    }

    void sortClients() { //this wrapper function to declare sorttracker calls quicksort.
        SortTracker tracker;
        QuickSort(clientFile, 0, capacity - 1, tracker);
        fullprint();
    }

    void loadfile() {
        ifstream file("bank_full.csv"); //this declares a ifstream class named "file" to open the external file bank_full.csv.
        if (!file) {
            cout << "Error. Could not open file.";
        }
        
        string line; //this declares a string class object named "line" to store values.
        getline(file, line); //here I use the getline() function to store rows from the external file into "line". It's placement here is meant to skip the header before executing the for loop.
        int totalClients = 0; //this counts the number of clients in the file.
        while (getline(file, line)) {
            totalClients++;
        }

        file.clear(); //this resets the reading position
        file.seekg(0);
        getline(file, line);

        clientFile = new AllClientData[totalClients];
        capacity = totalClients;

        int idNumber = 10000; //6 digit id number declared.

        for (int i = 0; i < capacity && getline(file, line); i++) { //this declares a for loop to read in capacity number rows from the external file.
            stringstream parse(line); //this declares a stringstream class named "parse" which splits values from rows stored in "line" variable into individual strings.
            string temporaryLine; //here I declare a string class object named "temporaryLine" to convert strings into integers.
            
            clientFile[i].clientInfo.id = idNumber++; //this assigns unique 6 digit id number to each client.
            //here I use the getline() function to extract data from "parse" and store it into data members accordingly. I used stoi() function to convert strings into integers where needed.
            getline(parse, temporaryLine, ';'); 
            clientFile[i].clientInfo.age = stoi(temporaryLine);
            getline(parse, clientFile[i].clientInfo.job, ';');
            getline(parse, clientFile[i].clientInfo.marital, ';');
            getline(parse, clientFile[i].clientInfo.education, ';');
            getline(parse, clientFile[i].clientBankInfo.defaulted, ';');
            getline(parse, temporaryLine, ';');
            clientFile[i].clientBankInfo.balance = stoi(temporaryLine);
            getline(parse, clientFile[i].clientBankInfo.housing, ';');
            getline(parse, clientFile[i].clientBankInfo.loan, ';');
            getline(parse, clientFile[i].campaignInfo.contact, ';');
            getline(parse, temporaryLine, ';'); 
            clientFile[i].campaignInfo.day = stoi(temporaryLine);
            getline(parse, clientFile[i].campaignInfo.month, ';');
            getline(parse, temporaryLine, ';'); 
            clientFile[i].campaignInfo.duration = stoi(temporaryLine);
            getline(parse, temporaryLine, ';'); 
            clientFile[i].campaignInfo.campaign = stoi(temporaryLine);
            getline(parse, temporaryLine, ';'); 
            clientFile[i].campaignInfo.pdays = stoi(temporaryLine);
            getline(parse, temporaryLine, ';'); 
            clientFile[i].campaignInfo.previous = stoi(temporaryLine);
            getline(parse, clientFile[i].campaignInfo.poutcome, ';');
        }
        file.close();
    }

    void search() { //function to search clients based of their id number.
        int idSearch;
        bool found = false;//here I intialize found variable to determine if a match was found or not.
        cout << "Enter ID Number (starts at 10000): ";
        cin >> idSearch;
        cout << "-----------------------" << endl;

        for (int i = 0; i < capacity; i++) {
            if (clientFile[i].clientInfo.id == idSearch) {
                clientFile[i].print();
                found = true;
                break;
            }
        }

        if (found != true) { //this second if statement lets user know if no matches were found.
            cout << "No matches found. Re-run program";
        }
        
    }

    void fullprint() const { //function to print clientFile
        for (int i = 0; i < capacity; i++) {
            clientFile[i].print(); 
        }
    }

    void addClient() {  //here I create a function to add a new client file
        AllClientData* newClientArray = new AllClientData[capacity + 1]; //this creates a new dynamic array with 1 space appended to store new client file.

        for (int i = 0; i < capacity; i++) {  //this for loop iterates through each existing client file and stores corresponding index to new array.
            newClientArray[i] = clientFile[i];  
        }
    
        cout << "Enter age: ";
        cin >> newClientArray[capacity].clientInfo.age;
        
        cout << "Enter job: ";
        cin >> newClientArray[capacity].clientInfo.job;
        cout << "-----------------------" << endl;
    
        newClientArray[capacity].clientInfo.id = 10000 + capacity; //this assigns new id based off the capacity number.
        
        delete[] clientFile; //this deletes the memory that was previously allocated for client file.
        clientFile = newClientArray; //this re-assigns clientFile with the new array created.
        capacity++; //this updates the array size for the next iteration

        clientFile[capacity - 1].print();

        ofstream outfile("bank_full.csv", ios::app);
        if (outfile.is_open()) {
            outfile << clientFile[capacity - 1].clientInfo.age << ";"
                    << clientFile[capacity - 1].clientInfo.job << ";"
                    << clientFile[capacity - 1].clientInfo.marital << ";"
                    << clientFile[capacity - 1].clientInfo.education << ";"
                    << clientFile[capacity - 1].clientBankInfo.defaulted << ";"
                    << clientFile[capacity - 1].clientBankInfo.balance << ";"
                    << clientFile[capacity - 1].clientBankInfo.housing << ";"
                    << clientFile[capacity - 1].clientBankInfo.loan << ";"
                    << clientFile[capacity - 1].campaignInfo.contact << ";"
                    << clientFile[capacity - 1].campaignInfo.day << ";"
                    << clientFile[capacity - 1].campaignInfo.month << ";"
                    << clientFile[capacity - 1].campaignInfo.duration << ";"
                    << clientFile[capacity - 1].campaignInfo.campaign << ";"
                    << clientFile[capacity - 1].campaignInfo.pdays << ";"
                    << clientFile[capacity - 1].campaignInfo.previous << ";"
                    << clientFile[capacity - 1].campaignInfo.poutcome << "\n";
            outfile.close();
        clientFile[capacity - 1].print();
    }
}

    void removeClient() {
        int removeID;
        cout << "Enter ID Number to remove: ";
        cin >> removeID;
    
        bool found = false;
        int removeIndex = -1;
    
        //search for index to remove using id number
        for (int i = 0; i < capacity; i++) {
            if (clientFile[i].clientInfo.id == removeID) {
                found = true;
                removeIndex = i;
                break;
            }
        }
    
        if (!found) {
            cout << "No client found with ID " << removeID << ".\n";
            return;
        }
    
        //dynamic array with size reduced.
        AllClientData* newClientArray = new AllClientData[capacity - 1];
    
        //copy everything except the client removed.
        for (int i = 0, j = 0; i < capacity; i++) {
            if (i != removeIndex) { //this skips the clients being removed
                newClientArray[j++] = clientFile[i];
            }
        }
    
        delete[] clientFile;
        clientFile = newClientArray;
        capacity--;
    
        cout << "Client with ID " << removeID << " has been removed.\n";
    
        ofstream outfile("bank_full.csv");
        if (outfile.is_open()) {
            outfile << "age;job;marital;education;default;balance;housing;loan;contact;day;month;duration;campaign;pdays;previous;poutcome\n"; // CSV header
    
            for (int i = 0; i < capacity; i++) {
                outfile << clientFile[i].clientInfo.age << ";"
                        << clientFile[i].clientInfo.job << ";"
                        << clientFile[i].clientInfo.marital << ";"
                        << clientFile[i].clientInfo.education << ";"
                        << clientFile[i].clientBankInfo.defaulted << ";"
                        << clientFile[i].clientBankInfo.balance << ";"
                        << clientFile[i].clientBankInfo.housing << ";"
                        << clientFile[i].clientBankInfo.loan << ";"
                        << clientFile[i].campaignInfo.contact << ";"
                        << clientFile[i].campaignInfo.day << ";"
                        << clientFile[i].campaignInfo.month << ";"
                        << clientFile[i].campaignInfo.duration << ";"
                        << clientFile[i].campaignInfo.campaign << ";"
                        << clientFile[i].campaignInfo.pdays << ";"
                        << clientFile[i].campaignInfo.previous << ";"
                        << clientFile[i].campaignInfo.poutcome << "\n";
            }
            outfile.close();
        } else {
            cout << "Error: Could not update the file after removing the client" << endl;
        }
    }
    
};

int main() { 
    Clients viewClients; //this class pushes capacity to constructor
   
    while(true) {
    cout << "MAIN MENU" << endl;
    cout << "1. View all clients" << endl;
    cout << "2. Search ID" << endl;
    cout << "3. Add new client file" << endl;
    cout << "4. Remove client file" << endl;
    cout << "5. Sort" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter option (1,2,3,4,5,6): ";
    int option;
    cin >> option;
    cout << "-----------------------" << endl;

    if (cin.fail()) {
        cout << "Invalid input. Enter valid input: 1,2,3,4,5,6" << endl;
        cout << "-----------------------" << endl;
        
    } else if (option == 1) {
        viewClients.fullprint();

    } else if (option == 2) {
        viewClients.search();

    } else if (option == 3) {
        viewClients.addClient();
    
    } else if (option == 4) {
        viewClients.removeClient();
    
    } else if (option == 5) {
        viewClients.sortClients();
        cout << "Clients sorted:\n";
        viewClients.fullprint();

    } else if (option == 6) {
        cout << "Closing...";
        break;
    
    } else {
        cout << "Invalid input. Enter valid input: 1,2,3,4,5" << endl;
        cout << "-----------------------" << endl;
    }
}


    return 0;

}
