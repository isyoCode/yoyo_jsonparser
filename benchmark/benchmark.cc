#define ANKERL_NANOBENCH_IMPLEMENT
#include <jsoncpp/json/json.h>

#include "../src/json_parser.hpp"
#include "./nanobench.h"
#include "./nlohmannJson.hpp"

int main() {
  // 打开 JSON 文件
  std::ifstream inputFile("./test_data.json");
  if (!inputFile) {
    std::cerr << "Failed to open the JSON file!" << std::endl;
    return 1;
  }
  // 将文件内容读取到 std::string 中
  std::string jsonString;
  try {
    // 使用流迭代器直接读取文件内容
    inputFile.seekg(0, std::ios::end);  // 移动到文件末尾
    jsonString.reserve(
        inputFile.tellg());  // 提前调整字符串容量（非必须，但提高性能）
    inputFile.seekg(0, std::ios::beg);  // 回到文件开头
    jsonString.assign((std::istreambuf_iterator<char>(inputFile)),
                      std::istreambuf_iterator<char>());  // 读取内容
  } catch (const std::exception& e) {
    std::cerr << "Error while reading file: " << e.what() << std::endl;
    return 1;
  }

  /**
    ns/op：每个bench内容需要经历的时间（ns为单位）。
    op/s：每秒可以执行多少次操作。
    err%：运行多次测试的波动情况（误差）。
    ins/op：每次操作需要多少条指令。
    cyc/op：每次操作需要多少次时钟周期。
    bra/op：每次操作有多少次分支预判。
    miss%：分支预判的miss率。
    total：本次消耗的总时间。
    benchmark：对应的名字
*/
  ankerl::nanobench::Bench().run("my_tiny_jsonparser", [&jsonString] {
    yoyo::JsonValue jValue = yoyo::parserJson(jsonString);
    ankerl::nanobench::doNotOptimizeAway(jValue);
  });

  ankerl::nanobench::Bench().run("jsoncpp", [&jsonString] {
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream ifs(jsonString);
    if (!Json::parseFromStream(builder, ifs, &root, &errs)) {
      std::cerr << "Failed to parse JSON: " << errs << std::endl;
      return;
    }
    ankerl::nanobench::doNotOptimizeAway(root);
  });

  ankerl::nanobench::Bench().run("nlohmann_json", [&jsonString] {
    nlohmann::json j = nlohmann::json::parse(jsonString);
    ankerl::nanobench::doNotOptimizeAway(j);
  });
}
