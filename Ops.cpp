#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

class IIncidentManager {
public:
    virtual void logIncident(Incident* incident) = 0;
    virtual const vector<Incident*>& getIncidents() const = 0;
    virtual ~IIncidentManager() = default;
};

class IResponderManager {
public:
    virtual void addResponder(Responder* responder) = 0;
    virtual const vector<Responder*>& getResponders() const = 0;
    virtual ~IResponderManager() = default;
};

class IncidentManager : public IIncidentManager {
private:
    vector<Incident*> incidents;

public:
    void logIncident(Incident* incident) override {
        incidents.push_back(incident);
        cout << "New incident logged: " << incident->getType()
             << " at " << incident->getLocation() << "." << endl;
    }

    const vector<Incident*>& getIncidents() const override {
        return incidents;
    }

    ~IncidentManager() {
        for (auto incident : incidents) {
            delete incident;
        }
    }
};

class ResponderManager : public IResponderManager {
private:
    vector<Responder*> responders;

public:
    void addResponder(Responder* responder) override {
        responders.push_back(responder);
    }

    const vector<Responder*>& getResponders() const override {
        return responders;
    }

    ~ResponderManager() {
        for (auto responder : responders) {
            delete responder;
        }
    }
};

class City {
private:
    IIncidentManager& incidentManager;
    IResponderManager& responderManager;

public:
    City(IIncidentManager& im, IResponderManager& rm)
        : incidentManager(im), responderManager(rm) {}

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

int main() {
    IncidentManager incidentManager;
    ResponderManager responderManager;

    incidentManager.logIncident(new TrafficIncident(2, "Anna Nagar"));
    incidentManager.logIncident(new MedicalIncident(3, "R.S. Puram"));

    responderManager.addResponder(new Firefighter("Kamalesh"));
    responderManager.addResponder(new Medic("Dharini"));

    City city(incidentManager, responderManager);

    auto incidents = incidentManager.getIncidents();
    auto responders = responderManager.getResponders();

    city.dispatchResponder(responders[0], incidents[0]);
    city.dispatchResponder(responders[1], incidents[1]);

    city.displayCityStatus();

    return 0;
}
