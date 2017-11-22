#include "./buffer_util.h"

namespace {
    char hexdecimal_character[17] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    char binary_decimal_character[2] = { '0', '1' };
}

std::string algorithm::common::dumpBufferAsBinaryString(char* buf, std::size_t buf_size)
{
    std::string result;
    for (std::size_t buf_counter = 0; buf_counter < buf_size; ++buf_counter) {
        char current = *(buf + buf_counter);
        result.push_back( hexdecimal_character[ (current >> 4) & 0xf ] );
        result.push_back( hexdecimal_character[current & 0xf] );
        result.push_back(' ');
    }
    return result;
}

std::string algorithm::common::dumpBufferAsHexString(char *buf, std::size_t buf_size)
{
    std::string result;
    for (std::size_t buf_counter = 0; buf_counter < buf_size; ++buf_counter) {
        char current = *(buf + buf_counter);
        for (int bit_move_distance = 7; bit_move_distance >= 0; --bit_move_distance) {
            result.push_back( binary_decimal_character[ (current >> bit_move_distance) & 0x1 ] );
        }
        result.push_back(' ');
    }
    return result;
}