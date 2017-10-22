#include "buffer_util.h"

namespace algorithm
{
    namespace common
    {
        namespace {
            char hexdecimal_character[17] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'A', 'B', 'C', 'D', 'E', 'F' };
        }

        std::string dumpBufferAsHexString(char *buf, std::size_t buf_size)
        {
            std::string result;
            for (std::size_t buf_counter = 0; buf_counter < buf_size; ++buf_counter) {
                char current = *(buf + buf_counter);
                if (current > 0) {
                    int tens_place = current / 16;
                    int ones_place = current % 16;
                    result.push_back(hexdecimal_character[tens_place]);
                    result.push_back(hexdecimal_character[ones_place]);
                }
                result.push_back(' ');
            }
            return result;
        }

        std::string dumpBufferAsBinaryString(char *buf, std::size_t buf_size)
        {
            std::string result;
            return result;
        }
    }
}
