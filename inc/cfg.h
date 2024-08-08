#pragma once

#include <string>
#include <unordered_map>

namespace cfg
{
    void initToDefault();

    void load();
    void saveCommon();
    void saveGD();

    extern std::unordered_map<std::string, bool> config;
    extern std::string driveClientID, driveClientSecret, driveAuthCode, driveRefreshToken;
}