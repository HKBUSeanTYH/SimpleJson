#include "JsonValue.h"
#include <sstream>

int main() {
    std::string input {"{ \"json\": [1.0, 2.0, 3.0] }"};
    JsonValue root{};
    std::istringstream(input) >> root; 

    std::cout << root;
    return 0; 
}