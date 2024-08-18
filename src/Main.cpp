#include "JsonValue.h"
#include <sstream>

int main() {
    std::string input {"{ \"json\": \"sean\" }"};
    JsonValue root{};
    std::istringstream(input) >> root;
    return 0; 
}