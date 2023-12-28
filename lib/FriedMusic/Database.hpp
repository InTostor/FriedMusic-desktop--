#include <iostream>
#include <map>

#include "Data.hpp"
#include "nlohman/json.hpp"

using json = nlohmann::json;
using namespace std;

class Database{
public:


json executeRemoteQuery(string sql);

};