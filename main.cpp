//
// Created by Zin Ko Winn on 11/20/2022.
//

#include "cycleTicket.h"

using namespace std;
using namespace Ticket;

void mainMenu();

int welcome();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int chosen;
    int result;
    string confirm;
    do {
        chosen = welcome();
        switch (chosen) {
            case 1:
                cout << "Are you sure to regenerate ticket numbers?(y/n)" << endl;
                cout << "Note : This action can not be restore after regenerate." << endl;
                cout << ">: ";
                cin >> confirm;
                cout << endl;
                if (confirm == "y" || confirm == "Y") {
                    CycleTicket::generateTicketNumbers();
                }
                break;
            case 2:
                CycleTicket::showAvailableTickets();
                break;
            case 3:
                result = CycleTicket::buyTicket();
                if (result == -1) {
                    mainMenu();
                }
                break;
            case 4:
                CycleTicket::showTicketSaleDetails();
                break;
            case 5:
                CycleTicket::ticketWinner();
                break;
            default:
                chosen = 6;
                break;
        }
    } while (chosen != 6);
}

int welcome() {
    int option = 0;
    cout << "WELCOME FROM CYCLE TICKET SALE" << endl;
    cout << "===========================================" << endl;
    cout << "1. GENERATE TICKET NUMBERS" << endl;
    cout << "2. SHOW AVAILABLE TICKETS" << endl;
    cout << "3. BUY TICKET" << endl;
    cout << "4. SHOW SALE DETAILS" << endl;
    cout << "5. TICKET WINNER" << endl;
    cout << "6. Quit" << endl;
    cin >> option;
    return option;
}
