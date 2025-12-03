#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "../core/Utils.hpp"

namespace Model {

    class Student {
    public:
        std::string id;
        std::string name;
        std::string email;
        int age;
        double gpa;

        Student() : age(0), gpa(0.0) {}

        Student(std::string name, std::string email, int age, double gpa)
            : name(name), email(email), age(age), gpa(gpa) {
            this->id = Core::Utils::generateUUID();
        }

        Student(std::string id, std::string name, std::string email, int age, double gpa)
            : id(id), name(name), email(email), age(age), gpa(gpa) {}

        // Serialization: ID,Name,Email,Age,GPA
        std::string serialize() const {
            std::stringstream ss;
            ss << id << "," << name << "," << email << "," << age << "," << gpa;
            return ss.str();
        }

        static Student deserialize(const std::string& data) {
            auto tokens = Core::Utils::split(data, ',');
            if (tokens.size() < 5) return Student(); // Handle error gracefully
            
            return Student(
                tokens[0],
                tokens[1],
                tokens[2],
                std::stoi(tokens[3]),
                std::stod(tokens[4])
            );
        }
    };

}
