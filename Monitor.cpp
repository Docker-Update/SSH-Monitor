#include "Includes/Monitor.h"

#include <array>
#include <cstdio>
#include <regex>

void Monitor::Start(LoginCallback callback)
{
    FILE* pipe =
        popen(
            "journalctl -f -n 0 -u ssh -u sshd --no-pager",
            "r"
        );

    if (!pipe)
        return;

    std::array<char,4096> buffer{};

    std::regex regex(
        R"(Accepted (?:password|publickey|keyboard-interactive) for (\S+) from ([0-9a-fA-F:.]+))"
    );

    while (fgets(buffer.data(), buffer.size(), pipe))
    {
        std::string line(buffer.data());

        std::smatch match;

        if (std::regex_search(line, match, regex))
        {
            callback(
                match[1].str(),
                match[2].str()
            );
        }
    }

    pclose(pipe);
}