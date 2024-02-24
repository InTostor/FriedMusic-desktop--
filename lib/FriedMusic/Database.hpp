#include <iostream>
#include <map>
#include <string>

#include "Data.hpp"
#include "macro.hpp"
#include "nlohman/json.hpp"
#include <cpr/cpr.h>

using namespace std;

class Database {
 public:
  /// @brief Returns JSON answer from API server
  /// @param sql
  /// @return
  nlohmann::json Database::executeRemoteQuery(string sql) {
    sql = ReplaceInString(sql, "&", "%26");
    string url;
    url = getConfigValue("apiUrl") + "/selectMetadata.php";
    cpr::Response response =
        cpr::Post(cpr::Url{url}, cpr::Payload{{"sql", sql}});
    if (response.status_code == 200) {
      return nlohmann::json::parse(response.text);
    }

    return nlohmann::json::parse("");
  }
}