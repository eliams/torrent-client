#include "bencode_parser.h"

#include <iostream>

#include <cctype>
#include <istream>
#include <string>

namespace bencode {

constexpr size_t MaxNumCharInteger = 19;

BencodeValue parseBencodeValue(std::istream& inputStream)
{
    char c = inputStream.peek();

    if (c == 'i')
        return parseInteger(inputStream);
    else if (std::isdigit(c))
        return parseString(inputStream);
    else if (c == 'l')
        return parseList(inputStream);
    else if (c == 'd')
        return parseDictionary(inputStream);

    return BencodeValue{std::monostate()};
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

    // Read the ending 'e'
    inputStream.get();

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

BencodeValue parseList(std::istream& inputStream)
{
    char c = inputStream.get();

    if (c != 'l')
        return BencodeValue{std::monostate()};

    BencodeValue bvalue{BencodeList{}};
    auto& list = std::get<BencodeList>(bvalue.value);

    do
    {
        list.push_back(parseBencodeValue(inputStream));
        c = inputStream.peek();
    }
    while (c != 'e');

    c = inputStream.get();

    return bvalue;
}

BencodeValue parseDictionary(std::istream& inputStream)
{
    char prefix = inputStream.get();

    if (prefix != 'd')
        return BencodeValue{std::monostate()};

    return BencodeValue{std::monostate()};
}

} // namespace bencode
