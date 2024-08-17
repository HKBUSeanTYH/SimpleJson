#include "JsonValue.h"


std::istream& operator>>(std::istream& is, JsonValue& json_val) {
    std::istream::sentry sentry{is};  //trims leading whitespace
    if (sentry) {
        std::string json{std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>()};  //construct the json string from a pair of iterators
        std::cout << "Sean: " << json << std::endl;
    } else {
        is.setstate(is.rdstate() | std::ios_base::failbit);
        json_val = JsonValue{};
    }
    return is;
}

// std::ostream& operator<<(std::ostream& os, const SimpleJson::JsonValue& json_val) {

// }