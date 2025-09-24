#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>

template<typename T>
T getDigitFromHex(const std::string& hexVal)
{
    T res {};

    std::stringstream ss;
    ss << std::hex << hexVal;
    ss >> res;

    return res;
}

#endif // UTILS_HPP
