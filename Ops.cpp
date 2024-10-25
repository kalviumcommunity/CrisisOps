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
        cout << "New incident logged: " << incident->getType()
             << " at " << incident->getLocation() << "." << endl;
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
