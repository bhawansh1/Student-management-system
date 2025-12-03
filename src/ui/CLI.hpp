#pragma once

#include "../service/StudentService.hpp"
#include <memory>

namespace UI {

    class CLI {
    public:
        CLI(std::shared_ptr<Service::StudentService> studentService);
        void run();

    private:
        std::shared_ptr<Service::StudentService> studentService;

        void displayMenu();
        void handleAddStudent();
        void handleViewAllStudents();
        void handleSearchStudent();
        void handleUpdateStudent();
        void handleDeleteStudent();
        
        // Helper to clear console
        void clearScreen();
        // Helper to pause
        void pause();
    };

}
