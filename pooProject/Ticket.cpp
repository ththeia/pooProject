#include <iostream>
#include <string>

using namespace std;

enum TicketType { VIP, MAIN_STAGE, LOUNGE, STANDING };

class Ticket {
private:
    TicketType type;
    int seatNumber;
    string eventDate;
    string eventName;
    int totalTickets;
    int ticketCounter;
    int ticketID;
   //to add * field 

public:
    Ticket() {
        type = VIP;
        seatNumber = 0;
        eventDate = "";
        eventName = "";
        totalTickets = 0;
        ticketCounter = 0;
        ticketID = 0;
    }

    Ticket(TicketType type, int seatNumber, string eventDate, string eventName) {
       
            this->type = type;
            this->seatNumber = seatNumber;
            this->eventDate = eventDate;
            this->eventName = eventName;
            totalTickets = 0;
            ticketCounter = 0;
            ticketID = 0;

            totalTickets++;
            ticketCounter++;
            this->ticketID = ticketCounter;
        
        
    }

    Ticket(const Ticket& t) {
        type = t.type;
        seatNumber = t.seatNumber;
        eventDate = t.eventDate;
        eventName = t.eventName;
        totalTickets = t.totalTickets;
        ticketCounter = t.ticketCounter;
        ticketID = t.ticketID;
    }

 
    ~Ticket() {
        totalTickets--;
    }

   
    TicketType getType()  {
        return type;
    }

    int getSeatNumber()  {
        return seatNumber;
    }

    string getEventDate()  {
        return eventDate;
    }

    string getEventName()  {
        return eventName;
    }

    int getTicketID()  {
        return ticketID;
    }

    int getTotalTickets()  {
        return totalTickets;
    }

    
    void setType(TicketType newType) {
        
        type = newType;
    }

    void setSeatNumber(int newSeatNumber) {
        if (newSeatNumber > 0) {
            seatNumber = newSeatNumber;
        }
        else {
            throw invalid_argument("Seat number must be a positive integer.");
        }
    }

    void setEventDate(string newEventDate) {
      
        eventDate = newEventDate;
    }

    void setEventName(string newEventName) {
        
        eventName = newEventName;
    }

    
    friend ostream& operator<<(ostream& out, const Ticket& ticket) {
        out << "Ticket ID: " << ticket.ticketID << endl;
        out << "Type: " << ticket.type << endl;
        out << "Seat Number: " << ticket.seatNumber << endl;
        out << "Event Date: " << ticket.eventDate << endl;
        out << "Event Name: " << ticket.eventName << endl;
        return out;
    }

    
    friend istream& operator>>(istream& in, Ticket& ticket) {
        cout << "Enter ticket type (VIP, MAIN_STAGE, LOUNGE, STANDING): ";
        int typeInt;
        in >> typeInt;
        ticket.type = static_cast<TicketType>(typeInt);

        cout << "Enter seat number: ";
        in >> ticket.seatNumber;
        cout << "Enter event date: ";
        in >> ticket.eventDate;
        cout << "Enter event name: ";
        in >> ticket.eventName;

        // santa maria why it doesnt work check tmrw
        //totalTickets++;
        ticket.ticketCounter++;
        ticket.ticketID = ticket.ticketCounter;

        return in;
    }
};

//int main() {
//    // Test the Ticket class
//    Ticket ticket1(VIP, 1, "2023-11-05", "Event 1");
//    cout << "Ticket 1 Details:\n" << ticket1;
//
//    Ticket ticket2;
//    cin >> ticket2;
//
//    if (ticket2.getTotalTickets() > 0) {
//        cout << "Ticket 2 Details:\n" << ticket2;
//    }
//    else {
//        cout << "Invalid ticket details entered.\n";
//    }
//
//    return 0;
//}

