#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <fstream> 

using namespace std;

// Structure to store student information
struct Student {
    char name[50];   // Fixed-size char array for binary file compatibility
    int rollNumber;
    int age;
    int grade;
};

// Class to manage student records
class StudentDatabase {
private:
    vector<Student> students;  // Store student records
    map<int, Student> studentMap; // Quick search using roll number
    const string filename = "students.dat";  // Binary file name

public:
    StudentDatabase() { loadFromFile(); }  // Load data when object is created

    // Function to add a new student
    void addStudent(const string& name, int rollNumber, int age, int grade) {
        Student newStudent;
        strncpy(newStudent.name, name.c_str(), sizeof(newStudent.name) - 1);
        newStudent.name[sizeof(newStudent.name) - 1] = '\0';  // Ensure null termination
        newStudent.rollNumber = rollNumber;
        newStudent.age = age;
        newStudent.grade = grade;

        students.push_back(newStudent);
        studentMap[rollNumber] = newStudent;

        saveToFile();  // Save after adding a new student
        cout << "Student added successfully!\n";
    }

    // Function to display all student records
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

    // Function to search for a student by roll number
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

    // Function to delete a student record
    void deleteStudent(int rollNumber) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->rollNumber == rollNumber) {
                students.erase(it);
                studentMap.erase(rollNumber);
                saveToFile();  // Save after deletion
                cout << "Student record deleted successfully!\n";
                return;
            }
        }
        cout << "Student with Roll Number " << rollNumber << " not found.\n";
    }

    // Function to save data to a binary file
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

    // Function to load data from a binary file
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

// Function to handle student operations
void studentFunction(){
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
                return ;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Structure to store employee information
struct Employee {
    int employeeID;
    string name;
    string department;
    string position;
    double salary;
   };

// Class to manage employee records
class EmployeeDatabase {
private:
    vector<Employee> employees;  // Store employee records
    map<int, Employee> employeeMap; // Quick search using employee ID
    const string filename = "employees.dat";  // Binary file name
public:
    EmployeeDatabase() { loadFromFile(); }  // Load data when object is created

    // Function to add a new employee
    void addEmployee(int employeeID, const string& name, const string& department, const string& position, double salary) {
        Employee newEmployee;
        newEmployee.employeeID = employeeID;
        newEmployee.name = name;
        newEmployee.department = department;
        newEmployee.position = position;
        newEmployee.salary = salary;

        employees.push_back(newEmployee);
        saveToFile();  // Save after adding a new employee
        cout << "Employee added successfully!\n";
    }

    // Function to display all employee records
    void displayAllEmployees() {
        if (employees.empty()) {
            cout << "No employee records available.\n";
            return;
        }
        cout << "Employee Records:\n";
        for (const auto& emp : employees) {
            cout << "Employee ID: " << emp.employeeID
                 << ", Name: " << emp.name
                 << ", Department: " << emp.department
                 << ", Position: " << emp.position
                 << ", Salary: $" << emp.salary << "\n";
        }
    }

    // Function to search for an employee by ID
    void searchEmployee(int employeeID) {
        for (const auto& emp : employees) {
            if (emp.employeeID == employeeID) {
                cout << "Employee Found!\n"
                     << "Employee ID: " << emp.employeeID
                     << ", Name: " << emp.name
                     << ", Department: " << emp.department
                     << ", Position: " << emp.position
                     << ", Salary: $" << emp.salary << "\n";
                return;
            }
        }
        cout << "Employee with ID " << employeeID << " not found.\n";
    }

    // Function to delete an employee record
    void deleteEmployee(int employeeID) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if (it->employeeID == employeeID) {
                employees.erase(it);
                saveToFile();  // Save after deletion
                cout << "Employee record deleted successfully!\n";
                return;
            }
        }
        cout << "Employee with ID " << employeeID << " not found.\n";
    }

    // Function to save data to a binary file
    void saveToFile() {
        ofstream file(filename, ios::binary | ios::out);
        if (!file) {
            cout << "Error saving data!\n";
            return;
        }
        for (const auto& emp : employees) {
            file.write(reinterpret_cast<const char*>(&emp), sizeof(Employee));
        }
        file.close();
        cout << "Data saved successfully!\n";
    }
    
    // Function to load data from a binary file
    void loadFromFile() {
        employees.clear();
        ifstream file(filename, ios::binary | ios::in);
        if (!file) {
            cout << "No existing employee data found. Starting fresh.\n";
            return;
        }
        Employee temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Employee))) {
            employees.push_back(temp);
        }
        file.close();
        cout << "Data loaded successfully!\n";
    }
    
    // Function to update employee details
    void updateEmployee(int employeeID, const string& name, const string& department, const string& position, double salary) {
        for (auto& emp : employees) {
            if (emp.employeeID == employeeID) {
                emp.name = name;
                emp.department = department;
                emp.position = position;
                emp.salary = salary;
                saveToFile();  // Save after updating
                cout << "Employee record updated successfully!\n";
                return;
            }
        }
        cout << "Employee with ID " << employeeID << " not found.\n";
    }
};

