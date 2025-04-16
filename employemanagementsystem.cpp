

//    // *************** EMPLOYMENT MANAGEMENT SYSTEM ***************//
// #include <iostream>
// #include <string>
// #include <limits>
// using namespace std;

// class employee {
// protected:
//     int empID;
//     string name;
// public:
//     void inputBasicInfo() {
//         cout << "Enter Employee ID: ";
//         cin >> empID;
//         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Prevent unwanted input issues
//         cout << "Enter Employee Name: ";
//         getline(cin, name);
//     }
//     void DisplayBasicInfo() const {
//         cout << "\n----- Basic Information -----\n";
//         cout << "Employee ID (in integers): " << empID << endl;
//         cout << "Employee Name: " << name << endl;
//     }
//     virtual void inputInfo() = 0;
//     virtual void calculateSalary() const = 0;
// };

// class visitingEmp : public employee {
// private:
//     int numberOfDays;
//     float dailyWages;
// public:
//     void inputInfo() {
//         cout << "Enter Daily Wages: ";
//         cin >> dailyWages;
//         if (dailyWages < 0) {
//             cout << "Error: Daily wages cannot be negative. Setting to 0.\n";
//             dailyWages = 0;
//         }
//         cout << "Enter Number of Days: ";
//         cin >> numberOfDays;
//         if (numberOfDays < 0) {
//             cout << "Error: Number of days cannot be negative. Setting to 0.\n";
//             numberOfDays = 0;
//         }
//     }
//     void calculateSalary() const {
//         float salary = dailyWages * numberOfDays;
//         cout << "Salary: " << salary << endl;
//     }
// };

// class permanentEmp : public employee {
// private:
//     int monthlySalary;
// public:
//     void inputInfo() {
//         cout << "Enter Monthly Salary: ";
//         cin >> monthlySalary;
//         if (monthlySalary < 0) {
//             cout << "Error: Monthly salary cannot be negative. Setting to 0.\n";
//             monthlySalary = 0;
//         }
//     }
//     void calculateSalary() const {
//         cout << "Salary: " << monthlySalary << " per month" << endl;
//     }
// };

// int main() {
//     employee* Emp = nullptr;
//     int choice;

//     do {
//         cout << "\n---- Main Menu ----\n";
//         cout << "1. Create Visiting Employee\n";
//         cout << "2. Create Permanent Employee\n";
//         cout << "0. Exit Program\n";
//         cout << "Enter Your Choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1:
//                 delete Emp;  // Prevent memory leak
//                 Emp = new visitingEmp();
//                 break;
//             case 2:
//                 delete Emp;  // Prevent memory leak
//                 Emp = new permanentEmp();
//                 break;
//             case 0:
//                 cout << "Exiting Program...\n";
//                 break;
//             default:
//                 cout << "Invalid choice! Please enter a correct number.\n";
//                 continue;
//         }

//         if (choice != 0) {
//             Emp->inputBasicInfo();
//             Emp->inputInfo();
//             cout << "\nEmployee Information\n";
//             Emp->DisplayBasicInfo();
//             Emp->calculateSalary();
//         }

//     } while (choice != 0);

//     delete Emp;  // Ensure cleanup before exit
//     return 0;
// }
// *************** ADVANCED EMPLOYMENT MANAGEMENT SYSTEM ***************//
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

// Utility functions
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

class Employee {
protected:
    int empID;
    string name;
    string joinDate;
    string department;
    string position;
    string contactNumber;
    string email;

public:
    virtual ~Employee() = default;

