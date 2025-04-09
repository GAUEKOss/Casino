#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Structure to represent of War Country data
struct  warCountry{
    string Country;
    int id; //Unique ID for each country
    int branches;   //Like does it have a navy, army, airforce, helicopter corp and trunsport park
    string Branches; //What branches does it have
    string buysell; //Is this country producing or buying
};

//Class to represent of War Country data
class Warcountry{
    private:
        map<string, warCountry> countryData; 
        vector<string> countryNames; 
        vector<string> countryBranches;
        int numCountries; 
        const string filename = "country.dat";

    public:
        Warcountry(){ loadFromFile(); }; 

        //Function to add new country to map
        void addCountry(string Country, int id, int branches, string Branches, string buysell) {
            warCountry newCountry;
            newCountry.Country = Country;
            newCountry.id = id;
            newCountry.branches = branches;
            newCountry.Branches = Branches;
            newCountry.buysell = buysell;

            countryData[Country] = newCountry; //Add to map
            countryNames.push_back(Country); //Add to vector
            numCountries++; //Increment number of countries
            saveToFile(); //Save to file
            cout << "Country added successfully!\n";
        }
        
        //Function to display all countries
        void displayCountries() {
            cout << "Countries:\n";
            for (const auto& country : countryNames) {
                cout << country << "\n";
                cout << "ID: " << countryData[country].id << "\n";
                cout << "Branches: " << countryData[country].Branches << "\n"; 
                }
        };

        //Function to search country by ID
        void searchCountryByID(int id){
            for (const auto& country : countryNames) {
                if (countryData[country].id == id) {
                    cout << "Country found: " << country << "\n";
                    cout << "Branches: " << countryData[country].Branches << "\n"; 
                    return;
                }
            }
            cout << "Country with ID " << id << " not found.\n";
        };

        //Function to search country by name
        void searchCountryByName(string name){
            if (countryData.find(name) != countryData.end()) {
                cout << "Country found: " << name << "\n";
                cout << "ID: " << countryData[name].id << "\n";
                cout << "Branches: " << countryData[name].Branches << "\n"; 
            } else {
                cout << "Country " << name << " not found.\n";
            }
        };

        //Function to show military branches
        void showMilitaryBranches(string Country){
                if (countryData.find(Country) != countryData.end()) {
                    cout << "Number of branches: " << countryData[Country].branches << "\n";
                    cout << "Military Branches of " << Country << ":\n";
                    cout << countryData[Country].Branches << "\n";
                } else {
                    cout << "Country " << Country << " not found.\n";
                }
        };

        //Function to show is the country is producing or buying
        void showProductionOrBuying(string Country, string buysell){
            if (countryData.find(Country) != countryData.end()) {
                cout << "Country " << Country << " is " << countryData[Country].buysell << ".\n";
            } else {
                cout << "Country " << Country << " not found.\n";
            }
        };

        //Function to load data from file
        void loadFromFile(){
            ifstream file(filename);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    warCountry country;
                    // Assuming the file format is: Country,ID,Branches,Branches,Buysell
                    size_t pos = 0;
                    pos = line.find(",");
                    country.Country = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(",");
                    country.id = stoi(line.substr(0, pos));
                    line.erase(0, pos + 1);

                    pos = line.find(",");
                    country.branches = stoi(line.substr(0, pos));
                    line.erase(0, pos + 1);

                    country.Branches = line.substr(0, line.find(","));
                    country.buysell = line.substr(line.find(",") + 1);

                    countryData[country.Country] = country;
                    countryNames.push_back(country.Country);
                }
                file.close();
            }
        };

        //Function to save data to file
        void saveToFile(){
            ofstream file(filename);
            if (file.is_open()) {
                for (const auto& country : countryNames) {
                    file << countryData[country].Country << ","
                         << countryData[country].id << ","
                         << countryData[country].branches << ","
                         << countryData[country].Branches << ","
                         << countryData[country].buysell << "\n";
                }
                file.close();
            }
        };

        //Function to get the number of countries
        int getNumCountries(){
            return numCountries;
        }
};

