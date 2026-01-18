# 📘 Student Result Management System (C++)

A **console-based Student Result Management System** developed using **C++**.  
This project allows efficient management of student academic records and uses **file handling** to store and retrieve data permanently.

---

## ✨ Features

- Add new student records  
- View all student records  
- Search records by **Student ID**  
- Search records by **Student Name**  
- Update existing student details  
- Delete student records  
- Sort students alphabetically by name  
- Display statistics (total students, average age)  
- Persistent storage using **file handling (`fstream`)**

---

## 🛠️ Technologies Used

- **Language:** C++  
- **Concepts Used:**
  - Structures
  - File Handling (`fstream`)
  - Functions
  - Arrays
  - String handling (`cstring`)
  - Console-based menu system

    
2 .Navigate to the project directory:
cd student-result-management-system
3. Compile the program:
g++ main.cpp -o student_system
4. Run the executable
./student_system

📂 File Handling Details

Student data is stored in a binary file named students.dat

Data is:

Loaded automatically at program startup

Saved automatically after insert, update, or delete operations

📋 Menu Options

Add Student

View All Students

Search Student by ID

Search Student by Name

Delete Student

Update Student

Sort Students by Name

Display Statistics

Exit

🎯 Learning Outcomes

Practical understanding of file handling in C++

Strong grip on CRUD operations

Improved logic building and structured programming skills
