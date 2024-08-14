#ifndef JSON_VALUE_DEF
#define JSON_VALUE_DEF

#include <memory>
#include <map>

struct NullHolder {

};

union JsonValue {
    int i;
    double d;
    bool b;
    NullHolder null;
    std::string s;
    std::unique_ptr<std::vector<JsonValue>> jsonArr;
    std::unique_ptr<std::map<std::string, JsonValue>> jsonObj; //allows pointing to nested json obj/array
};

#endif