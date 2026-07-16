cmake_minimum_required(VERSION 3.20)

project(SSHMonitor)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(SSHMonitor
        main.cpp
        Config.cpp
        Webhook.cpp
        Whitelist.cpp
        Monitor.cpp
        Includes/Whitelist.h
        Includes/Webhook.h
        Includes/Monitor.h
)

target_include_directories(SSHMonitor PRIVATE include)

target_link_libraries(SSHMonitor PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
)