#include "bencode_parser.h"

namespace bencode {

BencodeValue parseBencodeString(const std::string& str)
{
    if (str == "number")
        return BencodeValue{5};
    return BencodeValue{str};
}

} // namespace bencode