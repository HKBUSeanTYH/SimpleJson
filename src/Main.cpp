#include "JsonValue.h"
#include <sstream>

int main() {
    std::string input {"{ \"json\": \n1.0 }"};
    JsonValue root{};
    std::istringstream(input) >> root;
    return 0; 
}