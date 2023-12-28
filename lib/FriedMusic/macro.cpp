#include "macro.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "nlohman/json.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

std::string ReplaceString(
    std::string subject,
    const std::string &search,
    const std::string &replace)
{
  size_t pos = 0;
  while ((pos = subject.find(search, pos)) != std::string::npos)
  {
    subject.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return subject;
}

std::string join(std::vector<std::string> const &strings, std::string delim)
{
  std::stringstream ss;
  std::copy(strings.begin(), strings.end(),
            std::ostream_iterator<std::string>(ss, delim.c_str()));
  return ss.str();
}

std::string getConfigValue(const std::string &key)
{
  std::ifstream file("config.json");
  if(!file.is_open()){
    // harakiri or try to get something
    return "";
  }else{
    json config = json::parse(file);
    return config[key];
  }

}