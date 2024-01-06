#include <iostream>
#include <string>
#include <fstream>

using namespace std;


enum TicketType { VIP, LOUNGE, STANDING };

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
    int getDay() {
        return day;
    }

    int getMonth() {
        return month;
    }

    int getYear()  {
        return year;
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

    Event(string name, const Date& date, int duration) : DEFAULT_MAX_SEATS(DEFAULT_MAX_SEATS) {
        this->name = name;
        this->date = date;
        this->duration = duration;
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

    bool operator==(Event& compare) {
        return name == compare.name &&
            date.getDay() == compare.date.getDay() &&
            date.getMonth() == compare.date.getMonth() &&
            date.getYear() == compare.date.getYear() &&
            duration == compare.duration &&
            seats == compare.seats &&
            DEFAULT_MAX_SEATS == compare.DEFAULT_MAX_SEATS;
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
            seatNumbers = nullptr;
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

    Date getDate() {
        return this->date;
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

    Event operator++(int) {
        Event e = *this;
        duration++;
        return e;
    }

    Event operator+(int minutes){
        Event e = *this;
        e.duration += minutes;
        return e;
    } 

    bool operator!()  {
        return name.length() <= 2;
    }

    void showEvent() {
        cout << "Event " << name << " on " << date << " lasts for " << duration << " minutes and has " << seats << " places available.\n";
        
    }

    void displayEventInfo() {
        cout << "Event Name: " << getName() << endl;
        cout << "Event Duration: " << getTime() << " minutes" << endl;
        cout << "Event Date: " << getDate() << endl;
        cout << "Total Events So Far: " << getTotalEvents() << endl;
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

class Ticket {
private:

    string eventName;
    string buyerName;
    Date eventDate;
    int duration;
    int seatNumber;
    TicketType type;
    double price;
    int rowsDesc;
    string* eventDescription;
   
    static int ticketCounter;
    const int TICKET_ID;
  

public:
    Ticket() : TICKET_ID(0){
        eventName = " ";
        buyerName = "";
        eventDate = Date();
        duration = 0;
        seatNumber = 0;
        type = STANDING;
        price = 0;
        rowsDesc = NULL;
        eventDescription = nullptr;
        ticketCounter++;
    }

    Ticket(string eventName, string buyerName, int seatNumber, TicketType type, double price) : TICKET_ID(TICKET_ID) {
        this->eventName = eventName;
        this->buyerName = buyerName;
        this->seatNumber = seatNumber;
        this->type = type;
        this->price = price;
        ticketCounter++;
    }

    Ticket(string eventName, string buyerName, int day, int month, int year, int duration, int seatNumber, TicketType type, double price, int rowsDesc, string* eventDescription ) : TICKET_ID(TICKET_ID) {
        this->eventName = eventName;
        this->buyerName = buyerName;
        this->eventDate = Date(day, month, year);
        this->seatNumber = seatNumber;
        this->type = type;
        this->price = price;
        this->rowsDesc = rowsDesc;

        if (eventDescription != nullptr) {
            this->eventDescription = new string[rowsDesc];
            for (int i = 0; i < rowsDesc; i++) {
                this->eventDescription[i] = eventDescription[i];
            }
        }
        else {
            this->eventDescription = nullptr;
        }  
        ticketCounter++;
    }

    Ticket(const Ticket& t) : TICKET_ID(t.TICKET_ID) {
        this->eventName = t.eventName;
        this->buyerName = t.buyerName;
        this->eventDate = t.eventDate;
        this->duration = t.duration;
        this->seatNumber = t.seatNumber;
        this->type = t.type;
        this->price = t.price;
        this->rowsDesc = t.rowsDesc;
        if (t.eventDescription != nullptr) {
            this->eventDescription = new string[t.rowsDesc];
            for (int i = 0; i < t.rowsDesc; i++) {
                this->eventDescription[i] = t.eventDescription[i];
            }
        }
        else {
            this->eventDescription = nullptr;
        }
    }

    Ticket& operator=(const Ticket& t) {
        if (this == &t) {
            return *this;
        }
        this->eventName = t.eventName;
        this->buyerName = t.buyerName;
        this->eventDate = t.eventDate;
        this->duration = t.duration;
        this->seatNumber = t.seatNumber;
        this->type = t.type;
        this->price = t.price;
        if (t.eventDescription != nullptr) {
            this->eventDescription = new string[t.rowsDesc];
            for (int i = 0; i < t.rowsDesc; i++) {
                this->eventDescription[i] = t.eventDescription[i];
            }
        }
        else {
            this->eventDescription = nullptr;
        }

        return *this;
    }
   
    ~Ticket() {
        if (eventDescription != nullptr) {
            delete[] eventDescription;
            eventDescription = nullptr;
        }
    }

    string getEventName() {
        return eventName;
    }
    
    string getBuyerName() {
        return buyerName;
    }

    Date getDate() {
        return eventDate;
    }

    int getDuration() {
        return duration;
    }

    int getSeatNumber() {
        return seatNumber;
    }

    TicketType getTicketType() {
        return type;
    }

    double getPrice() {
        return price;
    }

    int getRowDesc() {
        return rowsDesc;
    }

    string* getEventDescription() {
        return eventDescription;
    }

    void setDate(int day, int month, int year) {
        Date newDate(day, month, year);
        if (newDate.isValid()) {
            eventDate = newDate;
        }
        else {
            cout << "Invalid date. Please enter a valid date.\n";
        }
    }

    void setDuration(int newDuration) {
        if (newDuration >= 0) {
            duration = newDuration;
        }
        else {
            cout << "Invalid duration. Please enter a non-negative duration.\n";
        }
    }
    void setRowDesc(int newRowDesc) {
        if (newRowDesc >= 0) {
            rowsDesc = newRowDesc;
        }
        else {
            cout << "The description must be greater than 0.\n";
        }
    }

    void setEventDescription(string* newEventDescription) {
        if (newEventDescription != nullptr) {
            for (int i = 0; i < rowsDesc; i++) {
                eventDescription[i] = newEventDescription[i];
            }
        }
        else {
            this->eventDescription = nullptr;
            cout << "Invalid description.\n";
        }
    }


    Ticket operator+(double price) const {
        Ticket newPrice(*this);
        newPrice.price += price;
        return newPrice;
    }

    Ticket& operator--() {
        price = price - 10;
        return *this;
    }

 
    Ticket operator--(int reducere) {
        Ticket redus(*this);
        price = price - 20;
        return redus;
    }

    void displayEventDescriptions() const {
        cout << "Event Descriptions:\n";
        if (rowsDesc > 0 && eventDescription != nullptr) {
            for (int i = 0; i < rowsDesc; i++) {
                cout << "  " << eventDescription[i] << endl;
            }
        }
    }

    void displayTicketInfo() const {
        cout << "Event Name: " << eventName << endl;
        cout << "Buyer Name: " << buyerName << endl;
        cout << "Event Date: " << eventDate << endl;
        cout << "Duration: " << duration << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Ticket Type: " << type << endl;
        cout << "Price: $" << price << endl;
        cout << "Rows: " << rowsDesc << endl;

        if (rowsDesc > 0 && eventDescription != nullptr) {
            cout << "Event Descriptions:\n";
            for (int i = 0; i < rowsDesc; i++) {
                cout << "  " << eventDescription[i] << endl;
            }
        }

        if (price > 50) {
            cout << "This ticket is expensive.\n";
        }
        else {
            cout << "This ticket is not expensive.\n";
        }
    }

    bool operator!() const {
        return eventName.empty() || buyerName.empty() || price <= 0;
    }

   /* bool operator==(const Ticket& t1, const Ticket& t2) {
        return t1.getEventName() == t2.getEventName() &&
            t1.getBuyerName() == t2.getBuyerName() &&
            t1.getDate() == t2.getDate() &&
            t1.getDuration() == t2.getDuration() &&
            t1.getSeatNumber() == t2.getSeatNumber() &&
            t1.getTicketType() == t2.getTicketType() &&
            t1.getPrice() == t2.getPrice() &&
            t1.getRowDesc() == t2.getRowDesc();

        if (t1.getRowDesc() != t2.getRowDesc()) {
            return false;
        }
        for (int i = 0; i < t1.getRowDesc(); ++i) {
            if (t1.getEventDescription()[i] != t2.getEventDescription()[i]) {
                return false;
            }
        }

        return true;
    }*/

    friend ostream& operator<<(ostream& out, Ticket& ticket) {
        out << "Event Name: " << ticket.getEventName() << endl;
        out << "Buyer Name: " << ticket.getBuyerName() << endl;
        out << "Event Date: " << ticket.getDate() << endl;
        out << "Duration: " << ticket.getDuration() << endl;
        out << "Seat Number: " << ticket.getSeatNumber() << endl;
        out << "Ticket Type: " << ticket.getTicketType() << endl;
        out << "Price: $" << ticket.getPrice() << endl;
        out << "Rows: " << ticket.getRowDesc() << endl;

        
        if (ticket.getRowDesc() > 0 && ticket.getEventDescription() != nullptr) {
            out << "Event Descriptions:" << endl;
            for (int i = 0; i < ticket.getRowDesc(); i++) {
                out <<  ticket.getEventDescription()[i] << endl;
            }
        
        }

        return out;
    }

    
    friend istream& operator>>(istream& in, Ticket& ticket) {
        cout << "Enter event name: ";
        getline(in, ticket.eventName);
        cout << "Enter buyer name: ";
        getline(in, ticket.buyerName);
        cout << "Enter event date (in the format DD-MM-YYYY): ";
        in >> ticket.eventDate;
        cout << "Enter duration (in minutes): ";
        in >> ticket.duration;
        cout << "Enter seat number: ";
        in >> ticket.seatNumber;
        cout << "Enter ticket type (0 for VIP, 1 for LOUNGE, 2 for STANDING): ";
        int ticketType;
        in >> ticketType;
        cout << "Enter price: $";
        in >> ticket.price;
        cout << "Enter the number of row descriptions: ";
        in >> ticket.rowsDesc;

        if (ticket.rowsDesc > 0) {
            ticket.eventDescription = new string[ticket.rowsDesc];
            in.ignore(); 
            cout << "Enter event descriptions:\n";
            for (int i = 0; i < ticket.rowsDesc; ++i) {
                cout << "  Description " << i + 1 << ": ";
                getline(in, ticket.eventDescription[i]);
            }
        }
        else {
            ticket.eventDescription = nullptr;
        }

        return in;
    }

    void serialize(ofstream& file)  {
        
        file.write((char*)&seatNumber, sizeof(seatNumber));
        file.write((char*)&duration, sizeof(duration));
        file.write((char*)&type, sizeof(type));
        file.write((char*)&price, sizeof(price));

        
        int eventNameSize = eventName.size();
        file.write((char*)&eventNameSize, sizeof(eventNameSize));
        file.write(eventName.c_str(), eventNameSize);

      
        int buyerNameSize = buyerName.size();
        file.write((char*)&buyerNameSize, sizeof(buyerNameSize));
        file.write(buyerName.c_str(), buyerNameSize);

        int day = eventDate.getDay();
        int month = eventDate.getMonth();
        int year = eventDate.getYear();
        file.write((char*)&day, sizeof(day));
        file.write((char*)&month, sizeof(month));
        file.write((char*)&year, sizeof(year));


       
        file.write((char*)&rowsDesc, sizeof(rowsDesc));
        for (int i = 0; i < rowsDesc; i++) {
            int descSize = eventDescription[i].size();
            file.write((char*)&descSize, sizeof(descSize));
            file.write(eventDescription[i].c_str(), descSize);
        }
    }

   
    void deserialize(ifstream& file) {
        
        file.read((char*)&seatNumber, sizeof(seatNumber));
        file.read((char*)&duration, sizeof(duration));
        file.read((char*)&type, sizeof(type));
        file.read((char*)&price, sizeof(price));

      
        int eventNameSize;
        file.read((char*)&eventNameSize, sizeof(eventNameSize));
        eventName.resize(eventNameSize);
        file.read(&eventName[0], eventNameSize);

      
        int buyerNameSize;
        file.read((char*)&buyerNameSize, sizeof(buyerNameSize));
        buyerName.resize(buyerNameSize);
        file.read(&buyerName[0], buyerNameSize);

    
        int day, month, year;
        file.read((char*)&day, sizeof(day));
        file.read((char*)&month, sizeof(month));
        file.read((char*)&year, sizeof(year));
        eventDate = Date(day, month, year);

      
        file.read((char*)&rowsDesc, sizeof(rowsDesc));
        delete[] eventDescription; 
        eventDescription = new std::string[rowsDesc];
        for (int i = 0; i < rowsDesc; i++) {
            int descSize;
            file.read((char*)&descSize, sizeof(descSize));
            eventDescription[i].resize(descSize);
            file.read(&eventDescription[i][0], descSize);
        }
    }

   
};
int Ticket::ticketCounter = 0;

class Buyer {
private:
    string buyerName;
    char* buyerEmail;
    string buyerPhoneNumber;
    int age;
    int ticketId;
    const int MINIMUM_AGE = 14;

    static string eventName;

public:

    Buyer() : MINIMUM_AGE(14) {
        buyerName = "";
        buyerEmail = nullptr;
        buyerPhoneNumber = "";
        age = 0;
        ticketId = 0;
    }

    Buyer(string name, const char* email, string phoneNumber, int age, int ticketId): MINIMUM_AGE(MINIMUM_AGE) {
        buyerName = name;

        if (email != nullptr) {
            buyerEmail = new char[strlen(email) + 1];
            strcpy_s(buyerEmail, strlen(email) + 1, email);
        }
        else {
            buyerEmail = nullptr; 
        }
        buyerPhoneNumber = phoneNumber;
        this->age = age;
        this->ticketId = ticketId;
    }

    Buyer(string name, string phoneNumber, int age) {
        buyerName = name;
        buyerPhoneNumber = phoneNumber;
        this->age = age;
          
    }

    Buyer(const Buyer& b) : MINIMUM_AGE(b.MINIMUM_AGE) {
        buyerName = b.buyerName;

        if (b.buyerEmail != nullptr) {
            buyerEmail = new char[strlen(b.buyerEmail) + 1];
            strcpy_s(buyerEmail, strlen(b.buyerEmail) + 1, b.buyerEmail);
        }
        else {
            buyerEmail = nullptr;
        }

        buyerPhoneNumber = b.buyerPhoneNumber;
        age = b.age;
        ticketId = b.ticketId;
    }

    
    ~Buyer() {
        if (buyerEmail != nullptr) {
            delete[]buyerEmail;
            this->buyerEmail = nullptr;
        }
    }

    Buyer& operator=(const Buyer& b) {
        if (this == &b) {
            return *this;
        }
        buyerName = b.buyerName;
        delete[] buyerEmail;
        if (b.buyerEmail != nullptr) {
            buyerEmail = new char[strlen(b.buyerEmail) + 1];
            strcpy_s(buyerEmail, strlen(b.buyerEmail) + 1, b.buyerEmail);
        }
        else {
            buyerEmail = nullptr;
        }
        buyerPhoneNumber = b.buyerPhoneNumber;
        age = b.age;
        ticketId = b.ticketId;

        return *this;
    }

    bool operator==(const Buyer& b) const {
        return (buyerName == b.buyerName &&
            buyerPhoneNumber == b.buyerPhoneNumber &&
            age == b.age &&
            ticketId == b.ticketId);
    }

    string getBuyerName()  {
        return buyerName;
    }


    string getBuyerPhoneNumber()  {
        return buyerPhoneNumber;
    }

    int getAge()  {
        return age;
    }

    int getTicketId()  {
        return ticketId;
    }
    int getMinimumAge()  {
        return MINIMUM_AGE;
    }

    static string getEventName() {
        return eventName;
    }


    static void setEventName(string& newEventName) {
        if (!newEventName.empty()) {
            eventName = newEventName;
        }
        else {
            cout << "Error: Event name cannot be empty." << endl;
            
        }
    }

    void setBuyerName(string& newBuyerName) {
        if (!newBuyerName.empty()) {
            buyerName = newBuyerName;
        }
        else {
            cout << "Error: Buyer name cannot be empty." << endl;
        }
    }


    Buyer operator+(string& countryCode) {
        Buyer newBuyer = *this;
        newBuyer.buyerPhoneNumber = countryCode + newBuyer.buyerPhoneNumber;

        return newBuyer;
    }

    
    friend ostream& operator<<(ostream& out, Buyer& buyer) {
        out << "Buyer Name: " << buyer.buyerName << endl;
        out << "Buyer Email: " << (buyer.buyerEmail ? buyer.buyerEmail : "N/A") << endl;
        out << "Buyer Phone Number: " << buyer.buyerPhoneNumber << endl;
        out << "Age: " << buyer.age << endl;
        out << "Ticket ID: " << buyer.ticketId << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Buyer& buyer) {
        cout << "Enter buyer name: ";
        getline(in, buyer.buyerName);

        char* tempEmail = new char[256]; 
        cout << "Enter buyer email: ";
       // in.ignore(); 
        in.getline(tempEmail, 256);
        buyer.buyerEmail = new char[strlen(tempEmail) + 1];
        strcpy_s(buyer.buyerEmail, strlen(tempEmail) + 1, tempEmail);
        delete[] tempEmail;

        cout << "Enter buyer phone number: ";
        getline(in, buyer.buyerPhoneNumber);
        cout << "Enter age: ";
        in >> buyer.age;
        cout << "Enter ticket ID: ";
        in >> buyer.ticketId;

        return in;
    }
};
string Buyer::eventName = "Default";


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

    Date eventDate(25, 12, 2023);
    Event constParam2("Constructor 2", eventDate, 90);

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
    Event original("Original", 1, 1, 2023, 60, 100);
    cout << "Original Event:\n" << original;

    Event newEvent = original + 15;
    cout << "New event duration:\n" << newEvent;


    Event opPPtest("Opp", 1, 1, 2023, 60, 100);
    cout << "Initial Seats: " << opPPtest.getMaxSeats() << endl;
    ++opPPtest;
    cout << "Updated Seats: " << opPPtest.getMaxSeats() << endl;


    Event event6("Bool! test", 1, 1, 2023, 60, 100);
    if (!event6) {
        cout << "Event name is too short!" << endl;
    }
    else {
        cout << "Event name is valid." << endl;
    }

    event6.showEvent();
    event6.displayEventInfo();

    if (event3 == event6) {
        cout << "Events are the same." << endl;
    }
    else {
        cout << "Events are not the same." << endl;
    }

    //test istream
 /*   Date inputDate;
    cout << "Enter a date:\n";
    cin >> inputDate;
    cout << "Entered date: " << inputDate << endl;

    Event inputEvent;
    cout << "\nEnter event details:\n";
    cin >> inputEvent;
    cout << "Entered event details:\n" << inputEvent;*/


    //Test ticket class
    Ticket defaultTicket;
    cout << "Default Ticket:\n" << defaultTicket << endl;
    Ticket vipTicket("Ed Sheeran", "Theo", 15, VIP, 73);
    cout << "Basic Ticket:\n" << vipTicket << endl;

    string eventDesc[] = { "Front row", "VIP access" };
    Ticket detailedTicket("ColdPlay", "Theo si Geo", 12, 9, 2023, 120, 25, LOUNGE, 75.5, 2, eventDesc);
    cout << "Detailed Ticket:\n" << detailedTicket << endl;

    detailedTicket.displayEventDescriptions();

    Ticket ticket1;
    ticket1.setDate(12, 10, 2023);
    ticket1.setDuration(120);
    ticket1.setRowDesc(3);

    Ticket originalTicket("Concert", "Mimi", 10, VIP, 22);
    Ticket copiedTicket(originalTicket);
    cout << "Original Ticket:\n" << originalTicket << endl;
    cout << "Copied Ticket:\n" << copiedTicket << endl;

    string eventDescr[] = { "Front row", "STANDARD ACCESS" };
    Ticket originalTicket1("Concert", "Bob", 01, 11, 2025, 90, 20, STANDING, 99.99, 2, eventDescr);
    Ticket copiedTicket1(originalTicket1);
    cout << "Original Ticket1:\n" << originalTicket1 << endl;
    cout << "Copied Ticket1:\n" << copiedTicket1 << endl;

    Ticket newprice = detailedTicket + 10;
    cout << "Discounted Ticket:\n" << newprice << endl;


    Ticket ticket3("Untold", "eu", 10, VIP, 96.5);
    cout << "Original:\n" << ticket3 << endl;
    --ticket3;
    cout << "Reduced price:\n" << ticket3 << endl;
    Ticket newTicket(ticket3);
    newTicket--;
    cout << "New Ticket :\n" << newTicket << endl;
    newTicket.displayTicketInfo();

    cout << "Is Default Ticket Valid: " << (!defaultTicket ? "Invalid" : "Valid") << endl;
    cout << "Is VIP Ticket Valid: " << (!vipTicket ? "Invalid" : "Valid") << endl;


    //test istream ticket
    /*Ticket inputTicket;
    cout << "\nEnter ticket details:\n";
    cin >> inputTicket;
    cout << "Entered ticket details:\n" << inputTicket;*/

    // Test Buyer class
    Buyer buyer1;

    const char* email = "buyer1@example.com";
    Buyer buyer2("miiii mi", email, "123-456-7890", 25, 1);

    Buyer buyer3("ssss mm", "987-654-3210", 30);
    Buyer buyer4 = buyer3;
    if (buyer3 == buyer4) {
        cout << "Buyer 3 and Buyer 4 are equal.\n";
    }
    else {
        cout << "Buyer 3 and Buyer 4 are not equal.\n";
    }

    cout << "Buyer 1 Name: " << buyer1.getBuyerName() << endl;
    cout << "Buyer 2 Age: " << buyer2.getAge() << endl;
    string countryCode = "+1";
    Buyer newBuyer = buyer2 + countryCode;
    cout << "Buyer 2 with updated phone number: " << newBuyer << endl;
    
};
