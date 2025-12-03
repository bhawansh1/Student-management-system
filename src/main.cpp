#include "core/Logger.hpp"
#include "model/Student.hpp"
#include "repository/FileRepository.hpp"
#include "service/StudentService.hpp"
#include "ui/CLI.hpp"
#include <memory>

int main() {
    // Initialize Logger
    Core::Logger::getInstance().setLogFile("app.log");
    Core::Logger::getInstance().log(Core::LogLevel::INFO, "Application started.");

    // Initialize Repository
    auto studentRepo = std::make_shared<Repository::FileRepository<Model::Student>>("students.db");

    // Initialize Service
    auto studentService = std::make_shared<Service::StudentService>(studentRepo);

    // Initialize UI
    UI::CLI cli(studentService);

    // Run Application
    cli.run();

    Core::Logger::getInstance().log(Core::LogLevel::INFO, "Application stopped.");
    return 0;
}
