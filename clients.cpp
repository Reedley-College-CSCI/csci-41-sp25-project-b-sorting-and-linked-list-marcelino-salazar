#include <iostream>
#include "clients.h"
#include "SortTracker.h"

Clients::Clients() {
    loadfile();
}

Clients::~Clients() { //
    if (clientFile) {
    delete[] clientFile;
    clientFile = nullptr;
    }
}

//this function divides the array into low and high
int Clients::Partition(AllClientData* clientBalance, int lowIndex, int highIndex, SortTracker& tracker, bool isAscending) {
    int pivot = clientBalance[lowIndex + (highIndex - lowIndex) / 2].clientBankInfo.balance;

    while (true) {
        if (isAscending) { //sorts in ascending order.
            while (tracker.IsLT(clientBalance[lowIndex].clientBankInfo.balance, pivot)) {
                lowIndex++;
            }
            while (tracker.IsLT(pivot, clientBalance[highIndex].clientBankInfo.balance)) {
                highIndex--;
            }
        } else { //sorts in descending order.
            while (tracker.IsLT(pivot, clientBalance[lowIndex].clientBankInfo.balance)) {
                lowIndex++;
            }
            while (tracker.IsLT(clientBalance[highIndex].clientBankInfo.balance, pivot)) {
                highIndex--;
            }
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
void Clients::QuickSort(AllClientData* clients, int lowIndex, int highIndex, SortTracker& tracker, bool isAscending) {
    if (lowIndex >= highIndex) return;

    int partitionIndex = Partition(clients, lowIndex, highIndex, tracker, isAscending);
    QuickSort(clients, lowIndex, partitionIndex, tracker, isAscending);
    QuickSort(clients, partitionIndex + 1, highIndex, tracker, isAscending);
}

void Clients::sortClients() {
    int option;

    cout << "Sort by Balance" << endl;
    cout << "1. Descending" << endl;
    cout << "2. Ascending" << endl;
    cout << "Enter an option" << endl;
    cin >> option;

    SortTracker tracker;
    bool isAscending = (option == 2); //this assigns isAscending if option is 2

    if(option == 1 || option == 2) {
    QuickSort(clientFile, 0, capacity - 1, tracker, isAscending);
    cout << "Result: " << endl;
    fullprint();
    } else {
        cout << "Invalid option. Enter 1 or 2" << endl;
    }
}

void Clients::loadfile() {
    ifstream file("bank_full.csv"); //this declares a ifstream class named "file" to open the external file bank_full.csv.
    if (!file) {
        cout << "Error. Could not open file." << endl;
        return;
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

    if (clientFile != nullptr) { 
        delete[] clientFile;
        clientFile = nullptr;
    }

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

void Clients::search() { //function to search clients based of their id number.
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

void Clients::fullprint() const { //function to print clientFile
    for (int i = 0; i < capacity; i++) {
        clientFile[i].print(); 
    }
}

void Clients::addClient() {  //here I create a function to add a new client file
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

void Clients::removeClient() {
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
};
//creating function to append deleted clients to the end of the list
void SinglyLinkedNode::TrashList::Append(const Clients::AllClientData& deletedClient) {
    Node* newNode = new Node(deletedClient);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

//this function will prepend a deleted client to the beginning of the list.
void SinglyLinkedNode::TrashList::Prepend(const Clients::AllClientData& deletedClient) {
    Node* newNode = new Node(deletedClient);
    
    if (!head) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }
}