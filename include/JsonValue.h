#ifndef JSON_VALUE_DEF
#define JSON_VALUE_DEF

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <variant>
#include <cstddef>
#include <iostream>

struct JsonValue;
struct JsonValue {
    std::variant<std::monostate, std::nullptr_t, int, double, bool, std::string, std::vector<JsonValue>, std::map<std::string, JsonValue>> data_;
};
std::istream& operator >>(std::istream&, JsonValue&);
// std::ostream& operator <<(std::ostream&, const JsonValue&);
#endif