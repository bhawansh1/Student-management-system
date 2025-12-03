#include "CLI.hpp"
#include <iostream>
#include <limits>

namespace UI {

    CLI::CLI(std::shared_ptr<Service::StudentService> studentService) 
        : studentService(studentService) {}

    void CLI::run() {
        int choice;
        do {
            clearScreen();
            displayMenu();
            std::cout << "\nEnter choice: ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = -1;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

            switch (choice) {
                case 1: handleAddStudent(); break;
                case 2: handleViewAllStudents(); break;
                case 3: handleSearchStudent(); break;
                case 4: handleUpdateStudent(); break;
                case 5: handleDeleteStudent(); break;
                case 0: std::cout << "Exiting...\n"; break;
                default: std::cout << "Invalid choice!\n"; pause(); break;
            }
        } while (choice != 0);
    }

    void CLI::displayMenu() {
        std::cout << "========================================\n";
        std::cout << "      STUDENT MANAGEMENT SYSTEM         \n";
        std::cout << "========================================\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View All Students\n";
        std::cout << "3. Search Student\n";
        std::cout << "4. Update Student\n";
        std::cout << "5. Delete Student\n";
        std::cout << "0. Exit\n";
        std::cout << "========================================\n";
    }

    void CLI::handleAddStudent() {
        std::string name, email;
        int age;
        double gpa;

        std::cout << "Enter Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Email: ";
        std::getline(std::cin, email);
        std::cout << "Enter Age: ";
        std::cin >> age;
        std::cout << "Enter GPA: ";
        std::cin >> gpa;

        studentService->addStudent(name, email, age, gpa);
        std::cout << "Student added successfully!\n";
        pause();
    }

    void CLI::handleViewAllStudents() {
        auto students = studentService->getAllStudents();
        std::cout << "\n--- Student List ---\n";
        printf("%-36s | %-20s | %-25s | %-3s | %-4s\n", "ID", "Name", "Email", "Age", "GPA");
        std::cout << "----------------------------------------------------------------------------------------------------\n";
        for (const auto& s : students) {
            printf("%-36s | %-20s | %-25s | %-3d | %-4.2f\n", s.id.c_str(), s.name.c_str(), s.email.c_str(), s.age, s.gpa);
        }
        pause();
    }

    void CLI::handleSearchStudent() {
        std::string query;
        std::cout << "Enter Name, Email or ID to search: ";
        std::getline(std::cin, query);
        query = Core::Utils::trim(query);

        auto results = studentService->searchStudents(query);
        if (results.empty()) {
            std::cout << "No students found.\n";
        } else {
            std::cout << "\n--- Search Results ---\n";
            for (const auto& s : results) {
                std::cout << "ID: " << s.id << ", Name: " << s.name << ", Email: " << s.email << "\n";
            }
        }
        pause();
    }

    void CLI::handleUpdateStudent() {
        std::string id;
        std::cout << "Enter Student ID to update: ";
        std::getline(std::cin, id);
        id = Core::Utils::trim(id);

        auto student = studentService->getStudentById(id);
        if (!student) {
            std::cout << "Student not found!\n";
            pause();
            return;
        }

        std::string name, email;
        int age;
        double gpa;

        std::cout << "Enter New Name (" << student->name << "): ";
        std::getline(std::cin, name);
        if (name.empty()) name = student->name;

        std::cout << "Enter New Email (" << student->email << "): ";
        std::getline(std::cin, email);
        if (email.empty()) email = student->email;

        std::cout << "Enter New Age (" << student->age << "): ";
        if (std::cin.peek() == '\n') {
            age = student->age;
            std::cin.ignore();
        } else {
            std::cin >> age;
            std::cin.ignore();
        }

        std::cout << "Enter New GPA (" << student->gpa << "): ";
        if (std::cin.peek() == '\n') {
            gpa = student->gpa;
            std::cin.ignore();
        } else {
            std::cin >> gpa;
            std::cin.ignore();
        }

        studentService->updateStudent(id, name, email, age, gpa);
        std::cout << "Student updated successfully!\n";
        pause();
    }

    void CLI::handleDeleteStudent() {
        std::string id;
        std::cout << "Enter Student ID to delete: ";
        std::getline(std::cin, id);
        id = Core::Utils::trim(id);

        if (char c; std::cout << "Are you sure? (y/n): " && std::cin >> c && (c == 'y' || c == 'Y')) {
            studentService->deleteStudent(id);
            std::cout << "Student deleted.\n";
        } else {
            std::cout << "Cancelled.\n";
        }
        std::cin.ignore(); // consume newline
        pause();
    }

    void CLI::clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void CLI::pause() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

}