    void inputBasicInfo() {
        cout << "\n--- Employee Basic Information ---\n";
        
        cout << "Enter Employee ID: ";
        while (!(cin >> empID)) {
            cout << "Invalid input. Please enter a numeric ID: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        
        cout << "Enter Employee Name: ";
        getline(cin, name);
        
        cout << "Enter Join Date (YYYY-MM-DD, leave blank for today): ";
        getline(cin, joinDate);
        if (joinDate.empty()) {
            joinDate = getCurrentDate();
        }
        
        cout << "Enter Department: ";
        getline(cin, department);
        
        cout << "Enter Position: ";
        getline(cin, position);
        
        cout << "Enter Contact Number: ";
        getline(cin, contactNumber);
        
        cout << "Enter Email: ";
        getline(cin, email);
    }

    void displayBasicInfo() const {
        cout << "\n----- Basic Information -----\n";
        cout << "Employee ID: " << empID << endl;
        cout << "Name: " << name << endl;
        cout << "Join Date: " << joinDate << endl;
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        cout << "Contact: " << contactNumber << endl;
        cout << "Email: " << email << endl;
    }

    virtual void inputAdditionalInfo() = 0;
    virtual void calculateSalary() const = 0;
    virtual void displayAllInfo() const = 0;
    virtual string getType() const = 0;
    
    int getID() const { return empID; }
    string getName() const { return name; }
};

class VisitingEmployee : public Employee {
private:
    int numberOfDays;
    float dailyWages;
    string contractEndDate;

public:
    void inputAdditionalInfo() override {
        cout << "\n--- Visiting Employee Details ---\n";
        
        cout << "Enter Daily Wages: ";
        while (!(cin >> dailyWages) || dailyWages < 0) {
            cout << "Invalid input. Please enter a positive number: ";
            clearInputBuffer();
        }
        
        cout << "Enter Number of Days Worked: ";
        while (!(cin >> numberOfDays) || numberOfDays < 0) {
            cout << "Invalid input. Please enter a positive integer: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        
        cout << "Enter Contract End Date (YYYY-MM-DD): ";
        getline(cin, contractEndDate);
    }

    void calculateSalary() const override {
        float salary = dailyWages * numberOfDays;
        cout << "\n----- Salary Calculation -----\n";
        cout << "Daily Wages: " << dailyWages << endl;
        cout << "Days Worked: " << numberOfDays << endl;
        cout << "Total Salary: " << fixed << setprecision(2) << salary << endl;
    }

    void displayAllInfo() const override {
        displayBasicInfo();
        cout << "\n----- Employment Details -----\n";
        cout << "Employee Type: Visiting" << endl;
        cout << "Daily Wages: " << dailyWages << endl;
        cout << "Days Worked: " << numberOfDays << endl;
        cout << "Contract End Date: " << contractEndDate << endl;
        calculateSalary();
    }
    
    string getType() const override { return "Visiting"; }
};

class PermanentEmployee : public Employee {
private:
    float monthlySalary;
    float bonus;
    int yearsOfService;
    string bankAccount;

public:
    void inputAdditionalInfo() override {
        cout << "\n--- Permanent Employee Details ---\n";
        
        cout << "Enter Monthly Salary: ";
        while (!(cin >> monthlySalary) || monthlySalary < 0) {
            cout << "Invalid input. Please enter a positive number: ";
            clearInputBuffer();
        }
        
        cout << "Enter Bonus: ";
        while (!(cin >> bonus) || bonus < 0) {
            cout << "Invalid input. Please enter a positive number: ";
            clearInputBuffer();
        }
        
        cout << "Enter Years of Service: ";
        while (!(cin >> yearsOfService) || yearsOfService < 0) {
            cout << "Invalid input. Please enter a positive integer: ";
            clearInputBuffer();
        }
        clearInputBuffer();
        
        cout << "Enter Bank Account Number: ";
        getline(cin, bankAccount);
    }

    void calculateSalary() const override {
        float totalSalary = monthlySalary + bonus;
        cout << "\n----- Salary Calculation -----\n";
        cout << "Monthly Salary: " << fixed << setprecision(2) << monthlySalary << endl;
        cout << "Bonus: " << bonus << endl;
        cout << "Total Salary: " << totalSalary << endl;
    }

    void displayAllInfo() const override {
        displayBasicInfo();
        cout << "\n----- Employment Details -----\n";
        cout << "Employee Type: Permanent" << endl;
        cout << "Monthly Salary: " << fixed << setprecision(2) << monthlySalary << endl;
        cout << "Bonus: " << bonus << endl;
        cout << "Years of Service: " << yearsOfService << endl;
        cout << "Bank Account: " << bankAccount << endl;
        calculateSalary();
    }
    
    string getType() const override { return "Permanent"; }
};

class EmployeeManager {
private:
    vector<unique_ptr<Employee>> employees;
    
    int generateUniqueID() const {
        static int nextID = 1000;
        return nextID++;
    }
    
    void saveToFile() const {
        ofstream outFile("employees.dat");
        if (!outFile) {
            cerr << "Error: Could not open file for writing.\n";
            return;
        }
        
        for (const auto& emp : employees) {
            outFile << emp->getType() << "\n";
            outFile << emp->getID() << "\n";
            // Add other fields as needed
            // In a real application, we would save all employee data
        }
        
        cout << "Employee data saved to file.\n";
    }
    
    void loadFromFile() {
        ifstream inFile("employees.dat");
        if (!inFile) {
            cout << "No existing employee data found.\n";
            return;
        }
        
        string type;
        int id;
        while (getline(inFile, type)) {
            inFile >> id;
            inFile.ignore();
            
            // In a real application, we would load all employee data
            // and create the appropriate employee objects
            cout << "Loaded employee: " << id << " (" << type << ")\n";
        }
    }

public:
    EmployeeManager() {
        loadFromFile();
    }
    
