#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>

template <typename T>
T getDigitFromHex(const std::string& hexVal)
{
    T res {};
    std::stringstream ss;

    if (hexVal.compare(0, 2, "0x") == 0 || hexVal.compare(0, 2, "0X") == 0) {
        ss << std::hex << hexVal.substr(2);
    } else {
        ss << std::hex << hexVal;
    }

    ss >> res;

    return res;
}

#endif // UTILS_HPP
