#include <iostream>

#include "Includes/Config.h"
#include "Includes/Monitor.h"
#include "Includes/Webhook.h"
#include "Includes/Whitelist.h"

int main()
{
    Config cfg = loadConfig("config.json");

    whitelist whitelist(cfg.whitelistIps);

    Webhook webhook(cfg.webhookUrl);

    Monitor monitor;

    monitor.start(
        [&](const std::string& user,
            const std::string& ip)
        {
            std::cout
                << user
                << " "
                << ip
                << std::endl;

            if (!whitelist.isAllowed(ip))
            {
                webhook.sendAlert(user, ip);
            }
        }
    );

    return 0;
}
