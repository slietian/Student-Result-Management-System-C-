#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_NAME_LENGTH = 50;
const int MAX_COURSE_LENGTH = 50;

struct Student {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char course[MAX_COURSE_LENGTH];
};

Student students[MAX_STUDENTS];
int studentCount = 0;

/* ------------------ Utility Functions ------------------ */

void printCentered(const string &text, int width) {
    int padding = (width - text.length()) / 2;
    for (int i = 0; i < padding; i++)
        cout << " ";
    cout << text << endl;
}

bool isUniqueID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id)
            return false;
    }
    return true;
}

/* ------------------ File Handling ------------------ */

void saveToFile() {
    ofstream outFile("students.dat", ios::binary);
    outFile.write((char*)&studentCount, sizeof(studentCount));
    outFile.write((char*)students, sizeof(Student) * studentCount);
    outFile.close();
}

void loadFromFile() {
    ifstream inFile("students.dat", ios::binary);
    if (!inFile)
        return;

    inFile.read((char*)&studentCount, sizeof(studentCount));
    inFile.read((char*)students, sizeof(Student) * studentCount);
    inFile.close();
}

/* ------------------ Core Features ------------------ */

void insertStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printCentered("Student list is full.", 100);
        return;
    }

    printCentered("Enter Student ID: ", 100);
    cin >> students[studentCount].id;

    while (!isUniqueID(students[studentCount].id)) {
        printCentered("ID already exists. Enter unique ID: ", 100);
        cin >> students[studentCount].id;
    }

    cin.ignore();
    printCentered("Enter Student Name: ", 100);
    cin.getline(students[studentCount].name, MAX_NAME_LENGTH);

    printCentered("Enter Student Age: ", 100);
    cin >> students[studentCount].age;

    while (cin.fail() || students[studentCount].age <= 0 || students[studentCount].age > 100) {
        cin.clear();
        cin.ignore(1000, '\n');
        printCentered("Enter valid age (1-100): ", 100);
        cin >> students[studentCount].age;
    }

    cin.ignore();
    printCentered("Enter Student Course: ", 100);
    cin.getline(students[studentCount].course, MAX_COURSE_LENGTH);

    studentCount++;
    saveToFile();

    printCentered("Student record added successfully.", 100);
}

void viewAllStudents() {
    if (studentCount == 0) {
        printCentered("No records found.", 100);
        return;
    }

    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(10) << "Age"
         << setw(25) << "Course" << endl;

    cout << "--------------------------------------------------------------" << endl;

    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(10) << students[i].id
             << setw(25) << students[i].name
             << setw(10) << students[i].age
             << setw(25) << students[i].course << endl;
    }
}

void searchByID() {
    int id;
    printCentered("Enter Student ID to search: ", 100);
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "ID: " << students[i].id
                 << ", Name: " << students[i].name
                 << ", Age: " << students[i].age
                 << ", Course: " << students[i].course << endl;
            return;
        }
    }
    printCentered("Student not found.", 100);
}

void searchByName() {
    char name[MAX_NAME_LENGTH];
    cin.ignore();
    printCentered("Enter Student Name: ", 100);
    cin.getline(name, MAX_NAME_LENGTH);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            cout << "ID: " << students[i].id
                 << ", Name: " << students[i].name
                 << ", Age: " << students[i].age
                 << ", Course: " << students[i].course << endl;
            return;
        }
    }
    printCentered("Student not found.", 100);
}

void deleteStudent() {
    int id;
    printCentered("Enter Student ID to delete: ", 100);
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++)
                students[j] = students[j + 1];

            studentCount--;
            saveToFile();
            printCentered("Student record deleted.", 100);
            return;
        }
    }
    printCentered("Student not found.", 100);
}

void updateStudent() {
    int id;
    printCentered("Enter Student ID to update: ", 100);
    cin >> id;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cin.ignore();
            printCentered("Enter New Name: ", 100);
            cin.getline(students[i].name, MAX_NAME_LENGTH);

            printCentered("Enter New Age: ", 100);
            cin >> students[i].age;

            cin.ignore();
            printCentered("Enter New Course: ", 100);
            cin.getline(students[i].course, MAX_COURSE_LENGTH);

            saveToFile();
            printCentered("Student record updated.", 100);
            return;
        }
    }
    printCentered("Student not found.", 100);
}

void sortByName() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printCentered("Students sorted by name.", 100);
}

void statistics() {
    if (studentCount == 0) {
        printCentered("No records available.", 100);
        return;
    }

    int totalAge = 0;
    for (int i = 0; i < studentCount; i++)
        totalAge += students[i].age;

    cout << "Total Students: " << studentCount << endl;
    cout << "Average Age: " << (float)totalAge / studentCount << endl;
}

/* ------------------ MAIN ------------------ */

int main() {
    loadFromFile();

    int choice;
    do {
        printCentered("------ Student Management System ------", 100);
        printCentered("1. Add Student", 100);
        printCentered("2. View All Students", 100);
        printCentered("3. Search by ID", 100);
        printCentered("4. Search by Name", 100);
        printCentered("5. Delete Student", 100);
        printCentered("6. Update Student", 100);
        printCentered("7. Sort by Name", 100);
        printCentered("8. Statistics", 100);
        printCentered("9. Exit", 100);
        printCentered("Enter your choice: ", 100);

        cin >> choice;

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchByID(); break;
            case 4: searchByName(); break;
            case 5: deleteStudent(); break;
            case 6: updateStudent(); break;
            case 7: sortByName(); break;
            case 8: statistics(); break;
            case 9: printCentered("Exiting program...", 100); break;
            default: printCentered("Invalid choice.", 100);
        }

    } while (choice != 9);

    return 0;
}
