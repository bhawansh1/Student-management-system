#pragma once

#include "../repository/FileRepository.hpp"
#include "../model/Student.hpp"
#include <memory>
#include <vector>
#include <optional>

namespace Service {

    class StudentService {
    public:
        StudentService(std::shared_ptr<Repository::FileRepository<Model::Student>> repo);

        void addStudent(const std::string& name, const std::string& email, int age, double gpa);
        std::vector<Model::Student> getAllStudents();
        std::optional<Model::Student> getStudentById(const std::string& id);
        void updateStudent(const std::string& id, const std::string& name, const std::string& email, int age, double gpa);
        void deleteStudent(const std::string& id);
        std::vector<Model::Student> searchStudents(const std::string& query);

    private:
        std::shared_ptr<Repository::FileRepository<Model::Student>> repository;
    };

}
