#include "bencode_parser.h"

#include <iostream>

#include <istream>
#include <string>

namespace bencode {

constexpr size_t MaxNumCharInteger = 19;

BencodeValue parseBencodeString(const std::string& str)
{
    if (str == "number")
        return BencodeValue{5};
    return BencodeValue{str};
}

BencodeValue parseInteger(std::istream& inputStream)
{
    char prefix = inputStream.get();

    if (prefix != 'i')
        return BencodeValue{std::monostate()};

    char signChar = inputStream.peek();
    int signMultipier = 1;

    if (signChar == '-')
    {
        signMultipier = -1;
        (void)inputStream.get();
    }

    long number = 0;

    inputStream >> number;

    if (inputStream.fail())
        return BencodeValue{std::monostate()};

    return BencodeValue{number * signMultipier};
}


BencodeValue parseString(std::istream& inputStream)
{
    size_t size = 0;

    inputStream >> size;

    if (inputStream.fail())
        return BencodeValue{std::monostate()};

    if (inputStream.get() != ':')
        return BencodeValue{std::monostate()};

    char content[size + 1];

    inputStream.read(content, size);
    content[size] = '\0';

    if (static_cast<size_t>(inputStream.gcount()) != size)
        return BencodeValue{std::monostate()};

    return BencodeValue{BencodeString{content}}; 
}

} // namespace bencode
