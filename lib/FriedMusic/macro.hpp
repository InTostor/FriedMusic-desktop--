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
template <typename T>
std::string join(const T& v, const std::string& delim) {
    std::ostringstream s;
    for (const auto& i : v) {
        if (&i != &v[0]) {
            s << delim;
        }
        s << i;
    }
    return s.str();
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

void setConfigValue(const std::string &key, const std::string &value) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    return;
  }else{
    nlohmann::json config = nlohmann::json::parse(file);
    config[key] = value;
  }
}
void setConfigValue(const std::string &key, const int &value) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    return;
  }else{
    nlohmann::json config = nlohmann::json::parse(file);
    config[key] = value;
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
    ret = ret + "0" + std::to_string(minute) + ":";
  } else if (minute > 9) {
    ret = ret + std::to_string(minute) + ":";
  }
  if (second <= 9) {
    ret = ret + "0" + std::to_string(second);
  } else if (second > 9) {
    ret = ret + std::to_string(second);
  }

  return ret;
}

template <typename T>
std::vector<T> sliceVector(std::vector<T> const& v,
                  int X, int Y)
{
 
    // Begin and End iterator
    auto first = v.begin() + X;
    auto last = v.begin() + Y + 1;
 
    // Copy the element
    std::vector<T> vector(first, last);
 
    // Return the results
    return vector;
}

typedef int64_t msec_t;
#if defined(__WIN32__)

#include <windows.h>

msec_t time_ms(void)
{
    return timeGetTime();
}

#else

#include <sys/time.h>

msec_t time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (msec_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif
