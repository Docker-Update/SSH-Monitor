#pragma once


#include <string>
#include <vector>

struct Config {
    std::string webhookUrl;
    std::vector<std::string> whitelistIps;
};

Config loadConfig(const std::string& filePath);