    ~EmployeeManager() {
        saveToFile();
    }
    
    void addEmployee() {
        int choice;
        cout << "\n--- Add New Employee ---\n";
        cout << "1. Add Visiting Employee\n";
        cout << "2. Add Permanent Employee\n";
        cout << "0. Cancel\n";
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        unique_ptr<Employee> emp;
        
        switch (choice) {
            case 1:
                emp = make_unique<VisitingEmployee>();
                break;
            case 2:
                emp = make_unique<PermanentEmployee>();
                break;
            case 0:
                default:
                return;
        }
        
        emp->inputBasicInfo();
        emp->inputAdditionalInfo();
        employees.push_back(move(emp));
        cout << "\nEmployee added successfully!\n";
    }
    
    void displayAllEmployees() const {
        if (employees.empty()) {
            cout << "\nNo employees in the system.\n";
            return;
        }
        
        cout << "\n--- Employee List (" << employees.size() << ") ---\n";
        for (const auto& emp : employees) {
            emp->displayAllInfo();
            cout << "------------------------------\n";
        }
    }
    
    void findEmployee() const {
        if (employees.empty()) {
            cout << "\nNo employees in the system.\n";
            return;
        }
        
        int searchChoice;
        cout << "\n--- Find Employee ---\n";
        cout << "1. Search by ID\n";
        cout << "2. Search by Name\n";
        cout << "0. Cancel\n";
        cout << "Enter your choice: ";
        cin >> searchChoice;
        clearInputBuffer();
        
        if (searchChoice == 0) return;
        
        if (searchChoice == 1) {
            int id;
            cout << "Enter Employee ID to search: ";
            cin >> id;
            clearInputBuffer();
            
            bool found = false;
            for (const auto& emp : employees) {
                if (emp->getID() == id) {
                    emp->displayAllInfo();
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                cout << "Employee with ID " << id << " not found.\n";
            }
        } else if (searchChoice == 2) {
            string name;
            cout << "Enter Employee Name to search: ";
            getline(cin, name);
            
            bool found = false;
            for (const auto& emp : employees) {
                if (emp->getName().find(name) != string::npos) {
                    emp->displayAllInfo();
                    found = true;
                    cout << "------------------------------\n";
                }
            }
            
            if (!found) {
                cout << "No employees with name containing '" << name << "' found.\n";
            }
        }
    }
    
    void deleteEmployee() {
        if (employees.empty()) {
            cout << "\nNo employees in the system.\n";
            return;
        }
        
        int id;
        cout << "\n--- Delete Employee ---\n";
        cout << "Enter Employee ID to delete: ";
        cin >> id;
        clearInputBuffer();
        
        auto it = find_if(employees.begin(), employees.end(), 
            [id](const unique_ptr<Employee>& emp) { return emp->getID() == id; });
            
        if (it != employees.end()) {
            cout << "Deleting employee: " << (*it)->getName() << " (ID: " << id << ")\n";
            employees.erase(it);
            cout << "Employee deleted successfully.\n";
        } else {
            cout << "Employee with ID " << id << " not found.\n";
        }
    }
    
    void showStatistics() const {
        if (employees.empty()) {
            cout << "\nNo employees in the system.\n";
            return;
        }
        
        int visitingCount = 0;
        int permanentCount = 0;
        
        for (const auto& emp : employees) {
            if (emp->getType() == "Visiting") {
                visitingCount++;
            } else {
                permanentCount++;
            }
        }
        
        cout << "\n--- Employee Statistics ---\n";
        cout << "Total Employees: " << employees.size() << endl;
        cout << "Visiting Employees: " << visitingCount << endl;
        cout << "Permanent Employees: " << permanentCount << endl;
        cout << "---------------------------\n";
    }
};

void displayMainMenu() {
    cout << "\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n";
    cout << "1. Add New Employee\n";
    cout << "2. Display All Employees\n";
    cout << "3. Find Employee\n";
    cout << "4. Delete Employee\n";
    cout << "5. Employee Statistics\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    EmployeeManager manager;
    int choice;
    
    do {
        displayMainMenu();
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                manager.addEmployee();
                break;
            case 2:
                manager.displayAllEmployees();
                break;
            case 3:
                manager.findEmployee();
                break;
            case 4:
                manager.deleteEmployee();
                break;
            case 5:
                manager.showStatistics();
                break;
            case 0:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}