#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Incident Class
class Incident {
private:
    string type; // Encapsulation: Data members are private, protecting the type of the incident      
    int severity; // Encapsulation: Severity of the incident is hidden from direct access     
    string location; // Encapsulation: Location is private, controlled via methods
    string status; // Encapsulation: Status is also private, ensuring controlled access    

    static int totalIncidents;

public:
    Incident(string type, int severity, string location)
        : type(type), severity(severity), location(location), status("pending") {
        totalIncidents++; // Encapsulation: Increments total incidents, which is encapsulated within the class  
    }

    static int getTotalIncidents() {
        return totalIncidents;
    }

    void updateStatus(string newStatus) {
        status = newStatus;
    }

    string getType() const {
        return type;
    }

    string getLocation() const {
        return location;
    }

    void displayDetails() const {
        cout << "Incident Type: " << type << "\n"
             << "Severity: " << severity << "\n"
             << "Location: " << location << "\n"
             << "Status: " << status << endl;
    }
};

int Incident::totalIncidents = 0;

// Responder Class
class Responder {
private:
    string name; // Encapsulation: Name of the responder is private       
    string type;  // Encapsulation: Type of responder (e.g., firefighter, medic) is private       
    bool available; // Encapsulation: Availability status is private    

    static int totalResponders; // Encapsulation: Static data member to track the total number of responders

public:
    Responder(string name, string type)
        : name(name), type(type), available(true) {
        totalResponders++;  
    }

    static int getTotalResponders() {
        return totalResponders;
    }

    void respondToIncident(Incident& incident) {
        if (available) {
            cout << name << " is responding to a " << incident.getType()
                 << " at " << incident.getLocation() << "." << endl;
            available = false;
            incident.updateStatus("in progress");
        } else {
            cout << name << " is currently unavailable." << endl;
        }
    }

    void updateAvailability(bool status) {
        available = status;
    }

    void displayDetails() const {
        cout << "Responder Name: " << name << "\n"
             << "Type: " << type << "\n"
             << "Availability: " << (available ? "Available" : "Unavailable") << endl;
    }
};

int Responder::totalResponders = 0;

// City Class
class City {
private:
    vector<Incident*> incidents; // Encapsulation: The list of incidents is private   
    vector<Responder*> responders; // Encapsulation: The list of responders is private 

public:
    City(Incident* incs[], int incCount, Responder* resps[], int respCount) {
        for (int i = 0; i < incCount; i++) {
            this->incidents.push_back(incs[i]);
        }
        for (int i = 0; i < respCount; i++) {
            this->responders.push_back(resps[i]);
        }
    }

    void logIncident(Incident incident) {
        this->incidents.push_back(incident);
        cout << "New incident logged: " << incident.getType()
             << " at " << incident.getLocation() << "." << endl;
    }

    void addResponder(Responder responder) {
        this->responders.push_back(responder);
    }

    void dispatchResponder(Responder* responder, Incident* incident) {
        responder->respondToIncident(*incident);
    }

    void displayCityStatus() const {
        cout << "City Status Overview:\n" << endl;
        cout << "Total Incidents: " << Incident::getTotalIncidents() << endl;
        cout << "Total Responders: " << Responder::getTotalResponders() << endl;
        cout << "Incidents:\n";
        for (const auto& incident : this->incidents) {
            incident->displayDetails();
            cout << "-------------------\n";
        }
        cout << "Responders:\n";
        for (const auto& responder : this->responders) {
            responder->displayDetails();
            cout << "-------------------\n";
        }
    }

    ~City() {
        for (auto incident : incidents) {
            delete incident;
        }
        for (auto responder : responders) {
            delete responder;
        }
    }
};

int main() {
    Incident* incidentsArray[] = {
        new Incident("Fire", 5, "Peelamedu"),
        new Incident("Medical", 3, "R.S. Puram")
    };

    Responder* respondersArray[] = {
        new Responder("Kamalesh", "Firefighter"),
        new Responder("Dharini", "Medic")
    };

    City city(incidentsArray, 2, respondersArray, 2);

    city.dispatchResponder(respondersArray[0], incidentsArray[0]);
    city.dispatchResponder(respondersArray[1], incidentsArray[1]);

    city.displayCityStatus();

    return 0;
}
