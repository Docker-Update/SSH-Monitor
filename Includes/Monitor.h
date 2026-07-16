#pragma once

#include <functional>
#include <string>

class Monitor
{
public:
    using LoginCallback =
        std::function<void(
            const std::string&,
            const std::string&
        )>;

    void Start(LoginCallback callback);
};