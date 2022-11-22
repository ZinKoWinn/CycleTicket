//
// Created by Zin Ko Winn on 11/20/2022.
//

#include "iostream"

#define TICKET_PRICE 4000

using namespace std;

struct TicketSaleDetail {
    string userName;
    string phoneNumber;
    string address;
    string ticketNumbers;
    int fees = 0;
};

namespace Ticket {
    class CycleTicket {
    public:
        void mainMenu();

        int welcome();

        void generateTicketNumbers();

        void showAvailableTickets();

        int isAvailableTicketNumber(string ticketNumber);

        void buyTicket();

        void updateAvailableTicket(string ticketNumbers);

        void replaceAll(string &str, const string &oldValue, const string &newValue);

        void save(TicketSaleDetail saleDetail);

        void showTicketSaleDetails();

        TicketSaleDetail *findTicketOwner(string ticketNumber);

        void ticketWinner();

        void showData(TicketSaleDetail ticketSaleDetail);
    };
}
