#pragma once

#include <string>
#include <random>
#include <sstream>
#include <algorithm>
#include <vector>

namespace Core {

    class Utils {
    public:
        static std::string generateUUID() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(0, 15);
            static std::uniform_int_distribution<> dis2(8, 11);

            std::stringstream ss;
            int i;
            ss << std::hex;
            for (i = 0; i < 8; i++) ss << dis(gen);
            ss << "-";
            for (i = 0; i < 4; i++) ss << dis(gen);
            ss << "-4";
            for (i = 0; i < 3; i++) ss << dis(gen);
            ss << "-";
            ss << dis2(gen);
            for (i = 0; i < 3; i++) ss << dis(gen);
            ss << "-";
            for (i = 0; i < 12; i++) ss << dis(gen);
            return ss.str();
        }

        static std::string toLower(std::string str) {
            std::transform(str.begin(), str.end(), str.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            return str;
        }

        static std::vector<std::string> split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream tokenStream(str);
            while (std::getline(tokenStream, token, delimiter)) {
                tokens.push_back(token);
            }
            return tokens;
        }

        static std::string trim(const std::string& str) {
            const auto strBegin = str.find_first_not_of(" \t\n\r\f\v");
            if (strBegin == std::string::npos)
                return "";

            const auto strEnd = str.find_last_not_of(" \t\n\r\f\v");
            const auto strRange = strEnd - strBegin + 1;

            return str.substr(strBegin, strRange);
        }
    };

}
