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

   // static int totalEvents;
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
       // totalEvents++;
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
    double price;
    int ticketID;
    //to add * field 

public:
    Ticket() {
        type = STANDING;
        seatNumber = 0;
        eventDate = "";
        eventName = "";
        totalTickets = 0;
        ticketCounter = 0;
        ticketID = 0;
        price = 0;
    }

    Ticket(TicketType type, int seatNumber, string eventDate, string eventName, double price) {

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
        this->price = price;


    }

    Ticket(const Ticket& t) {
        this->type = t.type;
        this->seatNumber = t.seatNumber;
        this->eventDate = t.eventDate;
        this->eventName = t.eventName;
        this->totalTickets = t.totalTickets;
        this->ticketCounter = t.ticketCounter;
        this->ticketID = t.ticketID;
        this->price = t.price;
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

    double getPrice()  {
        return price;
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


    Ticket operator+(const Ticket& plus) const {
        Ticket result = *this;
        result.price += plus.price;
        return result;
    }

    friend ostream& operator<<(ostream& out, const Ticket& ticket) {
        out << "Ticket ID: " << ticket.ticketID << endl;
        out << "Type: " << ticket.type << endl;
        out << "Seat Number: " << ticket.seatNumber << endl;
        out << "Event Date: " << ticket.eventDate << endl;
        out << "Event Name: " << ticket.eventName << endl;
        out << "Ticket Price: " << ticket.price << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Ticket& ticket) {
        int typeInt;

        cout << "Enter ticket type (0 for VIP, 1 for MAIN_STAGE, 2 for LOUNGE, 3 for STANDING): ";
        in >> typeInt;

        if (typeInt >= 0 && typeInt <= 3) {
            ticket.type = static_cast<TicketType>(typeInt);
        }
        else {
            cout << "Invalid ticket type. Setting to STANDING." << endl;
            ticket.type = STANDING;
        }

        cout << "Enter seat number: ";
        in >> ticket.seatNumber;

        cout << "Enter event date: ";
        in >> ticket.eventDate;

        cout << "Enter event name: ";
       // in.ignore();
        getline(in, ticket.eventName);

        cout << "Enter ticket price: ";
        in >> ticket.price;

        return in;
    }
   

   
};

class Buyer {
private:
    string buyerName;
    string buyerEmail;
    string buyerPhoneNumber;
    int age;
    int ticketId;

public:
   
    Buyer() {
        buyerName = "";
        buyerEmail = "";
        buyerPhoneNumber = "";
        age = 0;
        ticketId = 0;
    }

    Buyer(string name, string email, string phoneNumber, int age, int ticketId) {
        buyerName = name;
        buyerEmail = email;
        buyerPhoneNumber = phoneNumber;
        this->age = age;
        this->ticketId = ticketId;
    }

    
    Buyer(const Buyer& b) {
        buyerName = b.buyerName;
        buyerEmail = b.buyerEmail;
        buyerPhoneNumber = b.buyerPhoneNumber;
        age = b.age;
        ticketId = b.ticketId;
    }

    
    ~Buyer() {
        
    }

    
    string getBuyerName() {
        return buyerName;
    }

    string getBuyerEmail() {
        return buyerEmail;
    }

    string getBuyerPhoneNumber()  {
        return buyerPhoneNumber;
    }

    int getAge() {
        return age;
    }

    int getTicketId() {
        return ticketId;
    }

    void setBuyerName(string name) {
        buyerName = name;
    }

    void setBuyerEmail(string email) {
        buyerEmail = email;
    }

    void setBuyerPhoneNumber(string phoneNumber) {
        buyerPhoneNumber = phoneNumber;
    }

    void setAge(int newAge) {
        if (newAge >= 14) {
            age = newAge;
        }
        else {
            cout << "Error: Only people above 14 can participate to this event." << endl;
        }
    }

    void setTicketId(int newTicketId) {
        ticketId = newTicketId;
    }

    
    Buyer& operator=(const Buyer& b) {
        if (this == &b) {
            return *this;
        }

        buyerName = b.buyerName;
        buyerEmail = b.buyerEmail;
        buyerPhoneNumber = b.buyerPhoneNumber;
        age = b.age;
        ticketId = b.ticketId;

        return *this;
    }

    
    friend ostream& operator<<(ostream& out, const Buyer& buyer) {
        out << "Buyer Name: " << buyer.buyerName << endl;
        out << "Buyer Email: " << buyer.buyerEmail << endl;
        out << "Buyer Phone Number: " << buyer.buyerPhoneNumber << endl;
        out << "Age: " << buyer.age << endl;
        out << "Ticket ID: " << buyer.ticketId << endl;
        return out;
    }

    
    friend istream& operator>>(istream& in, Buyer& buyer) {
        cout << "Enter buyer name: ";
        getline(in, buyer.buyerName);
        cout << "Enter buyer email: ";
        getline(in, buyer.buyerEmail);
        cout << "Enter buyer phone number: ";
        getline(in, buyer.buyerPhoneNumber);
        cout << "Enter age: ";
        in >> buyer.age;
        cout << "Enter ticket ID: ";
        in >> buyer.ticketId;

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
    Ticket myTicket;
    Ticket ticket1(VIP, 1, "2023-11-05", "Event 1", 200);
    cout << "Ticket 1 Details:\n" << ticket1;

    Ticket ticket2;
    cin >> ticket2;

    if (ticket2.getTotalTickets() > 0) {
        cout << "Ticket 2 Details:\n" << ticket2;
    }
    else {
        cout << "Invalid ticket details entered.\n";
    }
    // Test Buyer class
    Buyer buyer1;
    cin >> buyer1;

    cout << "Buyer 1 Details:\n" << buyer1;

    Buyer buyer2("John Doe", "john@yahoo.com", "1234567890", 25, 101);
    cout << "Buyer 2 Details:\n" << buyer2;


    // Assignment operator
    Buyer buyer4;
    buyer4 = buyer2;
    cout << "Buyer 4 (Copy of Buyer 2) Details:\n" << buyer4;


};
