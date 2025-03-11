#include <iostream>
#include "clients.h"

using namespace std;

int main() {
    Clients viewClients; //this class pushes capacity to constructor
   
    while(true) {
    cout << "MAIN MENU" << endl;
    cout << "1. View all clients" << endl;
    cout << "2. Search ID" << endl;
    cout << "3. Add new client file" << endl;
    cout << "4. Remove client file" << endl;
    cout << "5. Sort Descending (highest to lowest balance)" << endl;
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
