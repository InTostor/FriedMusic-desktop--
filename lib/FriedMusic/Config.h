#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;

// Static, global, singleton
class Config {
public:
  static nlohmann::json config;
  static int accessCounter;
  static string configPath;
  inline static void forceClearCounter() { accessCounter = 0; }
  inline static void prepareCache() {
    std::ifstream file(configPath);
    if (!file.is_open()) {
      // Make config somehow
    } else {
      config = nlohmann::json::parse(file);
    }
  }
  inline static void checkCache() {
    if (accessCounter == -1 or accessCounter > 60) {
      prepareCache();
    }
  }
  static inline std::string getConfigValue(const std::string &key) {
    checkCache();
    accessCounter += 1;
    return config[key];
  }

  static inline bool getConfigBoolValue(const std::string &key) {
    checkCache();
    accessCounter += 1;
    return config[key];
  }

  static inline int getConfigIntValue(const std::string &key) {
    checkCache();
    accessCounter += 1;
    return config[key];
  }

  static inline void setConfigValue(const std::string &key,
                                    const std::string &value) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
      return;
    } else {
      nlohmann::json config = nlohmann::json::parse(file);
      config[key] = value;
      file.close();
      std::ofstream out(configPath);
      out << config << std::endl;
      out.close();
      prepareCache();
    }
  }
  static inline void setConfigValue(const std::string &key, const int &value) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
      return;
    } else {
      nlohmann::json config = nlohmann::json::parse(file);
      config[key] = value;
      file.close();
      std::ofstream out(configPath);
      out << config << std::endl;
      out.close();
      prepareCache();
    }
  }
};