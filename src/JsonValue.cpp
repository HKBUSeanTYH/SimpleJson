#include "JsonValue.h"

std::istream& operator>>(std::istream& is, SimpleJson::JsonValue& json_val) {
    std::istream::sentry sentry{is};
    if (sentry) {
        
    } else {
        is.setstate(is.rdstate() | std::ios_base::failbit);
        json_val = SimpleJson::JsonValue{};
    }
    return is;
}

// std::ostream& operator<<(std::ostream& os, const SimpleJson::JsonValue& json_val) {

// }