//
// Created by uab on 5/17/24.
//

#include "string_utils.h"

#include <numeric>
#include <sstream>

std::string join(const std::vector<std::string>& arr, const std::string& delim)
{
    return std::accumulate
    (
        std::next(arr.begin()),
        arr.end(),
        arr[0],
        [delim](std::string a, std::string b) { return a + delim + b; }
    );
}

std::string vec_to_string(const std::vector<std::string>& arr)
{
    return "[" + join(arr, ", ") + "]";
}