//
// Created by uab on 5/15/24.
//

#ifndef TRAFFIC_GENERATOR_HEX_H
#define TRAFFIC_GENERATOR_HEX_H

#include <sstream>
#include <iomanip>

std::string buffer_to_hex(char* buffer, ssize_t buffer_size)
{
    std::stringstream ss;
    for (size_t i = 0; i < buffer_size; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (static_cast<int>(buffer[i]) & 0xff) << " ";
    }

    return ss.str();
}

#endif //TRAFFIC_GENERATOR_HEX_H
