#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <mutex>

#include "Includes/Config.h"
#include "Includes/Monitor.h"
#include "Includes/Webhook.h"
#include "Includes/Whitelist.h"

namespace fs = std::filesystem;

int main()
{
    const std::string configPath = "config.json";

    Config cfg = loadConfig(configPath);

    whitelist whitelist(cfg.whitelistIps);
    Webhook webhook(cfg.webhookUrl);

    std::mutex configMutex;

    auto lastWrite = fs::last_write_time(configPath);

    std::thread watcher([&]()
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            try
            {
                auto current = fs::last_write_time(configPath);

                if (current != lastWrite)
                {
                    lastWrite = current;

                    std::lock_guard<std::mutex> lock(configMutex);

                    std::cout << "[CONFIG] Changement détecté, rechargement..." << std::endl;

                    cfg = loadConfig(configPath);

                    whitelist = ::whitelist(cfg.whitelistIps);
                    webhook = Webhook(cfg.webhookUrl);

                    std::cout << "[CONFIG] Rechargement terminé." << std::endl;
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "[CONFIG] Erreur : " << e.what() << std::endl;
            }
        }
    });

    watcher.detach();

    Monitor monitor;

    monitor.start(
        [&](const std::string& user,
            const std::string& ip)
        {
            std::lock_guard<std::mutex> lock(configMutex);

            std::cout
                << "[SSH] "
                << user
                << " -> "
                << ip
                << std::endl;

            if (!whitelist.isAllowed(ip))
            {
                std::cout << "[ALERT] IP non whitelistée, envoi du webhook..." << std::endl;

                if (!webhook.sendAlert(user, ip))
                {
                    std::cerr << "[ERROR] Impossible d'envoyer le webhook." << std::endl;
                }
            }
            else
            {
                std::cout << "[INFO] IP whitelistée." << std::endl;
            }
        });

    return 0;
}