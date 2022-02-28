
#include "bencode_parser.h"

#include <iostream>
#include <variant>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Torrent client v0.0.1" << std::endl;

    auto bvalue1 = bencode::parseBencodeString("number");
    auto bvalue2 = bencode::parseBencodeString("whatever");

    if (std::holds_alternative<long>(bvalue1))
        std::cout << "bvalue1 holds a number" << std::endl;

    if (std::holds_alternative<std::string>(bvalue2))
        std::cout << "bvalue2 holds a string" << std::endl;

    return 0;
}