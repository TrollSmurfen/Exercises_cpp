#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

class YamlParser {
public:
    YamlParser(const std::string& filename);
    std::string getString(const std::string& key) const;
    int getInt(const std::string& key) const;
    std::vector<std::string> getStringList(const std::string& key) const;

private:
    std::unordered_map<std::string, std::variant<std::string, std::vector<std::string>>> data;
};

YamlParser::YamlParser(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        if (std::getline(iss, key, ':')) {
            std::string value;
            if (std::getline(iss, value)) {
                value.erase(0, value.find_first_not_of(" \t")); // Trim leading spaces
                if (value.front() == '[' && value.back() == ']') {
                    // Handle list
                    value = value.substr(1, value.size() - 2); // Remove brackets
                    std::vector<std::string> list;
                    std::istringstream listStream(value);
                    std::string item;
                    while (std::getline(listStream, item, ',')) {
                        item.erase(0, item.find_first_not_of(" \t")); // Trim leading spaces
                        item.erase(item.find_last_not_of(" \t") + 1); // Trim trailing spaces
                        list.push_back(item);
                    }
                    data[key] = list;
                } else {
                    // Handle scalar
                    data[key] = value;
                }
            }
        }
    }
}

std::string YamlParser::getString(const std::string& key) const {
    if (data.find(key) != data.end()) {
        if (std::holds_alternative<std::string>(data.at(key))) {
            return std::get<std::string>(data.at(key));
        }
    }
    return "";
}

int YamlParser::getInt(const std::string& key) const {
    if (data.find(key) != data.end()) {
        if (std::holds_alternative<std::string>(data.at(key))) {
            return std::stoi(std::get<std::string>(data.at(key)));
        }
    }
    return 0;
}

std::vector<std::string> YamlParser::getStringList(const std::string& key) const {
    if (data.find(key) != data.end()) {
        if (std::holds_alternative<std::vector<std::string>>(data.at(key))) {
            return std::get<std::vector<std::string>>(data.at(key));
        }
    }
    return {};
}

int main() {
    YamlParser parser("example.yaml"); // Create parser object and read from file

    // Example of fetching data
    std::string name = parser.getString("name");
    int age = parser.getInt("age");
    std::vector<std::string> items = parser.getStringList("items");

    // Print name
    std::cout << "Name: " << name << std::endl;
    
    // Print age
    std::cout << "Age: " << age << std::endl;

    // Print items
    for (const auto& item : items) {
        std::cout << item << std::endl;
    }

    return 0;
}
