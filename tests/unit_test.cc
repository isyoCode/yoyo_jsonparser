#include <string>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../src/json_parser.hpp"
#include "./doctest.h"

const std::string jsonStr = R"(
    {
        "company": {
            "name": "Tech Innovators Inc.",
            "location": {
                "city": "New York",
                "country": "USA",
                "address": {
                    "street": "123 Main St",
                    "zip": "10001"
                }
            },
            "employees": [
                {
                    "id": 1,
                    "name": "Alice Johnson",
                    "department": "Engineering",
                    "projects": [
                        {
                            "project_name": "AI - Driven Chatbot",
                            "start_date": "2024 - 01 - 15",
                            "end_date": null,
                            "team_members": [
                                {
                                    "member_id": 2,
                                    "member_name": "Bob Smith"
                                },
                                {
                                    "member_id": 3,
                                    "member_name": "Charlie Brown"
                                }
                            ]
                        },
                        {
                            "project_name": "Data Analytics Platform",
                            "start_date": "2023 - 09 - 01",
                            "end_date": "2024 - 12 - 31",
                            "team_members": [
                                {
                                    "member_id": 4,
                                    "member_name": "David Lee"
                                }
                            ]
                        }
                    ]
                },
                {
                    "id": 5,
                    "name": "Eve Davis",
                    "department": "Marketing",
                    "campaigns": [
                        {
                            "campaign_name": "Product Launch",
                            "budget": 50000.00,
                            "channels": [
                                "Social Media",
                                "Email",
                                "TV"
                            ]
                        }
                    ]
                }
            ],
            "financials": {
                "revenue": 1000000.00,
                "expenses": {
                    "salaries": 600000.00,
                    "office_rent": 100000.00,
                    "marketing_costs": 150000.00
                },
                "profit": 150000.00
            },
            "is_publicly_traded": true
        }
    }
    )";

bool jsonParserIsSuccessful() {
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  return jValue.get<yoyo::JsonFiled::json_object>().size() > 0;
}

TEST_CASE("testing the json parser") {
  CHECK(jsonParserIsSuccessful() == true);
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  auto json_object = [&jValue]() -> bool { return jValue.isObject(); };

  auto company_obj = [&jValue]() -> bool {
    return jValue["company"].isObject();
  };
  auto company_name = [&jValue]() -> bool {
    return jValue["company"]["name"].isString();
  };
  auto company_location = [&jValue]() -> bool {
    return jValue["company"]["location"]["city"].get<std::string>() ==
           "New York";
  };
  auto company_employees = [&jValue]() -> bool {
    return jValue["company"]["employees"].isArray();
  };

  auto company_employees_id = [&jValue]() -> bool {
    return jValue["company"]["employees"][0]["id"].get<int>() == 1;
  };
  auto company_employees_projects_end_date = [&jValue]() -> bool {
    return jValue["company"]["employees"][0]["projects"][0]["end_date"]
        .isNull();
  };

  auto company_employees_projects_team_members = [&jValue]() -> bool {
    return jValue["company"]["employees"][0]["projects"][0]["team_members"]
               .isArray() &&
           jValue["company"]["employees"][0]["projects"][0]["team_members"]
                   .size() == 2;
  };

  auto company_employees_is_members_or_not_member = [&jValue]() -> bool {
    return jValue.isMember("company") &&
           (jValue.isMember("companyyoyoyoxxxxx") == false);
  };

  auto company_financials = [&jValue]() -> bool {
    return jValue["company"]["financials"].isObject();
  };

  auto company_financials_revenue = [&jValue]() -> bool {
    return jValue["company"]["financials"]["revenue"].get<double>() ==
           1000000.00;
  };

  auto company_is_publicly_traded = [&jValue]() -> bool {
    return jValue["company"]["is_publicly_traded"].get<bool>() == true;
  };

  CHECK(json_object() == true);
  CHECK(company_obj() == true);
  CHECK(company_name() == true);
  CHECK(company_location() == true);
  CHECK(company_employees() == true);
  CHECK(company_employees_id() == true);
  CHECK(company_employees_projects_end_date() == true);
  CHECK(company_employees_projects_team_members() == true);
  CHECK(company_employees_is_members_or_not_member() == true);
  CHECK(company_financials() == true);
  CHECK(company_financials_revenue() == true);
  CHECK(company_is_publicly_traded() == true);
}

