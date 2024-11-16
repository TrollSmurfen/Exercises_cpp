#ifndef YAML_PARSER_H
#define YAML_PARSER_H

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
//#include <yaml-cpp/yaml.h>

class YamlParser {
public:
    YamlParser(const std::string& filename);
    std::string getString(const std::string& key) const;
    int getInt(const std::string& key) const;
    std::vector<std::string> getStringList(const std::string& key) const;

private:
    std::unordered_map<std::string, std::variant<std::string, std::vector<std::string>>> data;
};

#endif // YAML_PARSER_H
