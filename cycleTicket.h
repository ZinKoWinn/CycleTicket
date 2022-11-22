//
// Created by Zin Ko Winn on 11/20/2022.
//

#include "iostream"

#define TICKET_PRICE 4000

struct TicketSaleDetail {
    std::string name;
    std::string phoneNumber;
    std::string address;
    std::string ticketNumbers;
    int fees = 0;
};

namespace Ticket {
    class CycleTicket {
    public:
        void mainMenu();

        int welcome();

        void generateTicketNumbers();

        void showAvailableTickets();

        int isAvailableTicketNumber(std::string ticketNumber);

        void buyTicket();

        void updateAvailableTicket(std::string ticketNumbers);

        void replaceAll(std::string &str, const std::string &oldValue, const std::string &newValue);

        void save(TicketSaleDetail saleDetail);

        void showTicketSaleDetails();

        TicketSaleDetail *findTicketOwner(std::string ticketNumber);

        void ticketWinner();

        void showData(TicketSaleDetail ticketSaleDetail);
    };
}
