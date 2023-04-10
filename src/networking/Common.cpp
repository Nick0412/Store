#include "networking/Common.h"
#include "common/StringUtils.h"
#include "networking/Constants.h"

#include <stdexcept>
#include <string>
#include <sstream>

namespace Networking::Common
{
    void ValidateIpAddress(const std::string& ip_address)
    {
        auto ip_address_string_blocks = ::Common::StringUtils::Split(ip_address, '.');
        try 
        {
            ValidateIpNumberOfBytes(ip_address_string_blocks);
            ValidateIpBlocksAreInRange(ip_address_string_blocks);
        }
        catch (std::runtime_error& ex)
        {
            std::ostringstream string_stream;
            string_stream << "Invalid IP: " << ip_address << "\n" << ex.what();
            
            throw std::runtime_error(string_stream.str());
        }
    }

    void ValidateIpNumberOfBytes(const std::vector<std::string>& ip_blocks)
    {
        if (ip_blocks.size() != Networking::Constants::IP_NUMBER_OF_BYTES)
        {
            std::ostringstream string_stream;
            string_stream << "Number of IP bytes does not equal "
                          << Networking::Constants::IP_NUMBER_OF_BYTES << "\n";

            throw std::runtime_error(string_stream.str());
        }
    }

    void ValidateIpBlocksAreInRange(const std::vector<std::string>& ip_blocks)
    {
        for (const auto& block_string : ip_blocks)
        {
            int block_number = std::stoi(block_string);
            if (block_number > Networking::Constants::MAX_VALUE_OF_IP_BLOCK ||
                block_number < Networking::Constants::MIN_VALUE_OF_IP_BLOCK)
            {
                std::ostringstream string_stream;
                string_stream << "IP block number is not in the range of ["
                              << Networking::Constants::MIN_VALUE_OF_IP_BLOCK << ", "
                              << Networking::Constants::MAX_VALUE_OF_IP_BLOCK << "]\n";

                throw std::runtime_error(string_stream.str());
            }
        }
    }
}