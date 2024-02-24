#pragma once
#include <cpr/cpr.h>

#include <../nlohman/json.hpp>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::string ReplaceInString(std::string subject, const std::string &search,
                            const std::string &replace) {
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return subject;
}
std::string join(std::vector<std::string> const &strings, std::string delim) {
  std::stringstream ss;
  std::copy(strings.begin(), strings.end(),
            std::ostream_iterator<std::string>(ss, delim.c_str()));
  return ss.str();
}
std::string getConfigValue(const std::string &key) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    // harakiri or try to get something
    return "";
  } else {
    nlohmann::json config = nlohmann::json::parse(file);
    return config[key];
  }
}

void downloadFile(std::string url, std::string destination) {
  cpr::Response response = cpr::Get(cpr::Url(url));
  std::ofstream file(destination);
  file << response.text;
  file.close();
}

void downloadFile(cpr::Url url, std::string destination) {
  cpr::Response response = cpr::Get(url);
  std::ofstream file(destination);
  file << response.text;
  file.close();
}

void downloadFileAsync(std::string url, std::string destination) {
  std::ofstream of(destination);
  cpr::Response r = cpr::Download(of, cpr::Url(url));
}

void downloadFileAsync(cpr::Url &url, std::string &destination) {
  std::ofstream of(destination);
  cpr::Response r = cpr::Download(of, url);
}

std::string secondsToTime(int seconds) {
  // prebuilt string format aren't reliable
  int hour = seconds / 3600;
  int minute = (seconds % 3600) / 60;
  int second = seconds % 60;
  std::string ret;
  if (hour > 0 and hour <= 9) {
    ret = "0" + std::to_string(hour) + ":";
  } else if (hour > 0 and hour > 9) {
    ret = std::to_string(hour) + ":";
  }
  if (minute <= 9) {
    ret = ret + "0"+std::to_string(minute) + ":";
  } else if (minute > 9) {
    ret = ret + std::to_string(minute) + ":";
  }
  if (second <= 9) {
    ret = ret + "0"+std::to_string(second);
  } else if (second > 9) {
    ret = ret + std::to_string(second);
  }

  return ret;
}