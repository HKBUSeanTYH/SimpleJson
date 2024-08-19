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
#include <ranges>

class JsonValue;
using JsonVariant = std::variant<std::monostate, std::nullptr_t, int, double, bool, std::string, std::vector<JsonValue>, std::map<std::string, JsonValue>>;
template<class... Ts> 
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

class JsonValue : public JsonVariant{
    friend std::istream& operator >>(std::istream&, JsonValue&);
    friend std::ostream& operator <<(std::ostream&, const JsonValue&);
    public:
        using JsonVariant::JsonVariant;
};
#endif