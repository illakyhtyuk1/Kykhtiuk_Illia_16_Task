#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Dormitory {
    string name;
    string address;
    int roomsCount;
    int residentsCount;
    string commandant;
};

void addDormitory(const string& filename) {
    ofstream outFile(filename, ios::app);
    if (!outFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    Dormitory d;
    cout << "Enter dormitory name: "; cin.ignore(); getline(cin, d.name);
    cout << "Enter address: "; getline(cin, d.address);
    cout << "Enter number of rooms: "; cin >> d.roomsCount;
    cout << "Enter number of residents: "; cin >> d.residentsCount;
    cout << "Enter commandant's full name: "; cin.ignore(); getline(cin, d.commandant);

    outFile << d.name << "|" << d.address << "|" << d.roomsCount << "|"
        << d.residentsCount << "|" << d.commandant << endl;

    outFile.close();
    cout << "Data saved successfully!\n";
}

vector<Dormitory> getAllDormitories(const string& filename) {
    vector<Dormitory> dorms;
    ifstream inFile(filename);
    if (!inFile) return dorms;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string item;
        Dormitory d;
        vector<string> fields;

        while (getline(ss, item, '|')) {
            fields.push_back(item);
        }

        if (fields.size() == 5) {
            d.name = fields[0];
            d.address = fields[1];
            d.roomsCount = stoi(fields[2]);
            d.residentsCount = stoi(fields[3]);
            d.commandant = fields[4];
            dorms.push_back(d);
        }
    }
    inFile.close();
    return dorms;
}

void showStatistics(const vector<Dormitory>& dorms) {
    if (dorms.empty()) {
        cout << "The list is empty." << endl;
        return;
    }

    const Dormitory* maxRooms = &dorms[0];
    const Dormitory* maxResidents = &dorms[0];

    for (const auto& d : dorms) {
        if (d.roomsCount > maxRooms->roomsCount) maxRooms = &d;
        if (d.residentsCount > maxResidents->residentsCount) maxResidents = &d;
    }

    cout << "\n--- Statistics ---\n";
    cout << "Dormitory with most rooms (" << maxRooms->roomsCount << "): " << maxRooms->name << endl;
    cout << "Dormitory with most students (" << maxResidents->residentsCount << "): " << maxResidents->name << endl;
}

int main() {
    string filename = "dormitories.txt";
    int choice;

    do {
        cout << "\n1. Add Dormitory\n2. View All\n3. Show Statistics\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            addDormitory(filename);
        }
        else if (choice == 2) {
            vector<Dormitory> dorms = getAllDormitories(filename);
            for (const auto& d : dorms) {
                cout << d.name << " | " << d.address << " | Rooms: " << d.roomsCount
                    << " | Residents: " << d.residentsCount << " | Com.: " << d.commandant << endl;
            }
        }
        else if (choice == 3) {
            vector<Dormitory> dorms = getAllDormitories(filename);
            showStatistics(dorms);
        }
    } while (choice != 0);

    return 0;
}
