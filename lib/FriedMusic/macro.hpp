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

#include "StringMethods.h"
#include "Config.h"

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

// inline void logLine()




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

inline static int randomInRange(int min, int max){
int range = max - min + 1;
return rand() % range + min;
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

