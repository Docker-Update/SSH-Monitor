#include "Includes/Config.h"

#include <fstream>
#include <stdexcept>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config loadConfig(const std::string& filePath)
{
    std::ifstream file(filePath);

    if (!file.is_open())
        throw std::runtime_error("Cannot open config file: " + filePath);

    json data;
    file >> data;

    Config config;
    config.webhookUrl = data.at("webhook_url").get<std::string>();
    config.whitelistIps =
        data.at("whitelist").get<std::vector<std::string>>();

    return config;
}