// 测试操作符重载
TEST_CASE("testing Operator overloading") {
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  auto company_location_overloadEqual = [&jValue]() -> bool {
    return (jValue["company"]["location"]["city"] == "New York") ||
           (std::string("New York") ==
            static_cast<std::string>(
                jValue["company"]["location"]["city"])); /**未提供右侧重载方法*/
  };

  auto company_employees_id_overloadEqual = [&jValue]() -> bool {
    return jValue["company"]["employees"][0]["id"] == 1;
  };

  auto company_financials_revenue_overloadEqual = [&jValue]() -> bool {
    return jValue["company"]["financials"]["revenue"] == 1000000.00;
  };

  auto company_is_publicly_traded_overloadEqual = [&jValue]() -> bool {
    return jValue["company"]["is_publicly_traded"] == true;
  };

  CHECK(company_location_overloadEqual() == true);
  CHECK(company_employees_id_overloadEqual() == true);
  CHECK(company_financials_revenue_overloadEqual() == true);
  CHECK(company_is_publicly_traded_overloadEqual() == true);
}

// 测试隐式转换
TEST_CASE("testing Implicit conversion") {
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  auto company_location_implicit = [&jValue]() -> bool {
    std::string city = jValue["company"]["location"]["city"];
    return city == "New York";
  };

  auto company_employees_id_implicit = [&jValue]() -> bool {
    int id = jValue["company"]["employees"][0]["id"];
    return id == 1;
  };

  auto company_financials_revenue_implicit = [&jValue]() -> bool {
    double revenue = jValue["company"]["financials"]["revenue"];
    return revenue == 1000000.00;
  };

  auto company_is_publicly_traded_implicit = [&jValue]() -> bool {
    bool isPubliclyTraded = jValue["company"]["is_publicly_traded"];
    return isPubliclyTraded == true;
  };

  CHECK(company_location_implicit() == true);
  CHECK(company_employees_id_implicit() == true);
  CHECK(company_financials_revenue_implicit() == true);
  CHECK(company_is_publicly_traded_implicit() == true);
}

// 测试显示转换
TEST_CASE("testing Explicit conversion") {
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  auto company_location_explicit = [&jValue]() -> bool {
    auto city = jValue["company"]["location"]["city"].asString();
    return city == "New York";
  };

  auto company_employees_id_explicit = [&jValue]() -> bool {
    auto id = jValue["company"]["employees"][0]["id"].asInt();
    return id == 1;
  };

  auto company_financials_revenue_explicit = [&jValue]() -> bool {
    auto revenue = jValue["company"]["financials"]["revenue"].asDouble();
    return revenue == 1000000.00;
  };

  auto company_is_publicly_traded_explicit = [&jValue]() -> bool {
    auto isPubliclyTraded = jValue["company"]["is_publicly_traded"].asBool();
    return isPubliclyTraded == true;
  };

  CHECK(company_location_explicit() == true);
  CHECK(company_employees_id_explicit() == true);
  CHECK(company_financials_revenue_explicit() == true);
  CHECK(company_is_publicly_traded_explicit() == true);
}
// 测试打印输出
TEST_CASE("testing print out") {
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  auto print_json_string = [&jValue]() -> bool {
    // yoyo::PrintJson(jValue);
    return true;
  };

  auto serialize_jsonValue_toString = [&jValue]() -> bool {
    std::string str = jValue.writeToString();
    // std::cout << str << std::endl;
    return str.size() > 0;
  };

  auto serialize_jsonValue_toString_to_deserialize = [&jValue]() -> bool {
    std::string str = jValue.writeToString();
    yoyo::JsonValue jValue2 = yoyo::parserJson(str);
    // yoyo::PrintJson(jValue2);
    return jValue2.size() > 0;
  };
  CHECK(print_json_string() == true);
  CHECK(serialize_jsonValue_toString() == true);
  CHECK(serialize_jsonValue_toString_to_deserialize() == true);
}

// 测试数组添加对象
TEST_CASE("testing add object to array") {
  yoyo::JsonValue jValue = yoyo::parserJson(jsonStr);
  auto add_object_to_array = [&jValue]() -> bool {
    yoyo::JsonValue newObject;
    newObject["name"] = "John Doe";
    newObject["age"] = 30;
    newObject["isMarried"] = false;
    yoyo::PrintJson(newObject);
    jValue["company"]["employees"].push_back(newObject);
    return jValue["company"]["employees"].size() == 3;
  };

  auto add_object_to_array_with_move = [&jValue]() -> bool {
    yoyo::JsonValue newObject;
    newObject["name"] = "John Doe";
    newObject["age"] = 30;
    newObject["isMarried"] = false;
    jValue["company"]["employees"].push_back(std::move(newObject));
    return jValue["company"]["employees"].size() == 4;
  };

  auto add_object = []() -> bool {
    yoyo::JsonValue newObject;
    newObject["array"].push_back("yoyo");
    yoyo::PrintJson(newObject);
    return newObject.size() == 1;
  };

  CHECK(add_object_to_array() == true);
  CHECK(add_object_to_array_with_move() == true);
  CHECK(add_object() == true);
}