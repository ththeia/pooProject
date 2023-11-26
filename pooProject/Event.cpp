#include <iostream>
#include <string>

using namespace std;


//enum TicketType { VIP, MAIN_STAGE, LOUNGE, STANDING };

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date() {
        day = 1;
        month = 1;
        year = 2023;
    }

    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    bool isValid() const {
        if (year < 1900) {
            return false; 
        }
        if (month < 1 || month > 12) {
            return false;
        }

        if (day < 1 || day > 31) {
            return false;
        }

        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }
        if (month == 2) {
            if (day > 29) {
                return false;
            }

            if (day == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))) {
                return false; 
            }
        }
        return true;
    }

    friend istream& operator>>(istream& in, Date& date) {
        cout << "Enter day: ";
        in >> date.day;

        cout << "Enter month: ";
        in >> date.month;

        cout << "Enter year: ";
        in >> date.year;

        return in;
    }

    friend ostream& operator<<(ostream& out, const Date& date) {
        if (date.day < 10) {
            out << '0';
        }
        out << date.day << "-";

        if (date.month < 10) {
            out << '0';
        }
        out << date.month << "-" << date.year;

        return out;
    }
    
};

class Event {
private:
    string name;
    Date date;
    int duration;
    int seats;
    int* seatNumbers; 
    const int DEFAULT_MAX_SEATS;

    static int totalEvents;

public:
    Event() : DEFAULT_MAX_SEATS(50) {
        name = "";
        date = Date();
        duration = 0;
        seats = 0;
        seatNumbers = nullptr;
        totalEvents++;
    }

    Event(string name, int day, int month, int year, int duration, int maxSeats) : DEFAULT_MAX_SEATS(DEFAULT_MAX_SEATS) {
        this->name = name;
        this->date = Date(day, month, year); 
        this->duration = duration;
        this->seats = maxSeats;

        if (maxSeats > 0) {
            this->seatNumbers = new int[maxSeats]();
        }
        else {
            this->seatNumbers = nullptr;
        }
        totalEvents++;
    }

    Event(const Event& e) : DEFAULT_MAX_SEATS(e.DEFAULT_MAX_SEATS) {
        this->name = e.name;
        this->date = e.date;
        this->duration = e.duration;
        this->seats = e.seats;

        if (e.seatNumbers != nullptr) {
            this->seatNumbers = new int[e.seats]();
            for (int i = 0; i < e.seats; i++) {
                this->seatNumbers[i] = e.seatNumbers[i];
            }
        }
        else {
            this->seatNumbers = nullptr;
        }
    }

    Event& operator=(const Event& o) {
        if (this == &o) {
            return *this;
        }
        this->name = o.name;
        this->date = o.date;
        this->duration = o.duration;
        this->seats = o.seats;

        delete[] this->seatNumbers;

        if (o.seatNumbers != nullptr) {
            this->seatNumbers = new int[o.seats]();
            for (int i = 0; i < o.seats; i++) {
                this->seatNumbers[i] = o.seatNumbers[i];
            }
        }
        else {
            this->seatNumbers = nullptr;
        }

        return *this;
    }

    ~Event() {
        if (this->seatNumbers != nullptr) {
            delete[] this->seatNumbers;
        }
    }

    string getName() {
        return this->name;
    }


    int getTime() {
        return this->duration;
    }

    int getMaxSeats() {
        return this->seats;
    }

    int* getSeatNumbers() {
        return this->seatNumbers;
    }
   static int getTotalEvents() {
        return totalEvents;
    }

    int getDefaultMaxSeats() const {
        return DEFAULT_MAX_SEATS;

    }
    void setName(string name) {
        this->name = name;
    }

    void setDuration(int duration) {
        if (duration >= 0) {
            if (this->duration <= duration) {
                this->duration = duration;
            }
            else {
                cout << "Error: New duration must be greater than or equal to the current duration." << endl;
            }
        }
        else {
            cout << "Error: Duration must be a non-negative number." << endl;
        }
    }

