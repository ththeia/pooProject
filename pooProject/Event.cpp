#include <iostream>
#include <string>

using namespace std;

class Event {
private:
    string name;
    string date;
    string time;
    int maxSeats;
    int* seatNumbers;

    //static int totalEvents;

public:
    const int DEFAULT_MAX_SEATS = 50;


public:
    Event() {
        name = "";
        date = "";
        time = "";
        maxSeats = 0;
        seatNumbers = nullptr;
    }

    Event(string name, string date, string time, int maxSeats) {
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


    Event(const Event& e) {
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
    bool isValid() const {
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


    operator string() const {
        return "Event: " + name + " - Date: " + date + " - Time: " + time;
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


};
