#include "Config.h"
#include <nlohmann/json.hpp>

int Config::accessCounter = -1;
string Config::configPath = "config.json";

// Believe the real config will be parsed
nlohmann::json Config::config = nlohmann::json::parse("{}");
