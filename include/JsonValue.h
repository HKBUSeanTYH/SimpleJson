#ifndef JSON_VALUE_DEF
#define JSON_VALUE_DEF

#include <memory>
#include <map>
#include <vector>
#include <string>
#include <variant>
#include <cstddef>
#include <iostream>
#include <exception>

struct JsonValue;
struct JsonValue {
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    using JsonVariant = std::variant<std::monostate, std::nullptr_t, int, double, bool, std::string, std::vector<JsonValue>, std::map<std::string, JsonValue>>;
    JsonVariant data_;
};
std::istream& operator >>(std::istream&, JsonValue&);
// std::ostream& operator <<(std::ostream&, const JsonValue&);
#endif