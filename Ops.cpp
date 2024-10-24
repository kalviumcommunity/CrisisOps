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

    virtual void displayDetails() const {
        cout << "Incident Type: " << type << "\n"
             << "Severity: " << severity << "\n"
             << "Location: " << location << "\n"
             << "Status: " << status << endl;
    }
};

int Incident::totalIncidents = 0;

//TrafficIncident inherits from Incident
class TrafficIncident : public Incident {
public:
    TrafficIncident(int severity, string location)
        : Incident("Traffic", severity, location) {}
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

    virtual void respondToIncident(Incident& incident) {
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

    virtual void displayDetails() const {
        cout << "Responder Name: " << name << "\n"
             << "Type: " << type << "\n"
             << "Availability: " << (available ? "Available" : "Unavailable") << endl;
    }
};

int Responder::totalResponders = 0;

//Police inherits from Responder
class Police : public Responder {
public:
    Police(string name) : Responder(name, "Police") {}
};

//Firefighter inherits from Responder
class Firefighter : public Responder {
public:
    Firefighter(string name) : Responder(name, "Firefighter") {}
};

//Medic inherits from Responder
class Medic : public Responder {
public:
    Medic(string name) : Responder(name, "Medic") {}
};

class City {
private:
    vector<Incident*> incidents;
    vector<Responder*> responders;

public:
    City(Incident* incs[], int incCount, Responder* resps[], int respCount) {
        for (int i = 0; i < incCount; i++) {
            this->incidents.push_back(incs[i]);
        }
        for (int i = 0; i < respCount; i++) {
            this->responders.push_back(resps[i]);
        }
    }

    void logIncident(Incident* incident) {
        this->incidents.push_back(incident);
        cout << "New incident logged (by pointer): " << incident->getType()
             << " at " << incident->getLocation() << "." << endl;
    }

    void logIncident(Incident& incident) {
        this->incidents.push_back(&incident);
        cout << "New incident logged (by reference): " << incident.getType()
             << " at " << incident.getLocation() << "." << endl;
    }

    void addResponder(Responder* responder) {
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
        new TrafficIncident(2, "Anna Nagar"),
        new Incident("Medical", 3, "R.S. Puram")
    };

    Responder* respondersArray[] = {
        new Firefighter("Kamalesh"),
        new Medic("Dharini")
    };

    City city(incidentsArray, 2, respondersArray, 2);

    Incident* newIncident = new Incident("Fire", 4, "Peelamedu");
    city.logIncident(newIncident);  // overloaded method

    TrafficIncident anotherIncident(5, "Thudiyalur");
    city.logIncident(anotherIncident); 

    city.dispatchResponder(respondersArray[0], incidentsArray[0]);
    city.dispatchResponder(respondersArray[1], incidentsArray[1]);

    city.displayCityStatus();

    return 0;
}