//Function to display the country menu
void displayCountriesMenu(){
    Warcountry db;
    int choice, id, branches;
    string Country, Branches, buysell;

    while (true) {
        cout << "\n--- Country Menu ---\n";
        cout << "1. Add Country\n";
        cout << "2. Display All Countries\n";
        cout << "3. Search Country by ID\n";
        cout << "4. Search Country by Name\n";
        cout << "5. Show Military Branches\n";
        cout << "6. Show Production or Buying\n";
        cout << "7. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Country Name: ";
                cin >> Country;
                cout << "Enter Country ID: ";
                cin >> id;
                cout << "Enter Number of Branches: ";
                cin >> branches;
                cout << "Enter Military Branches: ";
                cin >> Branches;
                cout << "Is the country producing or buying? ";
                cin >> buysell;
                db.addCountry(Country, id, branches, Branches, buysell);
                break;
            case 2:
                db.displayCountries();
                break;
            case 3:
                cout << "Enter Country ID to search: ";
                cin >> id;
                db.searchCountryByID(id);
                break;
            case 4:
                cout << "Enter Country Name to search: ";
                cin >> Country;
                db.searchCountryByName(Country);
                break;
            case 5:
                cout << "Enter Military Branches to show: ";
                cin >> Branches;
                db.showMilitaryBranches(Country);
                break;
            case 6:
                cout << "Enter Country Name to show production or buying status: ";
                cin >> Country;
                db.showProductionOrBuying(Country, buysell);
                break;
            case 7:
                return; //Back to main menu
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
};

//Structure to represent branches type data
struct BranchType{
    string name;
    int id; //Unique ID for each branch
    string type; //Type of branch
    int numViechales; //Number of vehicles
    string vehicles; //What vehicles does it have
};

//Class to represent branches type data
class Typebranches{
    private:
        map<string, BranchType> branchesData; 
        vector<string> branchesNames; 
        vector<string> branchesTypes;
        int numBranches; 
        const string filename = "branches.dat";

    public:
        Typebranches(){ loadFromFile(); }; 

        //Function to add new branch to map
        void addBranch(string name, int id, string type, int numViechales, string vehicles) {
            BranchType newBranch;
            newBranch.name = name;
            newBranch.id = id;
            newBranch.type = type;
            newBranch.numViechales = numViechales;
            newBranch.vehicles = vehicles;

            branchesData[name] = newBranch; // Add to map

            branchesData[name] = newBranch; //Add to map
            branchesNames.push_back(name); //Add to vector
            numBranches++; //Increment number of branches
            saveToFile(); //Save to file
            cout << "Branch added successfully!\n";
        }

        //Function to display all branches
        void displayBranches(){
            cout << "Branches:\n";
            for (const auto& branch : branchesNames) {
                cout << branch << "\n";
                cout << "ID: " << branchesData[branch].id << "\n";
                cout << "Type: " << branchesData[branch].type << "\n"; 
            }
        }

        //Function to search branch by ID
        void searchBranchByID(int id){
            for (const auto& branch : branchesNames) {
                if (branchesData[branch].id == id) {
                    cout << "Branch found: " << branch << "\n";
                    cout << "Type: " << branchesData[branch].type << "\n"; 
                    return;
                }
            }
            cout << "Branch with ID " << id << " not found.\n";
        }

        //Function to search branch by name
        void searchBranchByName(string name){
            if (branchesData.find(name) != branchesData.end()) {
                cout << "Branch found: " << name << "\n";
                cout << "ID: " << branchesData[name].id << "\n";
                cout << "Type: " << branchesData[name].type << "\n"; 
            } else {
                cout << "Branch " << name << " not found.\n";
            }
        }

        //Function to show vehicles
        void showVehicles(string name, int numViechales){
            if (branchesData.find(name) != branchesData.end()) {
                cout << "Number of vehicles: " << branchesData[name].numViechales << "\n";
                cout << "Type of vehicles: " << branchesData[name].type << "\n";
                cout << "Vehicles of " << name << ":\n";
                cout << branchesData[name].vehicles << "\n";
            } else {
                cout << "Branch " << name << " not found.\n";
            }
        }

        //Function to load data from file
        void loadFromFile(){
            ifstream file(filename);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    BranchType branch;
                    // Assuming the file format is: Name,ID,Type,NumViechales,Vehicles
                    size_t pos = 0;
                    pos = line.find(",");
                    branch.name = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    pos = line.find(",");
                    branch.id = stoi(line.substr(0, pos));
                    line.erase(0, pos + 1);

                    pos = line.find(",");
                    branch.type = line.substr(0, pos);
                    line.erase(0, pos + 1);

                    branch.numViechales = stoi(line.substr(0, line.find(",")));
                    branch.vehicles = line.substr(line.find(",") + 1);

                    branchesData[branch.name] = branch;
                    branchesNames.push_back(branch.name);
                }
                file.close();
            }
        }

        //Function to save data to file
        void saveToFile(){
            ofstream file(filename);
            if (file.is_open()) {
                for (const auto& branch : branchesNames) {
                    file << branchesData[branch].name << ","
                         << branchesData[branch].id << ","
                         << branchesData[branch].type << ","
                         << branchesData[branch].numViechales << ","
                         << branchesData[branch].vehicles << "\n";
                }
                file.close();
            }
        }
        //Function to get the number of branches
        int getNumBranches(){
            return numBranches;
        }
};

//Function to display the branches menu
void displayBranchesMenu(){
    Typebranches db;
    int choice, id, numViechales;
    string name, type, vehicles;

    while (true) {
        cout << "\n--- Branches Menu ---\n";
        cout << "1. Add Branch\n";
        cout << "2. Display All Branches\n";
        cout << "3. Search Branch by ID\n";
        cout << "4. Search Branch by Name\n";
        cout << "5. Show Vehicles\n";
        cout << "6. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Branch Name: ";
                cin >> name;
                cout << "Enter Branch ID: ";
                cin >> id;
                cout << "Enter Branch Type: ";
                cin >> type;
                cout << "Enter Number of Vehicles: ";
                cin >> numViechales;
                cout << "Enter Vehicles: ";
                cin >> vehicles;
                db.addBranch(name, id, type, numViechales, vehicles);
                break;
            case 2:
                db.displayBranches();
                break;
            case 3:
                cout << "Enter Branch ID to search: ";
                cin >> id;
                db.searchBranchByID(id);
                break;
            case 4:
                cout << "Enter Branch Name to search: ";
                cin >> name;
                db.searchBranchByName(name);
                break;
            case 5:
                cout << "Enter Branch Name to show vehicles: ";
                cin >> name;
                db.showVehicles(name, numViechales);
                break;
            case 6:
                return; //Back to main menu
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

//Main function
int main (){
int choice;

while (true) {
    cout << "\n--- Main Menu ---\n";
    cout << "1. Country chooser\n";
    cout << "2. Branches chooser\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            displayCountriesMenu();
            break;
        case 2:
            displayBranchesMenu();
            break;
        case 3:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }
}
