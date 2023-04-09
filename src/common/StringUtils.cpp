#include "common/StringUtils.h"

#include <iostream>

namespace Common::StringUtils
{
    std::vector<std::string> Split(const std::string& str, char delimiter)
    {
        std::vector<std::string> strings;

        std::size_t previous_delimter_position = 0;
        std::size_t next_delimter_position = str.find(delimiter, previous_delimter_position);

        while (next_delimter_position != std::string::npos)
        {                      
            std::size_t string_size = next_delimter_position - previous_delimter_position;
            std::string sub_string = str.substr(previous_delimter_position, string_size);

            strings.push_back(sub_string);

            previous_delimter_position = next_delimter_position + 1;
            next_delimter_position = str.find(delimiter, previous_delimter_position);
        }

        strings.push_back(str.substr(
            previous_delimter_position,
            str.size() - previous_delimter_position));

        return strings;
    }
}