// Function to handle employee operations
void employeeFunction(){
    EmployeeDatabase db;
    int choice, employeeID;
    string name, department, position;
    double salary;

    // Menu loop for employee operations
    while (true) {
        cout << "\n--- Employee Database Menu ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee by ID\n";
        cout << "4. Delete Employee\n";
        cout << "5. Update Employee Details\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Employee ID: ";
                cin >> employeeID;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Department: ";
                getline(cin, department);
                cout << "Enter Position: ";
                getline(cin, position);
                cout << "Enter Salary: ";
                cin >> salary;
                db.addEmployee(employeeID, name, department, position, salary);
                break;
            case 2:
                db.displayAllEmployees();
                break;
            case 3:
                cout << "Enter Employee ID to Search: ";
                cin >> employeeID;
                db.searchEmployee(employeeID);
                break;
            case 4:
                cout << "Enter Employee ID to Delete: ";
                cin >> employeeID;
                db.deleteEmployee(employeeID);
                break;
            case 5:
                cout << "Enter Employee ID to Update: ";
                cin >> employeeID;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter New Department: ";
                getline(cin, department);
                cout << "Enter New Position: ";
                getline(cin, position);
                cout << "Enter New Salary: ";
                cin >> salary;
                db.updateEmployee(employeeID, name, department, position, salary);
                break;
            case 6:
                cout << "Exiting program...\n";
                return ;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Structure to store course task
struct CourseTask {

    int taskID;
    string taskName;
    string description;
    string dueDate;
};

// Class to manage course task records
class CourseTaskDatabase {
private:
    vector<CourseTask> tasks;  // Store course tasks
    map<int, CourseTask> taskMap; // Quick search using task ID
    const string filename = "tasks.dat";  // Binary file name
public:
    CourseTaskDatabase() { loadFromFile(); }  // Load data when object is created

    // Function to add a new course task
    void addTask(int taskID, const string& taskName, const string& description, const string& dueDate) {
        CourseTask newTask;
        newTask.taskID = taskID;
        newTask.taskName = taskName;
        newTask.description = description;
        newTask.dueDate = dueDate;

        tasks.push_back(newTask);
        taskMap[taskID] = newTask;

        saveToFile();  // Save after adding a new task
        cout << "Course Task added successfully!\n";
    }

    // Function to display all course tasks
    void displayAllTasks() {
        if (tasks.empty()) {
            cout << "No course tasks available.\n";
            return;
        }
        cout << "Course Tasks:\n";
        for (const auto& task : tasks) {
            cout << "Task ID: " << task.taskID
                 << ", Task Name: " << task.taskName
                 << ", Description: " << task.description
                 << ", Due Date: " << task.dueDate << "\n";
        }
    }

    // Function to search for a course task by ID
    void searchTask(int taskID) {
        if (taskMap.find(taskID) != taskMap.end()) {
            CourseTask t = taskMap[taskID];
            cout << "Course Task Found!\n"
                 << "Task ID: " << t.taskID
                 << ", Task Name: " << t.taskName
                 << ", Description: " << t.description
                 << ", Due Date: " << t.dueDate << "\n";
        } else {
            cout << "Course Task with ID " << taskID << " not found.\n";
        }
    }

    // Function to delete a course task record
    void deleteTask(int taskID) {
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->taskID == taskID) {
                tasks.erase(it);
                taskMap.erase(taskID);
                saveToFile();  // Save after deletion
                cout << "Course Task record deleted successfully!\n";
                return;
            }
        }
        cout << "Course Task with ID " << taskID << " not found.\n";
    }
    
    // Function to save data to a binary file
    void saveToFile() {
        ofstream file(filename, ios::binary | ios::out);
        if (!file) {
            cout << "Error saving data!\n";
            return;
        }
        for (const auto& task : tasks) {
            file.write(reinterpret_cast<const char*>(&task), sizeof(CourseTask));
        }
        file.close();
        cout << "Data saved successfully!\n";
    }

    // Function to load data from a binary file
    void loadFromFile() {
        tasks.clear();
        taskMap.clear();
        ifstream file(filename, ios::binary | ios::in);
        if (!file) {
            cout << "No existing course task data found. Starting fresh.\n";
            return;
        }
        CourseTask temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(CourseTask))) {
            tasks.push_back(temp);
            taskMap[temp.taskID] = temp;
        }
        file.close();
        cout << "Data loaded successfully!\n";
    }
};