    void setMaxSeats(int seats) {
        if (seats >= 0) {
            this->seats = seats;
            delete[] this->seatNumbers;
            if (seats > 0) {
                this->seatNumbers = new int[seats];
            }
            else {
                this->seatNumbers = nullptr;
            }
        }
        else {
            cout << "Error: Maximum seats must be a positive number." << endl;
        }
    }

    static void setTotalEvents(int newTotalEvents) {
        if (newTotalEvents >= 0) {
            totalEvents = newTotalEvents;
        }
        else {
            cout << "Error: Total events must be a non-negative number." << endl;
        }
    }

    bool isValid() {
        return !this->name.empty() && this->duration>0 && this->date.isValid() && this->seats > 0;
    }
    Event& operator++() {
        ++seats;
        int* newSeatNumbers = new int[seats]();
        for (int i = 0; i < seats - 1; ++i) {
            newSeatNumbers[i] = seatNumbers[i];
        }
        delete[] seatNumbers;
        seatNumbers = newSeatNumbers;
        return *this;
    }


    Event operator+(int minutes) const {
        Event e = *this;
        e.duration += minutes;
        return e;
    } 

    friend istream& operator>>(istream& in, Event& event) {
        cout << "Enter event name: ";
        in >> event.name;
        cout << "Enter event date:\n";
        in >> event.date;
        cout << "Enter event time: ";
        in >> event.duration;
        cout << "Enter maximum number of seats: ";
        in >> event.seats;
        if (event.seats > 0) {
            event.seatNumbers = new int[event.seats];
        }
        else {
            event.seatNumbers = nullptr;
        }
        return in;
    }

    friend ostream& operator<<(ostream& out, const Event& event) {
        out << "Event Name: " << event.name << endl;
        out << "Event Date: " << event.date << endl;
        out << "Event Time: " << event.duration << endl;
        out << "Maximum Seats: " << event.seats << endl;
        return out;
    }

};
int Event::totalEvents = 0;

