#pragma once
#ifndef MACRO_H
#define MACRO_H
#include <cpr/cpr.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <sstream>
#include <string>
#include <vector>

typedef int64_t msec_t;
#if defined(__WIN32__)

#include <windows.h>

inline msec_t time_ms(void) { return timeGetTime(); }

#else

#include <sys/time.h>

inline msec_t time_ms(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (msec_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#endif

#endif
#define timestamp std::cout << __LINE__ << ";" << __FILE__ << ";" << time_ms() << std::endl;

#define FUNC_NAME(a)         (QString(#a).remove(QRegExp("\\((.*)\\)")).trimmed().toLatin1().constData())

inline std::string ReplaceInString(std::string subject,
                                   const std::string &search,
                                   const std::string &replace) {
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos) {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return subject;
}

template <typename T>
inline std::string join(const T &v, const std::string &delim) {
  std::ostringstream s;
  for (const auto &i : v) {
    if (&i != &v[0]) {
      s << delim;
    }
    s << i;
  }
  return s.str();
}

inline std::vector<std::string> explode(const std::string &str,
                                        const char &ch) {
  std::string next;
  std::vector<std::string> result;

  // For each character in the string
  for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
    // If we've hit the terminal character
    if (*it == ch) {
      // If we have some characters accumulated
      if (!next.empty()) {
        // Add them to the result vector
        result.push_back(next);
        next.clear();
      }
    } else {
      // Accumulate the next character into the sequence
      next += *it;
    }
  }
  if (!next.empty())
    result.push_back(next);
  return result;
}

static inline void
ParseStringByStringSeparator(std::string s, const std::string separator,
                             std::vector<std::string> &result) {
  result.clear();
  size_t pos = 0;
  std::string token;

  while ((pos = s.find(separator)) != std::string::npos) {
    token = s.substr(0, pos);
    result.push_back(token);
    s.erase(0, pos + separator.length());
  }
  result.push_back(s);
}

static inline std::vector<std::string>
explodeMultiplDelimeters(std::string s,
                         const std::vector<std::string> &separators) {
  std::vector<std::string> result = {s};
  for (const auto &sep : separators) {
    std::vector<std::string> toReplaceBy, tempRes;
    for (auto &a : result) {
      ParseStringByStringSeparator(a, sep, tempRes);
      toReplaceBy.insert(toReplaceBy.end(), tempRes.begin(), tempRes.end());
    }
    auto it = toReplaceBy.begin();
    while (it != toReplaceBy.end()) {
      if ((*it) == "")
        it = toReplaceBy.erase(it);
      else
        ++it;
    }
    result = toReplaceBy;
  }
  return result;
}

static inline std::string getConfigValue(const std::string &key) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    // harakiri or try to get something
    return "";
  } else {
    nlohmann::json config = nlohmann::json::parse(file);
    return config[key];
  }
}

static inline bool getConfigBoolValue(const std::string &key) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    // harakiri or try to get something
    return "";
  } else {
    nlohmann::json config = nlohmann::json::parse(file);
    return config[key];
  }
}


static inline int getConfigIntValue(const std::string &key) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    // harakiri or try to get something
    return -1;
  } else {
    nlohmann::json config = nlohmann::json::parse(file);
    return config[key];
  }
}

inline void setConfigValue(const std::string &key, const std::string &value) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    return;
  } else {
    nlohmann::json config = nlohmann::json::parse(file);
    config[key] = value;
    file.close();
    std::ofstream out("config.json");
    out << config << std::endl;
    out.close();
  }
}
inline void setConfigValue(const std::string &key, const int &value) {
  std::ifstream file("config.json");
  if (!file.is_open()) {
    return;
  } else {
    nlohmann::json config = nlohmann::json::parse(file);
    config[key] = value;
    file.close();
    std::ofstream out("config.json");
    out << config << std::endl;
    out.close();
  }
}

inline void downloadFile(std::string url, std::string destination) {
  cpr::Response response = cpr::Get(cpr::Url(url));
  std::ofstream file(destination);
  file << response.text;
  file.close();
}

inline void downloadFile(cpr::Url url, std::string destination) {
  cpr::Response response = cpr::Get(url);
  std::ofstream file(destination);
  file << response.text;
  file.close();
}

inline void downloadFileAsync(std::string url, std::string destination) {
  std::ofstream of(destination);
  cpr::Response r = cpr::Download(of, cpr::Url(url));
}

inline void downloadFileAsync(cpr::Url &url, std::string &destination) {
  std::ofstream of(destination);
  cpr::Response r = cpr::Download(of, url);
}

inline std::string secondsToTime(int seconds) {
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

template<typename T>
inline T randomByWeight(std::vector<T> values, std::vector<float> weights){
  // alghorithm from https://dev.to/jacktt/understanding-the-weighted-random-algorithm-581p
  float totalWeight = 0;
  for (float weight : weights){
    totalWeight += weight;
  }
  // https://stackoverflow.com/questions/686353/random-float-number-generation
  // quite ancient way
  srand (static_cast <unsigned> (time_ms()));
  float random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/totalWeight));
  float cursor = 0;
  for (int i=0; i< distance(weights.begin(), weights.end()); i++){
    cursor += weights[i];
    if (cursor >= random){
      return values[i];
    }
  }
  // if something goes wrong
  return values[0];
}

template <typename T>
inline std::vector<T> sliceVector(std::vector<T> const &v, int X, int Y) {

  // Begin and End iterator
  auto first = v.begin() + X;
  auto last = v.begin() + Y + 1;

  // Copy the element
  std::vector<T> vector(first, last);

  // Return the results
  return vector;
}

