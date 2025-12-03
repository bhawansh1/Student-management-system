#include "StudentService.hpp"
#include "../core/Logger.hpp"
#include <algorithm>

namespace Service {

    StudentService::StudentService(std::shared_ptr<Repository::FileRepository<Model::Student>> repo) 
        : repository(repo) {}

    void StudentService::addStudent(const std::string& name, const std::string& email, int age, double gpa) {
        Model::Student student(name, email, age, gpa);
        repository->add(student);
        Core::Logger::getInstance().log(Core::LogLevel::INFO, "Added student: " + name);
    }

    std::vector<Model::Student> StudentService::getAllStudents() {
        return repository->getAll();
    }

    std::optional<Model::Student> StudentService::getStudentById(const std::string& id) {
        return repository->getById(id);
    }

    void StudentService::updateStudent(const std::string& id, const std::string& name, const std::string& email, int age, double gpa) {
        auto existing = repository->getById(id);
        if (existing) {
            Model::Student updated = *existing;
            updated.name = name;
            updated.email = email;
            updated.age = age;
            updated.gpa = gpa;
            repository->update(updated);
            Core::Logger::getInstance().log(Core::LogLevel::INFO, "Updated student: " + id);
        } else {
            Core::Logger::getInstance().log(Core::LogLevel::WARNING, "Attempted to update non-existent student: " + id);
        }
    }

    void StudentService::deleteStudent(const std::string& id) {
        repository->remove(id);
        Core::Logger::getInstance().log(Core::LogLevel::INFO, "Deleted student: " + id);
    }

    std::vector<Model::Student> StudentService::searchStudents(const std::string& query) {
        auto all = repository->getAll();
        std::vector<Model::Student> results;
        std::string lowerQuery = Core::Utils::toLower(query);

        for (const auto& s : all) {
            if (Core::Utils::toLower(s.name).find(lowerQuery) != std::string::npos ||
                Core::Utils::toLower(s.email).find(lowerQuery) != std::string::npos ||
                s.id == query) {
                results.push_back(s);
            }
        }
        return results;
    }

}