//class Ticket {
//private:
//    TicketType type;
//    int seatNumber;
//    string eventDate;
//    string eventName;
//    int totalTickets;
//    int ticketCounter;
//    double price;
//    int ticketID;
//    //to add * field 
//
//public:
//    Ticket() {
//        type = STANDING;
//        seatNumber = 0;
//        eventDate = "";
//        eventName = "";
//        totalTickets = 0;
//        ticketCounter = 0;
//        ticketID = 0;
//        price = 0;
//    }
//
//    Ticket(TicketType type, int seatNumber, string eventDate, string eventName, double price) {
//
//        this->type = type;
//        this->seatNumber = seatNumber;
//        this->eventDate = eventDate;
//        this->eventName = eventName;
//        totalTickets = 0;
//        ticketCounter = 0;
//        ticketID = 0;
//
//        totalTickets++;
//        ticketCounter++;
//        this->ticketID = ticketCounter;
//        this->price = price;
//
//
//    }
//
//    Ticket(const Ticket& t) {
//        this->type = t.type;
//        this->seatNumber = t.seatNumber;
//        this->eventDate = t.eventDate;
//        this->eventName = t.eventName;
//        this->totalTickets = t.totalTickets;
//        this->ticketCounter = t.ticketCounter;
//        this->ticketID = t.ticketID;
//        this->price = t.price;
//    }
//
//   
//    ~Ticket() {
//        totalTickets--;
//    }
//
//    TicketType getType() {
//        return type;
//    }
//
//    int getSeatNumber() {
//        return seatNumber;
//    }
//
//    string getEventDate() {
//        return eventDate;
//    }
//
//    string getEventName() {
//        return eventName;
//    }
//
//    int getTicketID() {
//        return ticketID;
//    }
//
//    int getTotalTickets() {
//        return totalTickets;
//    }
//
//    double getPrice()  {
//        return price;
//    }
//
//
//    void setType(TicketType newType) {
//
//        type = newType;
//    }
//
//  
//
//    void setEventDate(string newEventDate) {
//
//        eventDate = newEventDate;
//    }
//
//    void setEventName(string newEventName) {
//
//        eventName = newEventName;
//    }
//
//
//    Ticket operator+(const Ticket& plus) const {
//        Ticket result = *this;
//        result.price += plus.price;
//        return result;
//    }
//
//    friend ostream& operator<<(ostream& out, const Ticket& ticket) {
//        out << "Ticket ID: " << ticket.ticketID << endl;
//        out << "Type: " << ticket.type << endl;
//        out << "Seat Number: " << ticket.seatNumber << endl;
//        out << "Event Date: " << ticket.eventDate << endl;
//        out << "Event Name: " << ticket.eventName << endl;
//        out << "Ticket Price: " << ticket.price << endl;
//        return out;
//    }
//
//    friend istream& operator>>(istream& in, Ticket& ticket) {
//        int typeInt;
//
//        cout << "Enter ticket type (0 for VIP, 1 for MAIN_STAGE, 2 for LOUNGE, 3 for STANDING): ";
//        in >> typeInt;
//
//        if (typeInt >= 0 && typeInt <= 3) {
//            ticket.type = static_cast<TicketType>(typeInt);
//        }
//        else {
//            cout << "Invalid ticket type. Setting to STANDING." << endl;
//            ticket.type = STANDING;
//        }
//
//        cout << "Enter seat number: ";
//        in >> ticket.seatNumber;
//
//        cout << "Enter event date: ";
//        in >> ticket.eventDate;
//
//        cout << "Enter event name: ";
//       // in.ignore();
//        getline(in, ticket.eventName);
//
//        cout << "Enter ticket price: ";
//        in >> ticket.price;
//
//        return in;
//    }
//   
//
//   
//};
//
//class Buyer {
//private:
//    string buyerName;
//    string buyerEmail;
//    string buyerPhoneNumber;
//    int age;
//    int ticketId;
//
//public:
//   
//    Buyer() {
//        buyerName = "";
//        buyerEmail = "";
//        buyerPhoneNumber = "";
//        age = 0;
//        ticketId = 0;
//    }
//
//    Buyer(string name, string email, string phoneNumber, int age, int ticketId) {
//        buyerName = name;
//        buyerEmail = email;
//        buyerPhoneNumber = phoneNumber;
//        this->age = age;
//        this->ticketId = ticketId;
//    }
//
//    
//    Buyer(const Buyer& b) {
//        buyerName = b.buyerName;
//        buyerEmail = b.buyerEmail;
//        buyerPhoneNumber = b.buyerPhoneNumber;
//        age = b.age;
//        ticketId = b.ticketId;
//    }
//
//    
//    ~Buyer() {
//        
//    }
//
//    
//    string getBuyerName() {
//        return buyerName;
//    }
//
//    string getBuyerEmail() {
//        return buyerEmail;
//    }
//
//    string getBuyerPhoneNumber()  {
//        return buyerPhoneNumber;
//    }
//
//    int getAge() {
//        return age;
//    }
//
//    int getTicketId() {
//        return ticketId;
//    }
//
//    void setBuyerName(string name) {
//        buyerName = name;
//    }
//
//    void setBuyerEmail(string email) {
//        buyerEmail = email;
//    }
//
//    void setBuyerPhoneNumber(string phoneNumber) {
//        buyerPhoneNumber = phoneNumber;
//    }
//
//    void setAge(int newAge) {
//        if (newAge >= 14) {
//            age = newAge;
//        }
//        else {
//            cout << "Error: Only people above 14 can participate to this event." << endl;
//        }
//    }
//
//    void setTicketId(int newTicketId) {
//        ticketId = newTicketId;
//    }
//
//    
//    Buyer& operator=(const Buyer& b) {
//        if (this == &b) {
//            return *this;
//        }
//
//        buyerName = b.buyerName;
//        buyerEmail = b.buyerEmail;
//        buyerPhoneNumber = b.buyerPhoneNumber;
//        age = b.age;
//        ticketId = b.ticketId;
//
//        return *this;
//    }
//
//    
//    friend ostream& operator<<(ostream& out, const Buyer& buyer) {
//        out << "Buyer Name: " << buyer.buyerName << endl;
//        out << "Buyer Email: " << buyer.buyerEmail << endl;
//        out << "Buyer Phone Number: " << buyer.buyerPhoneNumber << endl;
//        out << "Age: " << buyer.age << endl;
//        out << "Ticket ID: " << buyer.ticketId << endl;
//        return out;
//    }
//
//    friend istream& operator>>(istream& in, Buyer& buyer) {
//        cout << "Enter buyer name: ";
//       // in.ignore(); 
//        getline(in, buyer.buyerName);
//        cout << "Enter buyer email: ";
//        getline(in, buyer.buyerEmail);
//        cout << "Enter buyer phone number: ";
//        getline(in, buyer.buyerPhoneNumber);
//        cout << "Enter age: ";
//        in >> buyer.age;
//        cout << "Enter ticket ID: ";
//        in >> buyer.ticketId;
//
//        return in;
//    }
//};


