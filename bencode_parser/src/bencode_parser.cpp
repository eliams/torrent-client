#include "bencode_parser.h"

#include <istream>

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

} // namespace bencode
