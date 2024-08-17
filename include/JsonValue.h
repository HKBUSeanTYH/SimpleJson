#ifndef JSON_VALUE_DEF
#define JSON_VALUE_DEF

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <variant>
#include <cstddef>
#include <iostream>

namespace SimpleJson {
    class JsonValue;
    using JsonArray = std::vector<JsonValue>;
    using JsonObject = std::map<std::string, JsonValue>;
    using JsonValue = std::variant<std::monostate, std::nullptr_t, int, double, bool, std::string, JsonArray, JsonObject>;

    std::istream& operator >>(std::istream&, JsonValue&);
    // std::ostream& operator <<(std::ostream&, const JsonValue&);
}
#endif