void main() {

    Date defaultDate;
    cout << "Default Date: " << defaultDate << endl;

    Date paramDate(25, 12, 2023);
    cout << "Date with Parameters: " << paramDate << endl;

    Event event1("Music Festival", 10, 8, 2023, 60, 100);
    if (event1.isValid()) {
        cout << "Event Details:\n" << event1;
    }
    else {
        cout << "Invalid event details entered.\n";
    }

    Event event2("Untold", 25, 12, 2023, 120, 50);
    cout << "Event2:\n" << event2;
    cout << "Event Name: " << event2.getName() << endl;
    cout << "Event Time: " << event2.getTime() << endl;
    cout << "Event Max Seats: " << event2.getMaxSeats() << endl;

    // copy constructor
    Event event3(event1);
    cout << "Event 3 (Copy of Event 1) Details:\n" << event3;
    event3.setName("New Event Name");
    cout << "Updated Event Name: " << event3.getName() << endl;

    event3.setMaxSeats(75);
    cout << "Updated Max Seats: " << event3.getMaxSeats() << endl;

    // = operator
    Event event4;
    event4 = event2;
    cout << "Event 4 (Copy of Event 2) Details:\n" << event4;

    event2 = event3 = event1;

    Event event5("Sports Game", 5, 9, 2023, 15, 75);
    event5.setName("Updated Sports Game");
    event5.setDuration(80);
    event5.setMaxSeats(100);

    if (event5.isValid()) {
        cout << "Updated Event Details:\n" << event5;
    }
    else {
        cout << "Invalid event details entered.\n";
    }
    // test static field
    cout << "Total Events: " << Event::getTotalEvents() << endl;

    //test +operator
    Event original("My Event", 1, 1, 2023, 60, 100);
    cout << "Original Event:\n" << original;

    Event newEvent = original + 15;
    cout << "New event duration:\n" << newEvent;


    Event opPPtest("Example Event", 1, 1, 2023, 60, 100);
    cout << "Initial Seats: " << opPPtest.getMaxSeats() << endl;
    ++opPPtest; 
    cout << "Updated Seats: " << opPPtest.getMaxSeats() << endl;

    //test istream
    Date inputDate;
    cout << "Enter a date:\n";
    cin >> inputDate;
    cout << "Entered date: " << inputDate << endl;

    Event inputEvent;
    cout << "\nEnter event details:\n";
    cin >> inputEvent;
    cout << "Entered event details:\n" << inputEvent;

  
    //// Test ticket class
    //Ticket myTicket;
    //Ticket ticket1(VIP, 1, "2023-11-05", "Event 1", 200);
    //cout << "Ticket 1 Details:\n" << ticket1;

    //Ticket ticket2;
    //cin >> ticket2;

    //if (ticket2.getTotalTickets() > 0) {
    //    cout << "Ticket 2 Details:\n" << ticket2;
    //}
    //else {
    //    cout << "Invalid ticket details entered.\n";
    //}

    //// Test Buyer class
    //Buyer buyer1;
    //cin >> buyer1;

    //cout << "Buyer 1 Details:\n" << buyer1;

    //Buyer buyer2("John Doe", "john@yahoo.com", "1234567890", 25, 101);
    //cout << "Buyer 2 Details:\n" << buyer2;


    //// Assignment operator
    //Buyer buyer4;
    //buyer4 = buyer2;
    //cout << "Buyer 4 (Copy of Buyer 2) Details:\n" << buyer4;


};
