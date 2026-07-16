#pragma once

#include <string>

class Webhook {
public:
    explicit Webhook(const std::string& url);


        bool sendAlert(
            const std::string& username,
            const std::string& ip);

private:
    std::string m_url;
};
