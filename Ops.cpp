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

    // update status of the incident
    void updateStatus(string newStatus) {
        status = newStatus;
    }

    // get type of the incident
    string getType() const {
        return type;
    }

    // get location of the incident
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

    // respond to a incident
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

    // update availability of the responder
    void updateAvailability(bool status) {
        available = status;
    }

    // display details of the responder
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
    // log newIncident
    void logIncident(Incident incident) {
        incidents.push_back(incident);
        cout << "New incident logged: " << incident.getType()
             << " at " << incident.getLocation() << "." << endl;
    }

    // add responder to the city
    void addResponder(Responder responder) {
        responders.push_back(responder);
    }

    // dispatch a responder
    void dispatchResponder(Responder& responder, Incident& incident) {
        responder.respondToIncident(incident);
    }

    // display the overall cityStatus
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

    City city;

    Incident fireIncident("Fire", 5, "peelamedu");
    Incident medicalIncident("Medical", 3, "RSpuram");

    city.logIncident(fireIncident);
    city.logIncident(medicalIncident);

    Responder johnDoe("Kamalesh", "Firefighter");
    Responder janeSmith("Dharini", "Medic");

    city.addResponder(johnDoe);
    city.addResponder(janeSmith);

    city.dispatchResponder(johnDoe, fireIncident);
    city.dispatchResponder(janeSmith, medicalIncident);

    city.displayCityStatus();

    return 0;
}