#include <iostream>
#include <string>

using namespace std;

enum TicketType { VIP, MAIN_STAGE, LOUNGE, STANDING };

class Event {
private:
    string name;
    string date;
    string time;
    int maxSeats;
    int* seatNumbers;

    //static int totalEvents;
    const int DEFAULT_MAX_SEATS;

public:
    Event() : DEFAULT_MAX_SEATS(50) {
        name = "";
        date = "";
        time = "";
        maxSeats = 0;
        seatNumbers = nullptr;
    }

    Event(string name, string date, string time, int maxSeats) : DEFAULT_MAX_SEATS(DEFAULT_MAX_SEATS) {
        this->name = name;
        this->date = date;
        this->time = time;
        this->maxSeats = maxSeats;

        if (maxSeats > 0) {
            this->seatNumbers = new int[maxSeats];
        }
        else {
            this->seatNumbers = nullptr;
        }
        //totalEvents++;
    }

    Event& operator=(const Event& o) {
        if (this == &o) {
            return *this;
        }
        this->name = o.name;
        this->date = o.date;
        this->time = o.time;
        this->maxSeats = o.maxSeats;


        delete[] this->seatNumbers;


        if (o.seatNumbers != nullptr) {
            this->seatNumbers = new int[o.maxSeats];
            for (int i = 0; i < o.maxSeats; i++) {
                this->seatNumbers[i] = o.seatNumbers[i];
            }
        }
        else {
            this->seatNumbers = nullptr;
        }

        return *this;
    }


    Event(const Event& e): DEFAULT_MAX_SEATS(e.DEFAULT_MAX_SEATS) {
        this->name = e.name;
        this->date = e.date;
        this->time = e.time;
        this->maxSeats = e.maxSeats;

        if (e.seatNumbers != nullptr) {
            this->seatNumbers = new int[e.maxSeats];
            for (int i = 0; i < e.maxSeats; i++) {
                this->seatNumbers[i] = e.seatNumbers[i];
            }
        }
        else {
            this->seatNumbers = nullptr;
        }
    }

    ~Event() {
        if (this->seatNumbers != nullptr) {
            delete[] this->seatNumbers;
        }
    }
    string getName() {
        return this->name;
    }

    string getDate() {
        return this->date;
    }

    string getTime() {
        return this->time;
    }

    int getMaxSeats() {
        return this->maxSeats;
    }

    int* getSeatNumbers() {
        return this->seatNumbers;
    }
   /* static int getTotalEvents() {
        return totalEvents;
    }*/

    int getDefaultMaxSeats() const {
        return DEFAULT_MAX_SEATS;

    }
    void setName(string name) {
        this->name = name;
    }

    void setDate(string date) {
        this->date = date;
    }

    void setTime(string time) {
        this->time = time;
    }

    void setMaxSeats(int newMaxSeats) {
        if (newMaxSeats >= 0) {
            this->maxSeats = newMaxSeats;
            delete[] this->seatNumbers;
            if (newMaxSeats > 0) {
                this->seatNumbers = new int[newMaxSeats];
            }
            else {
                this->seatNumbers = nullptr;
            }
        }
        else {
            cout << "Error: Maximum seats must be a positive number." << endl;
        }
    }
    bool isValid() {
        return !this->name.empty() && !this->date.empty() && !this->time.empty() && this->maxSeats > 0;
    }

    friend istream& operator>>(istream& in, Event& event) {
        cout << "Enter event name: ";
        getline(in, event.name);
        cout << "Enter event date: ";
        getline(in, event.date);
        cout << "Enter event time: ";
        getline(in, event.time);
        cout << "Enter maximum number of seats: ";
        in >> event.maxSeats;

        if (event.maxSeats > 0) {
            event.seatNumbers = new int[event.maxSeats];
        }
        else {
            event.seatNumbers = nullptr;
        }

        return in;

    }

    friend ostream& operator<<(ostream& out, const Event& event) {
        out << "Event Name: " << event.name << endl;
        out << "Event Date: " << event.date << endl;
        out << "Event Time: " << event.time << endl;
        out << "Maximum Seats: " << event.maxSeats << endl;
        return out;
    }

};

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

    TicketType getType() {
        return type;
    }

    int getSeatNumber() {
        return seatNumber;
    }

    string getEventDate() {
        return eventDate;
    }

    string getEventName() {
        return eventName;
    }

    int getTicketID() {
        return ticketID;
    }

    int getTotalTickets() {
        return totalTickets;
    }


    void setType(TicketType newType) {

        type = newType;
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


void main() {

    Event event1;
    cin >> event1;


    if (event1.isValid()) {
        cout << "Event Details:\n" << event1;
    }
    else {
        cout << "Invalid event details entered.\n";
    }

    Event event2("Event 2", "2023-11-05", "15:00", 100);
    cout << "Event Details:\n" << event2;

    // copy constructor
    Event event3(event1);
    cout << "Event 3 (Copy of Event 1) Details:\n" << event3;

    //  = operator
    Event event4;
    event4 = event2;
    cout << "Event 4 (Copy of Event 2) Details:\n" << event4;

    event2 = event3 = event1;

    // Test ticket class
    Ticket ticket1(VIP, 1, "2023-11-05", "Event 1");
    cout << "Ticket 1 Details:\n" << ticket1;

    Ticket ticket2;
    cin >> ticket2;

    if (ticket2.getTotalTickets() > 0) {
        cout << "Ticket 2 Details:\n" << ticket2;
    }
    else {
        cout << "Invalid ticket details entered.\n";
    }


};
