#include "Database.hpp"
#include <iostream>
#include "macro.hpp"
#include <cpr/cpr.h>
#include "nlohman/json.hpp"

using json = nlohmann::json;
using namespace std;


/// @brief Returns JSON answer from API server
/// @param sql 
/// @return 
json Database::executeRemoteQuery(
  string sql
  ){
    sql = ReplaceString(sql,"&","%26");
    string url;
    url = getConfigValue("apiUrl") + "/selectMetadata.php";
    cpr::Response response = cpr::Post(
      cpr::Url{url},
      cpr::Payload{{"sql",sql}}
      );
    if (response.status_code == 200){
      return json::parse(response.text);
    }

return "";
}