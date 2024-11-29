#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base Incident class
class Incident {
protected:
    string type;
    int severity;
    string location;
    string status;

    static int totalIncidents;

public:
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

    virtual void displayDetails() const = 0;

    virtual ~Incident() {}
};

int Incident::totalIncidents = 0;

// TrafficIncident class
class TrafficIncident : public Incident {
public:
    TrafficIncident(int severity, string location)
        : Incident("Traffic", severity, location) {}

    void displayDetails() const override {
        cout << "Incident Type: " << type << "\n"
             << "Severity: " << severity << "\n"
             << "Location: " << location << "\n"
             << "Status: " << status << endl;
    }
};

// MedicalIncident class
class MedicalIncident : public Incident {
public:
    MedicalIncident(int severity, string location)
        : Incident("Medical", severity, location) {}

    void displayDetails() const override {
        cout << "Incident Type: " << type << "\n"
             << "Severity: " << severity << "\n"
             << "Location: " << location << "\n"
             << "Status: " << status << endl;
    }
};

// Responder class
class Responder {
protected:
    string name;
    string type;
    bool available;

    static int totalResponders;

public:
    Responder(string name, string type)
        : name(name), type(type), available(true) {
        totalResponders++;
    }

    static int getTotalResponders() {
        return totalResponders;
    }

    virtual void respondToIncident(Incident& incident) = 0;

    void updateAvailability(bool status) {
        available = status;
    }

    virtual void displayDetails() const {
        cout << "Responder Name: " << name << "\n"
             << "Type: " << type << "\n"
             << "Availability: " << (available ? "Available" : "Unavailable") << endl;
    }

    virtual ~Responder() {}
};

int Responder::totalResponders = 0;

// Police class
class Police : public Responder {
public:
    Police(string name) : Responder(name, "Police") {}

    void respondToIncident(Incident& incident) override {
        if (available) {
            cout << name << " (Police) is responding to a " << incident.getType()
                 << " at " << incident.getLocation() << "." << endl;
            available = false;
            incident.updateStatus("in progress");
        } else {
            cout << name << " is currently unavailable." << endl;
        }
    }
};

// Firefighter class
class Firefighter : public Responder {
public:
    Firefighter(string name) : Responder(name, "Firefighter") {}

    void respondToIncident(Incident& incident) override {
        if (available) {
            cout << name << " (Firefighter) is responding to a " << incident.getType()
                 << " at " << incident.getLocation() << "." << endl;
            available = false;
            incident.updateStatus("in progress");
        } else {
            cout << name << " is currently unavailable." << endl;
        }
    }
};

// Medic class
class Medic : public Responder {
public:
    Medic(string name) : Responder(name, "Medic") {}

    void respondToIncident(Incident& incident) override {
        if (available) {
            cout << name << " (Medic) is responding to a " << incident.getType()
                 << " at " << incident.getLocation() << "." << endl;
            available = false;
            incident.updateStatus("in progress");
        } else {
            cout << name << " is currently unavailable." << endl;
        }
    }
};

// IncidentManager class
class IncidentManager {
private:
    vector<Incident*> incidents;

public:
    void logIncident(Incident* incident) {
        incidents.push_back(incident);
        cout << "New incident logged: " << incident->getType()
             << " at " << incident->getLocation() << "." << endl;
    }

    const vector<Incident*>& getIncidents() const {
        return incidents;
    }

    ~IncidentManager() {
        for (auto incident : incidents) {
            delete incident;
        }
    }
};

// ResponderManager class
class ResponderManager {
private:
    vector<Responder*> responders;

public:
    void addResponder(Responder* responder) {
        responders.push_back(responder);
    }

    const vector<Responder*>& getResponders() const {
        return responders;
    }

    ~ResponderManager() {
        for (auto responder : responders) {
            delete responder;
        }
    }
};

// City class
class City {
private:
    IncidentManager incidentManager;
    ResponderManager responderManager;

public:
    City(Incident* incs[], int incCount, Responder* resps[], int respCount) {
        for (int i = 0; i < incCount; i++) {
            incidentManager.logIncident(incs[i]);
        }
        for (int i = 0; i < respCount; i++) {
            responderManager.addResponder(resps[i]);
        }
    }

    void dispatchResponder(Responder* responder, Incident* incident) {
        responder->respondToIncident(*incident);
    }

    void displayCityStatus() const {
        cout << "City Status Overview:\n" << endl;
        cout << "Total Incidents: " << Incident::getTotalIncidents() << endl;
        cout << "Total Responders: " << Responder::getTotalResponders() << endl;

        cout << "Incidents:\n";
        for (const auto& incident : incidentManager.getIncidents()) {
            incident->displayDetails();
            cout << "-------------------\n";
        }

        cout << "Responders:\n";
        for (const auto& responder : responderManager.getResponders()) {
            responder->displayDetails();
            cout << "-------------------\n";
        }
    }
};

// Main function
int main() {
    Incident* incidentsArray[] = {
        new TrafficIncident(2, "Anna Nagar"),
        new MedicalIncident(3, "R.S. Puram")
    };

    Responder* respondersArray[] = {
        new Firefighter("Kamalesh"),
        new Medic("Dharini")
    };

    City city(incidentsArray, 2, respondersArray, 2);

    city.dispatchResponder(respondersArray[0], incidentsArray[0]);
    city.dispatchResponder(respondersArray[1], incidentsArray[1]);

    city.displayCityStatus();

    return 0;
}
