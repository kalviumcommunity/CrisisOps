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

public:
    
    Incident(string type, int severity, string location)
        : type(type), severity(severity), location(location), status("pending") {}

    void updateStatus(string newStatus) {
        status = newStatus;
    }

    string getType() const {
        return type;
    }

    string getLocation() const {
        return location;
    }

    // display details
    void displayDetails() const {
        cout << "Incident Type: " << type << "\n"
             << "Severity: " << severity << "\n"
             << "Location: " << location << "\n"
             << "Status: " << status << endl;
    }
};

// Responder Class
class Responder {
private:
    string name;        
    string type;        
    bool available;     

public:
    
    Responder(string name, string type)
        : name(name), type(type), available(true) {}

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

// City Class
class City {
private:
    vector<Incident> incidents;    
    vector<Responder> responders;  

public:
    City(Incident incs[], int incCount, Responder resps[], int respCount) {
        for (int i = 0; i < incCount; i++) {
            this->incidents.push_back(incs[i]);
        }
        for (int i = 0; i < respCount; i++) {
            this->responders.push_back(resps[i]);
        }
    }

    void logIncident(Incident incident) {
        incidents.push_back(incident);
        cout << "New incident logged: " << incident.getType()
             << " at " << incident.getLocation() << "." << endl;
    }

    void addResponder(Responder responder) {
        responders.push_back(responder);
    }

    void dispatchResponder(Responder& responder, Incident& incident) {
        responder.respondToIncident(incident);
    }

    void displayCityStatus() const {
        cout << "City Status Overview:\n" << endl;

        cout << "Incidents:\n";
        for (const auto& incident : incidents) {
            incident.displayDetails();
            cout << "-------------------\n";
        }

        cout << "Responders:\n";
        for (const auto& responder : responders) {
            responder.displayDetails();
            cout << "-------------------\n";
        }
    }
};

int main() {
    Incident incidentsArray[] = {
        Incident("Fire", 5, "peelamedu"),
        Incident("Medical", 3, "RSpuram")
    };

    Responder respondersArray[] = {
        Responder("Kamalesh", "Firefighter"),
        Responder("Dharini", "Medic")
    };

    City city(incidentsArray, 2, respondersArray, 2);

    city.dispatchResponder(respondersArray[0], incidentsArray[0]);
    city.dispatchResponder(respondersArray[1], incidentsArray[1]);

    city.displayCityStatus();

    return 0;
}
