//
// Created by uab on 5/16/24.
//

#include "hex.h"

#include <sstream>
#include <iomanip>

std::string buffer_to_hex(char* buffer, ssize_t buffer_size)
{
    std::stringstream ss;
    for (size_t i = 0; i < buffer_size; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (static_cast<int>(buffer[i]) & 0xff) << " ";

    return ss.str();
}
