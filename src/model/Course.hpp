#pragma once

#include <string>
#include <sstream>
#include "../core/Utils.hpp"

namespace Model {

    class Course {
    public:
        std::string id;
        std::string name;
        int credits;

        Course() : credits(0) {}

        Course(std::string name, int credits) : name(name), credits(credits) {
            this->id = Core::Utils::generateUUID();
        }

        Course(std::string id, std::string name, int credits) 
            : id(id), name(name), credits(credits) {}

        std::string serialize() const {
            std::stringstream ss;
            ss << id << "," << name << "," << credits;
            return ss.str();
        }

        static Course deserialize(const std::string& data) {
            auto tokens = Core::Utils::split(data, ',');
            if (tokens.size() < 3) return Course();

            return Course(
                tokens[0],
                tokens[1],
                std::stoi(tokens[2])
            );
        }
    };

}
