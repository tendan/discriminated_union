#include <iostream>
#include <map>
#include "results.h"

Result<int, std::string> dummy_function() {
    return 5;
}

Result<int, std::string> dummy_with_error(int param) {
    switch (param) {
        case 1:
        case 2:
        case 3:
            return param;
        default:
            return std::string("Invalid parameter");
    }
}

Result<int, const char*> parseInt(const std::basic_string<char>& stringToParse) {
    try {
        return stoi(stringToParse);
    } catch (const std::invalid_argument& ex) {
        return ex.what();
    }
}

int main() {

    return 0;
}
