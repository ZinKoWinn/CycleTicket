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
        static void generateTicketNumbers();

        static void showAvailableTickets();

        static int buyTicket();

        static void showTicketSaleDetails();

        static void ticketWinner();

    private:
        static void replaceAll(std::string &str, const std::string &oldValue, const std::string &newValue);

        static TicketSaleDetail *findTicketOwner(const std::string &ticketNumber);

        static int isAvailableTicketNumber(const std::string &ticketNumber);

        static void save(const TicketSaleDetail &saleDetail);

        static void updateAvailableTicket(const std::string &ticketNumbers);

        static void showData(const TicketSaleDetail &ticketSaleDetail);
    };
}
