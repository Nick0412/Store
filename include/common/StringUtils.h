#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace Common::StringUtils
{
    std::vector<std::string> Split(const std::string& str, char delimiter);
}

#endif