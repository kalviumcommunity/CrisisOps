#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Incident Class
class Incident {
private:
    string type;    
    int severity;      
    string location; 
    string status;     

    static int totalIncidents;


public:
    // Constructor: Initializes an Incident with type, severity, and location
    Incident(string type, int severity, string location)
        : type(type), severity(severity), location(location), status("pending") {
        totalIncidents++;
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
    string name;     
    string type;      
    bool available; 
  

    static int totalResponders; 

public:
// Constructor: Initializes a Responder with a name and type
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
    vector<Incident*> incidents;    
    vector<Responder*> responders;  

public:
    // Constructor: Initializes a City with arrays of incidents and responders
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

    // Destructor: Cleans up dynamically allocated memory for incidents and responders
    ~City() {
        for (auto incident : incidents) {
            delete incident; // Destructor cleans up Incident objects
        }
        for (auto responder : responders) {
            delete responder; // Destructor cleans up Responder objects
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
