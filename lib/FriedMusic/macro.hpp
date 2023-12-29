#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

std::string ReplaceString(
  std::string subject, 
  const std::string& search,
  const std::string& replace);

std::string join(std::vector<std::string> const &strings, std::string delim);
std::string getConfigValue(const std::string&);

