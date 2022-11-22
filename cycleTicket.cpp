//
// Created by Zin Ko Winn on 11/20/2022.
//

#include "cycleTicket.h"
#include "iostream"
#include "fstream"
#include "string"
#include "iomanip"

using namespace Ticket;
using namespace std;

void CycleTicket::mainMenu() {
    CycleTicket cycleTicket;
    int chosen;
    do {
        chosen = cycleTicket.welcome();
        switch (chosen) {
            case 1:
                cycleTicket.generateTicketNumbers();
                break;
            case 2:
                cycleTicket.showAvailableTickets();
                break;
            case 3:
                cycleTicket.buyTicket();
                break;
            case 4:
                cycleTicket.showTicketSaleDetails();
                break;
            case 5:
                cycleTicket.ticketWinner();
                break;
        }
    } while (chosen != 6);
}

int CycleTicket::welcome() {
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

void CycleTicket::generateTicketNumbers() {
    fstream file;
    fstream tmpFile;
    file.open("available_tickets.txt", ios::app);
    tmpFile.open("temp.txt", ios::app);

    if (!file.is_open() || !tmpFile.is_open()) {
        printf("File opening error");
        exit(1);
    }

    string ticketNumber = "";
    for (int i = 1; i <= 1000; i++) {
        stringstream ss;
        ss << std::setw(4) << std::setfill('0') << i;
        if (i % 20 == 0) {
            ticketNumber = ss.str() + " \n";
        } else {
            ticketNumber = ss.str() + " ";
        }
        tmpFile << ticketNumber;
    }

    file.close();
    tmpFile.close();
    remove("available_tickets.txt");
    rename("temp.txt", "available_tickets.txt");

    cout << "Generate ticket number successfully" << endl << endl;
}

void CycleTicket::showAvailableTickets() {
    cout << "***********************" << endl;
    cout << "AVAILABLE TICKETS" << endl;
    cout << "***********************" << endl << endl;

    fstream file;
    file.open("available_tickets.txt", ios::in);

    if (!file.is_open()) {
        printf("File opening error");
        exit(1);
    }
    string ticketNumber = "";
    string tempTicketNumber = "";
    int index = 1;
    while (!file.eof()) {
        file >> tempTicketNumber;
        if (index % 20 == 0) {
            ticketNumber += tempTicketNumber + "\n";
        } else {
            ticketNumber += tempTicketNumber + " ";
        }
        tempTicketNumber = "";
        index++;
    }
    cout << ticketNumber << endl << endl;
    file.close();
}

int CycleTicket::isAvailableTicketNumber(string ticketNumber) {
    fstream file;
    int ticketNumberIndex = 1;
    file.open("available_tickets.txt", ios::in);

    if (!file.is_open()) {
        printf("File opening error");
        exit(1);
    }
    string tempTicketNumber = "";
    while (!file.eof()) {
        file >> tempTicketNumber;
        if (tempTicketNumber == ticketNumber) {
            return ticketNumberIndex;
        }
        ticketNumberIndex++;
    }
    file.close();
    return -1;
}

void CycleTicket::buyTicket() {
    TicketSaleDetail ticketSaleDetail;
    string tempTicketNumber = "";
    string ticketNumberIndex = "";
    int ticketCount = 0;
    string isValidTicketNumbers;
    do {
        cout << "Enter ticket number : ";
        cin >> ticketSaleDetail.ticketNumbers;
        if (ticketSaleDetail.ticketNumbers == "" || ticketSaleDetail.ticketNumbers.length() < 4) {
            cout << endl << "Invalid ticket number. Please check available ticket number." << endl << endl;
            mainMenu();
        } else {
            for (auto &ch: ticketSaleDetail.ticketNumbers + ",") {
                if (ch == ',') {
                    int tempTicketNumberIndex = isAvailableTicketNumber(tempTicketNumber);
                    if (tempTicketNumberIndex != -1) {
                        ticketNumberIndex += to_string(tempTicketNumberIndex) + ",";
                        isValidTicketNumbers += "1";
                        ticketCount++;
                    } else {
                        isValidTicketNumbers += "0";
                        cout << endl << "Ticket Number " + tempTicketNumber + " is not available." << endl;
                    }
                    tempTicketNumber = "";
                } else {
                    string st(1, ch);
                    tempTicketNumber += st;
                }
            }
        }
    } while (ticketSaleDetail.ticketNumbers == "" || ticketSaleDetail.ticketNumbers.length() < 4);

    replaceAll(isValidTicketNumbers, "1", "");
    int totalPrice = TICKET_PRICE * ticketCount;

    if (isValidTicketNumbers == "") {
        cout << endl;
        cout << "Enter Name : ";
        cin >> ticketSaleDetail.name;
        cout << "Enter Phone Number : ";
        cin >> ticketSaleDetail.phoneNumber;
        cout << "Enter Address : ";
        cin >> ticketSaleDetail.address;
        do {
            cout << endl << "Your Ticket Charges : " << totalPrice << endl;

            cout << "Enter Amount : ";
            cin >> ticketSaleDetail.fees;

            if (ticketSaleDetail.fees < totalPrice) {
                cout << endl
                     << "Ticket fees are " + to_string(totalPrice) + " Kyats. So you need to pay for total charges."
                     << endl;
            }

            if (ticketSaleDetail.fees > totalPrice) {
                int refund = ticketSaleDetail.fees - totalPrice;
                ticketSaleDetail.fees = ticketSaleDetail.fees - refund;
                cout << endl;
                cout << "Your Charges : " << totalPrice << endl;
                cout << "Paid : " << ticketSaleDetail.fees << endl;
                cout << "Refund : " << refund << endl << endl;
            }
        } while (ticketSaleDetail.fees < totalPrice);
        updateAvailableTicket(ticketNumberIndex);
        save(ticketSaleDetail);
    } else {
        cout << ticketSaleDetail.ticketNumbers + " contain invalid lucky number. Please try again!" << endl << endl;
    }
}

void CycleTicket::updateAvailableTicket(string ticketNumbers) {
    if (ticketNumbers != "") {
        fstream file, tmpFile;
        file.open("available_tickets.txt", ios::in);
        tmpFile.open("temp.txt", ios::app);

        if (!file.is_open() || !tmpFile.is_open()) {
            printf("File opening error");
            exit(1);
        }

        string ticketNumberIndex = "";
        string ticketNumber;
        string isTicketFound = "";
        int index = 1;

        while (!file.eof()) {
            file >> ticketNumber;
            for (auto &ch: ticketNumbers + ",") {
                if (ch == ',') {
                    if (to_string(index) == ticketNumberIndex) {
                        isTicketFound += "1";
                        if (index % 20 == 0) {
                            tmpFile << "----  \n";
                        } else {
                            tmpFile << "---- ";
                        }
                    }
                    ticketNumberIndex = "";
                } else {
                    string st(1, ch);
                    ticketNumberIndex += st;
                }
            }

            if (isTicketFound == "") {
                if (index % 20 == 0) {
                    tmpFile << ticketNumber + "  \n";
                } else {
                    tmpFile << ticketNumber + " ";
                }
            }
            isTicketFound = "";
            ticketNumber = "";
            index++;
        }

        file.close();
        tmpFile.close();
        remove("available_tickets.txt");
        rename("temp.txt", "available_tickets.txt");
    }
}

void CycleTicket::save(TicketSaleDetail saleDetail) {
    fstream file;
    file.open("ticket_sale_detail.txt", ios::app);

    if (!file.is_open()) {
        printf("File opening error");
        exit(1);
    }

    file << saleDetail.name << ' ' << saleDetail.phoneNumber << ' ' << saleDetail.address << ' '
         << saleDetail.ticketNumbers << ' ' << saleDetail.fees << '\n';


    cout << "Ticket sale detail added successfully" << endl << endl;
    file.close();
}

void CycleTicket::replaceAll(string &str, const string &oldValue, const string &newValue) {
    if (oldValue.empty())
        return;
    size_t startPosition = 0;
    while ((startPosition = str.find(oldValue, startPosition)) != std::string::npos) {
        str.replace(startPosition, oldValue.length(), newValue);
        startPosition += newValue.length();
    }
}

void CycleTicket::showTicketSaleDetails() {
    cout << "***********************" << endl;
    cout << "TICKET SALE DETAILS" << endl;
    cout << "***********************" << endl << endl;

    fstream file;
    TicketSaleDetail ticketSaleDetail;
    TicketSaleDetail *ticketSaleDetailPtr;
    file.open("ticket_sale_detail.txt", ios::in);

    if (!file.is_open()) {
        printf("File opening error");
        exit(1);
    }

    while (!file.eof()) {
        file >> ticketSaleDetail.name >> ticketSaleDetail.phoneNumber >> ticketSaleDetail.address
             >> ticketSaleDetail.ticketNumbers >> ticketSaleDetail.fees;

        ticketSaleDetailPtr = ticketSaleDetail.name == "" ? NULL : &ticketSaleDetail;

        if (ticketSaleDetailPtr != NULL) {
            if (ticketSaleDetail.name == "") {
                cout << "There is no sale detail data." << endl << endl;
            } else {
                showData(*ticketSaleDetailPtr);
                ticketSaleDetail.name = "";
                ticketSaleDetail.phoneNumber = "";
                ticketSaleDetail.address = "";
                ticketSaleDetail.ticketNumbers = "";
                ticketSaleDetail.fees = 0;
            }
        }
    }

    file.close();
}

TicketSaleDetail *CycleTicket::findTicketOwner(string ticketNumber) {
    if (ticketNumber != "") {
        TicketSaleDetail ticketSaleDetail;
        fstream file;
        file.open("ticket_sale_detail.txt", ios::in);

        if (!file.is_open()) {
            printf("File opening error");
            exit(1);
        }
        string tempTicketNumber = "";

        while (!file.eof()) {
            file >> ticketSaleDetail.name >> ticketSaleDetail.phoneNumber >> ticketSaleDetail.address
                 >> ticketSaleDetail.ticketNumbers >> ticketSaleDetail.fees;
            for (auto &ch: ticketSaleDetail.ticketNumbers + ",") {
                if (ch == ',') {
                    if (tempTicketNumber == ticketNumber) {
                        return &ticketSaleDetail;
                    }
                    tempTicketNumber = "";
                } else {
                    string st(1, ch);
                    tempTicketNumber += st;
                }
            }
            cout << tempTicketNumber << endl;
        }
        file.close();
    }
    return NULL;
}

void CycleTicket::ticketWinner() {
    cout << "***********************" << endl;
    cout << "TICKET WINNER" << endl;
    cout << "***********************" << endl << endl;

    string ticketNumber = "";
    cout << "Enter ticket number : ";
    cin >> ticketNumber;
    TicketSaleDetail *ticketSaleDetail = findTicketOwner(ticketNumber);
    if (ticketSaleDetail != NULL) {
        showData(*ticketSaleDetail);
    } else {
        cout << "There is no ticket winner." << endl << endl;
    }
}

void CycleTicket::showData(TicketSaleDetail ticketSaleDetail) {
    cout << endl;
    cout << "Name : " << ticketSaleDetail.name << endl;
    cout << "Phone Number : " << ticketSaleDetail.phoneNumber << endl;
    cout << "Address : " << ticketSaleDetail.address << endl;
    cout << "Ticket Numbers : " << ticketSaleDetail.ticketNumbers << endl;
    cout << "Ticket Fees : " << ticketSaleDetail.fees << "  Kyats" << endl << endl;
}