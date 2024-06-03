#include "utils.h"
#include <sstream>

Position parsePosition(const std::string& input) {
    if (input.length() < 2) {
        throw std::out_of_range("Invalid input length");
    }
    return { input[1] - '1', input[0] - 'a' };
}
