#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

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