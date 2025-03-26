#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

struct Student {
    int studentId;
    string fname, lname, course;
    float gpa;
};

vector<Student> students;

// Utility Function to Validate Integer Input
int getValidatedInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Utility Function to Validate Float Input
float getValidatedFloat(string prompt) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0.0 && value <= 4.0) {
            return value;
        } else {
            cout << "Invalid GPA. Please enter a valid GPA (0.0 - 4.0).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Check for Duplicate Student ID
bool isDuplicate(int studentId) {
    return any_of(students.begin(), students.end(), [studentId](Student& s) {
        return s.studentId == studentId;
    });
}

// Add New Student
void addStudent() {
    int studentId = getValidatedInt("Enter Student ID: ");
    while (isDuplicate(studentId)) {
        cout << "Student ID already exists! Enter a new Student ID.\n";
        studentId = getValidatedInt("Enter Student ID: ");
    }

    Student newStudent;
    newStudent.studentId = studentId;
    cout << "Enter First Name: "; cin >> newStudent.fname;
    cout << "Enter Last Name: "; cin >> newStudent.lname;
    cout << "Enter Course: "; cin >> newStudent.course;
    newStudent.gpa = getValidatedFloat("Enter GPA: ");

    students.push_back(newStudent);
    cout << "Student added successfully!\n";
}

// Search Student Index by ID (Binary Search)
int searchStudentIndex(int studentId) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i].studentId == studentId) {
            return i;
        }
    }
    return -1;
}

// Edit Student Data
void editStudent() {
    if (students.empty()) {
        cout << "No records available.\n";
        return;
    }

    int studentId = getValidatedInt("Enter Student ID to edit: ");
    int index = searchStudentIndex(studentId);

    if (index == -1) {
        cout << "Student ID not found.\n";
        return;
    }

    cout << "Enter New First Name: "; cin >> students[index].fname;
    cout << "Enter New Last Name: "; cin >> students[index].lname;
    cout << "Enter New Course: "; cin >> students[index].course;
    students[index].gpa = getValidatedFloat("Enter New GPA: ");
    cout << "Student data updated successfully!\n";
}

// Delete Student Data
void deleteStudent() {
    if (students.empty()) {
        cout << "No records available.\n";
        return;
    }

    int studentId = getValidatedInt("Enter Student ID to delete: ");
    int index = searchStudentIndex(studentId);

    if (index == -1) {
        cout << "Student ID not found.\n";
        return;
    }

    students.erase(students.begin() + index);
    cout << "Student deleted successfully!\n";
}

// Sort Students by Option (1 = Last Name, 2 = GPA)
void sortStudents(int option) {
    if (option == 1) {
        sort(students.begin(), students.end(), [](Student& a, Student& b) {
            return a.lname < b.lname;
        });
    } else if (option == 2) {
        sort(students.begin(), students.end(), [](Student& a, Student& b) {
            return a.gpa > b.gpa; // Descending order (higher GPA first)
        });
    }
}

// Display Student Records
void displayStudents() {
    if (students.empty()) {
        cout << "No records available.\n";
        return;
    }

    int choice = getValidatedInt("View Options:\n1. Sort by Last Name\n2. Sort by GPA\nEnter option: ");
    if (choice == 1 || choice == 2) {
        sortStudents(choice);
    } else {
        cout << "Invalid option. Showing unsorted data.\n";
    }

    cout << "\nID\tFirst Name\tLast Name\tCourse\tGPA\n";
    for (const auto& s : students) {
        cout << s.studentId << "\t"
             << s.fname << "\t\t"
             << s.lname << "\t\t"
             << s.course << "\t"
             << fixed << setprecision(2) << s.gpa << "\n";
    }
}

// Main Menu
void displayMenu() {
    cout << "\nStudent Management System\n";
    cout << "1. Add Student\n";
    cout << "2. Edit Student\n";
    cout << "3. Delete Student\n";
    cout << "4. View Students\n";
    cout << "5. Exit\n";
}

// Main Function
int main() {
    while (true) {
        displayMenu();
        int choice = getValidatedInt("Enter choice: ");

        switch (choice) {
            case 1: addStudent(); break;
            case 2: editStudent(); break;
            case 3: deleteStudent(); break;
            case 4: displayStudents(); break;
            case 5: cout << "Exiting...\n"; return 0;
            }
            }
            }