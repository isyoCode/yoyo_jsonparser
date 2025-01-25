#include "../src/json_parser.hpp"

std::string sJson = R"({
  "name": "example",
  "version": 1,
  "description": "This is a sample JSON file.",
  "enabled": true
})";

void usage01() {
  yoyo::JsonValue root;
  yoyo::JsonParser parser(sJson);
  root = parser.parser();
  std::string sName = root["name"];
  int iVersion = root["version"];
  bool bEnable = root["enabled"];
  std::cout << "sName: " << sName << "\n"
            << "iVersion: " << iVersion << "\n"
            << "bEnable: " << bEnable << std::endl;
}

void usage02() {
  yoyo::JsonValue root = yoyo::parserJson(sJson);
  std::string sName = root["name"];
  int iVersion = root["version"];
  bool bEnable = root["enabled"];
  std::cout << "sName: " << root["name"] << "\n"
            << "iVersion: " << root["version"] << "\n"
            << "bEnable: " << root["enabled"] << std::endl;

  // std::cout << root.writeToString() << std::endl;
}

int main() {
  usage01();
  usage02();
  return 0;
}
