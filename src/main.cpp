
#include "bencode_parser.h"

#include <iostream>
#include <sstream>
#include <variant>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Torrent client v0.0.1" << std::endl;

    auto bvalue1 = bencode::parseBencodeString("number");
    auto bvalue2 = bencode::parseBencodeString("whatever");

    if (std::holds_alternative<bencode::BencodeInt>(bvalue1.value))
        std::cout << "bvalue1 holds a number" << std::endl;

    if (std::holds_alternative<bencode::BencodeString>(bvalue2.value))
        std::cout << "bvalue2 holds a string" << std::endl;

    std::stringstream ss;

    ss.str("i42e");
    auto bvalue3 = bencode::parseInteger(ss);
    if (std::holds_alternative<bencode::BencodeInt>(bvalue3.value))
        std::cout << "bvalue3 holds an integer, value:" << std::get<long>(bvalue3.value) << std::endl;
    else
        std::cout << "error parsing: " << ss.str() << std::endl;

    ss.str("i-41e");
    auto bvalue4 = bencode::parseInteger(ss);
    if (std::holds_alternative<bencode::BencodeInt>(bvalue4.value))
        std::cout << "bvalue4 holds an integer, value:" << std::get<long>(bvalue4.value) << std::endl;
    else
        std::cout << "error parsing: " << ss.str() << std::endl;

    ss.str("i0e");
    auto bvalue5 = bencode::parseInteger(ss);
    if (std::holds_alternative<bencode::BencodeInt>(bvalue5.value))
        std::cout << "bvalue5 holds an integer, value:" << std::get<long>(bvalue5.value) << std::endl;
    else
        std::cout << "error parsing: " << ss.str() << std::endl;

    return 0;
}