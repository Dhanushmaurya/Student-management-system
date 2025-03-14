#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Student {
    int rollNo;
    string name;
    int age;
};

// Function to add a student
void addStudent(vector<Student> &students) {
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    
    students.push_back(s);
    
    // Save to file
    ofstream file("students.txt", ios::app);
    file << s.rollNo << " " << s.name << " " << s.age << endl;
    file.close();
    
    cout << "Student added successfully!\n";
}

// Function to display students
void displayStudents() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No student records found!\n";
        return;
    }
    
    Student s;
    cout << "\n--- Student Records ---\n";
    while (file >> s.rollNo >> ws) {
        getline(file, s.name);
        file >> s.age;
        cout << "Roll No: " << s.rollNo << ", Name: " << s.name << ", Age: " << s.age << endl;
    }
    file.close();
}

// Function to delete a student
void deleteStudent(vector<Student> &students, int rollNo) {
    ofstream tempFile("temp.txt");
    ifstream file("students.txt");
    
    Student s;
    bool found = false;
    
    while (file >> s.rollNo >> ws) {
        getline(file, s.name);
        file >> s.age;
        
        if (s.rollNo == rollNo) {
            found = true;
            cout << "Student Deleted Successfully!\n";
        } else {
            tempFile << s.rollNo << " " << s.name << " " << s.age << endl;
        }
    }
    
    file.close();
    tempFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    
    if (!found) {
        cout << "Student not found!\n";
    }
}

int main() {
    vector<Student> students;
    int choice, rollNo;
    
    do {
        cout << "\n1. Add Student\n2. View Students\n3. Delete Student\n4. Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: addStudent(students); break;
            case 2: displayStudents(); break;
            case 3: 
                cout << "Enter Roll No to delete: ";
                cin >> rollNo;
                deleteStudent(students, rollNo);
                break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);
    
    return 0;
}

