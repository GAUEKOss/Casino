#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std 

struct Student{
    string name;
    int rollNumber;
    int age;
    double grade;
};

struct classStudent{
private:
    vector<Student> students; 
    map<int, Student> studentMap; 
    const string filename = "students.dat";

public:
    StudentDatabase() { loadFromFile(); }
  
        void addStudent(const string& name, int rollNumber, int age, int grade) {
        Student newStudent;
        strncpy(newStudent.name, name.c_str(), sizeof(newStudent.name) - 1);
        newStudent.name[sizeof(newStudent.name) - 1] = '\0'; 
        newStudent.rollNumber = rollNumber;
        newStudent.age = age;
        newStudent.grade = grade;

        students.push_back(newStudent);
        studentMap[rollNumber] = newStudent;

        saveToFile();  
        cout << "Student added successfully!\n";
    }


    void displayAllStudents() {
        if (students.empty()) {
            cout << "No student records available.\n";
            return;
        }
        cout << "Student Records:\n";
        for (const auto& student : students) {
            cout << "Roll Number: " << student.rollNumber
                 << ", Name: " << student.name
                 << ", Age: " << student.age
                 << ", Grade: " << student.grade << "\n";
        }
    }

 
    void searchStudent(int rollNumber) {
        if (studentMap.find(rollNumber) != studentMap.end()) {
            Student s = studentMap[rollNumber];
            cout << "Student Found!\n"
                 << "Roll Number: " << s.rollNumber
                 << ", Name: " << s.name
                 << ", Age: " << s.age
                 << ", Grade: " << s.grade << "\n";
        } else {
            cout << "Student with Roll Number " << rollNumber << " not found.\n";
        }
    }


void deleteStudent(int rollNumber) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->rollNumber == rollNumber) {
                students.erase(it);
                studentMap.erase(rollNumber);
                saveToFile();  
                cout << "Student record deleted successfully!\n";
                return;
            }
        }
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }

    
    void saveToFile() {
        ofstream file(filename, ios::binary | ios::out);
        if (!file) {
            cout << "Error saving data!\n";
            return;
        }
        for (const auto& student : students) {
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        }
        file.close();
        cout << "Data saved successfully!\n";
    }

    
    void loadFromFile() {
        students.clear();
        studentMap.clear();
        ifstream file(filename, ios::binary | ios::in);
        if (!file) {
            cout << "No existing student data found. Starting fresh.\n";
            return;
        }
        Student temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
            students.push_back(temp);
            studentMap[temp.rollNumber] = temp;
        }
        file.close();
        cout << "Data loaded successfully!\n";
    }
};

int main() {
    StudentDatabase db;
    int choice, rollNumber, age, grade;
    string name;

    while (true) {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Grade (integer): ";
                cin >> grade;
                db.addStudent(name, rollNumber, age, grade);
                break;
            case 2:
                db.displayAllStudents();
                break;
            case 3:
                cout << "Enter Roll Number to Search: ";
                cin >> rollNumber;
                db.searchStudent(rollNumber);
                break;
            case 4:
                cout << "Enter Roll Number to Delete: ";
                cin >> rollNumber;
                db.deleteStudent(rollNumber);
                break;
            case 5:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
