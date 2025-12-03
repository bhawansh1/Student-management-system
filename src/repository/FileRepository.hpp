#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <shared_mutex>
#include <mutex>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include "../core/Logger.hpp"

namespace Repository {

    template<typename T>
    class FileRepository {
    public:
        FileRepository(const std::string& filename) : filename(filename) {
            loadFromFile();
        }

        ~FileRepository() {
            saveToFile();
        }

        void add(const T& item) {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            items[item.id] = item;
            saveToFile(); // Auto-save on write
        }

        std::optional<T> getById(const std::string& id) {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            if (items.find(id) != items.end()) {
                return items[id];
            }
            return std::nullopt;
        }

        std::vector<T> getAll() {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            std::vector<T> allItems;
            for (const auto& pair : items) {
                allItems.push_back(pair.second);
            }
            return allItems;
        }

        void update(const T& item) {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            items[item.id] = item;
            saveToFile();
        }

        void remove(const std::string& id) {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            items.erase(id);
            saveToFile();
        }

    private:
        std::string filename;
        std::unordered_map<std::string, T> items;
        mutable std::shared_mutex mutex_;

        void loadFromFile() {
            std::ifstream file(filename);
            if (!file.is_open()) {
                Core::Logger::getInstance().log(Core::LogLevel::WARNING, "Could not open file for reading: " + filename + ". Creating new.");
                return;
            }

            std::string line;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    try {
                        T item = T::deserialize(line);
                        items[item.id] = item;
                    } catch (...) {
                        Core::Logger::getInstance().log(Core::LogLevel::ERROR, "Failed to deserialize line: " + line);
                    }
                }
            }
        }

        void saveToFile() {
            std::ofstream file(filename); // Truncate and rewrite
            if (!file.is_open()) {
                Core::Logger::getInstance().log(Core::LogLevel::ERROR, "Could not open file for writing: " + filename);
                return;
            }

            for (const auto& pair : items) {
                file << pair.second.serialize() << std::endl;
            }
        }
    };

}