// Function to handle course task operations
void courseTaskFunction(){
    CourseTaskDatabase db;
    int choice, taskID;
    string taskName, description, dueDate;

    while (true) {
        cout << "\n--- Course Task Database Menu ---\n";
        cout << "1. Add Course Task\n";
        cout << "2. Display All Course Tasks\n";
        cout << "3. Search Course Task by ID\n";
        cout << "4. Delete Course Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> taskID;
                cout << "Enter Task Name: ";
                cin.ignore();
                getline(cin, taskName);
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Due Date: ";
                getline(cin, dueDate);
                db.addTask(taskID, taskName, description, dueDate);
                break;
            case 2:
                db.displayAllTasks();
                break;
            case 3:
                cout << "Enter Task ID to Search: ";
                cin >> taskID;
                db.searchTask(taskID);
                break;
            case 4:
                cout << "Enter Task ID to Delete: ";
                cin >> taskID;
                db.deleteTask(taskID);
                break;
            case 5:
                cout << "Exiting program...\n";
                return ;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

//Structure to store library information
struct Library {
    int bookID;
    string title;
    string author;
    string genre;
    string borrower;
    int borrowerID;
    string dueDate;
};

// Class to manage library records
class LibraryDatabase {
private:
    vector<Library> books;  // Store library records
    map<int, Library> bookMap; // Quick search using book ID
    const string filename = "library.dat";  // Binary file name
public:
    LibraryDatabase() { loadFromFile(); }

    // Function to add a new book
    void addBook(int bookID, const string& title, const string& author, const string& genre) {
        Library newBook;
        newBook.bookID = bookID;
        newBook.title = title;
        newBook.author = author;
        newBook.genre = genre;

        books.push_back(newBook);
        bookMap[bookID] = newBook;

        saveToFile();  // Save after adding a new book
        cout << "Book added successfully!\n";
    }

    // Function to display all library records
    void displayAllBooks(){
        if(books.empty()){
            cout << "No library records available.\n";
            return;
        }
        cout << "Library Records:\n";
        for (const auto& book :books){
            cout << "Book ISNB: " << book.bookID
                 << ", Title: " << book.title
                 << ", Author: " << book.author
                 << ", Genre: " << book.genre
                 << ", Borrower: " << book.borrower
                 << ", Borrower ID: " << book.borrowerID
                 << ", Due Date: " << book.dueDate << "\n";
        }
    }

    // Function to search for a book by ID
    void searchBook(int bookID){
        if (bookMap.find(bookID) != bookMap.end()){
            Library b = bookMap[bookID];
            cout << "Book has been Found!\n"
                 << "Book ID: " << b.bookID
                 << ", Title: " << b.title << "\n";
        } else {
            cout << "Book with ID " << bookID << " not found.\n";
        }
    }

    // Function to delete a book record
    void deleteBook(int bookID) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->bookID == bookID) {
                books.erase(it);
                bookMap.erase(bookID);
                saveToFile();  // Save after deletion
                cout << "Book record deleted successfully!\n";
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }

    // Function to save data to a binary file
    void saveToFile() {
        ofstream file(filename, ios::binary | ios::out);
        if (!file) {
            cout << "Error saving data!\n";
            return;
        }
        for (const auto& book : books) {
            file.write(reinterpret_cast<const char*>(&book), sizeof(Library));
        }
        file.close();
        cout << "Data saved successfully!\n";
    }

    // Function to load data from a binary file
    void loadFromFile() {
        books.clear();
        bookMap.clear();
        ifstream file(filename, ios::binary | ios::in);
        if (!file) {
            cout << "No existing library data found. Starting fresh.\n";
            return;
        }
        Library temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Library))) {
            books.push_back(temp);
            bookMap[temp.bookID] = temp;
        }
        file.close();
        cout << "Data loaded successfully!\n";
    }

    // Function to update book details
    void updateBook(int bookID, const string& title, const string& author, const string& genre) {
        for (auto& book : books) {
            if (book.bookID == bookID) {
                book.title = title;
                book.author = author;
                book.genre = genre;
                saveToFile();  // Save after updating
                cout << "Book record updated successfully!\n";
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }
    
    // Function to borrow a book
    void borrowBook(int bookID, const string& borrower, int borrowerID, const string& dueDate) {
        for (auto& book : books) {
            if (book.bookID == bookID) {
                book.borrower = borrower;
                book.borrowerID = borrowerID;
                book.dueDate = dueDate;
                saveToFile();  // Save after borrowing
                cout << "Book borrowed successfully!\n";
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }
    
    // Function to return a book
    void returnBook(int bookID) {
        for (auto& book : books) {
            if (book.bookID == bookID) {
                book.borrower = "";
                book.borrowerID = 0;
                book.dueDate = "";
                saveToFile();  // Save after returning
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }
};

// Function to handle library operations
void libraryFunction(){
    LibraryDatabase db;
    int choice, bookID, borrowerID;
    string title, author, genre, borrower, dueDate;

    while (true) {
        cout << "\n--- Library Database Menu ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Delete Book\n";
        cout << "5. Update Book Details\n";
        cout << "6. Borrow Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> bookID;
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter Genre: ";
                getline(cin, genre);
                db.addBook(bookID, title, author, genre);
                break;
            case 2:
                db.displayAllBooks();
                break;
            case 3:
                cout << "Enter Book ID to Search: ";
                cin >> bookID;
                db.searchBook(bookID);
                break;
            case 4:
                cout << "Enter Book ID to Delete: ";
                cin >> bookID;
                db.deleteBook(bookID);
                break;
            case 5:
                cout << "Enter Book ID to Update: ";
                cin >> bookID;
                cout << "Enter New Title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter New Author: ";
                getline(cin, author);
                cout << "Enter New Genre: ";
                getline(cin, genre);
                db.updateBook(bookID, title, author, genre);
                break;
            case 6:
                cout << "Enter Book ID to Borrow: ";
                cin >> bookID;
                cout << "Enter Borrower Name: ";
                cin.ignore();
                getline(cin, borrower);
                cout << "Enter Borrower ID: ";
                cin >> borrowerID;
                cout << "Enter Due Date: ";
                cin.ignore();
                getline(cin, dueDate);
                db.borrowBook(bookID, borrower, borrowerID, dueDate);
                break;
            case 7:
                cout << "Enter Book ID to Return: ";
                cin >> bookID;
                db.returnBook(bookID);
                break;
            case 8:
                cout << "Exiting program...\n";
                return ;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

//Structure to store gradebook information
struct Gradebook {
    int studentID;
    string subject;
    double grade;
    
};

// Class to manage gradebook records
class GradebookDatabase {
private:
    vector<Gradebook> grades;  // Store gradebook records
    map<int, Gradebook> gradeMap; // Quick search using student ID
    const string filename = "gradebook.dat";  // Binary file name
public:
    GradebookDatabase() { loadFromFile(); }  // Load data when object is created

    // Function to add a new grade
    void addGrade(int studentID, const string& subject, double grade) {
        Gradebook newGrade;
        newGrade.studentID = studentID;
        newGrade.subject = subject;
        newGrade.grade = grade;

        grades.push_back(newGrade);
        gradeMap[studentID] = newGrade;

        saveToFile();  // Save after adding a new grade
        cout << "Grade added successfully!\n";
    }

    // Function to display all grades
    void displayAllGrades() {
        if (grades.empty()) {
            cout << "No grade records available.\n";
            return;
        }
        cout << "Grade Records:\n";
        for (const auto& g : grades) {
            cout << "Student ID: " << g.studentID
                 << ", Subject: " << g.subject
                 << ", Grade: " << g.grade << "\n";
        }
    }

    // Function to search for a grade by student ID
    void searchGrade(int studentID) {
        if (gradeMap.find(studentID) != gradeMap.end()) {
            Gradebook g = gradeMap[studentID];
            cout << "Grade Found!\n"
                 << "Student ID: " << g.studentID
                 << ", Subject: " << g.subject
                 << ", Grade: " << g.grade << "\n";
        } else {
            cout << "Grade for Student ID " << studentID << " not found.\n";
        }
    }

    // Function to delete a grade record
    void deleteGrade(int studentID) {
        for (auto it = grades.begin(); it != grades.end(); ++it) {
            if (it->studentID == studentID) {
                grades.erase(it);
                gradeMap.erase(studentID);
                saveToFile();  // Save after deletion
                cout << "Grade record deleted successfully!\n";
                return;
            }
        }
        cout << "Grade for Student ID " << studentID << " not found.\n";
    }

    // Function to save data to a binary file
    void saveToFile() {
        ofstream file(filename, ios::binary | ios::out);
        if (!file) {
            cout << "Error saving data!\n";
            return;
        }
        for
 (const auto& g : grades) {
            file.write(reinterpret_cast<const char*>(&g), sizeof(Gradebook));
        }
        file.close();
        cout << "Data saved successfully!\n";
    }

    // Function to load data from a binary file
    void loadFromFile(){
        grades.clear();
        gradeMap.clear();
        ifstream file(filename, ios::binary | ios::in);
        if (!file) {
            cout << "No existing grade data found. Starting fresh.\n";
            return;
        }
        Gradebook temp;
        while (file.read(reinterpret_cast<char*>(&temp), sizeof(Gradebook))) {
            grades.push_back(temp);
            gradeMap[temp.studentID] = temp;
        }
        file.close();
        cout << "Data loaded successfully!\n";
    }

// Main function
int main() {
    int choice;

    while (true) {
        cout << "\n--- Database Menu ---\n";
        cout << "1. Work with Student Data.\n";
        cout << "2. Work with Employee Data.\n";
        cout << "3. Work with Tasks Data.\n";
        cout << "4. Work with Library Data.\n";
        cout << "5. Work with Student Gradebook.\n";
        cout << "6. Exit.\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentFunction();
                break;
            case 2:
                employeeFunction();
                break;
            case 3:
                courseTaskFunction();
                break;
            case 4:
                libraryFunction();
                break;
            case 5:

                break;
            case 6:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
