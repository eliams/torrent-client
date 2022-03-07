#pragma once

#include <list>
#include <map>
#include <string>
#include <variant>

namespace bencode {

struct BencodeValue;

using BencodeInt = long;
using BencodeString = std::string;
using BencodeList = std::list<BencodeValue>;
using BencodeDictionary = std::map<BencodeString, BencodeValue>;

struct BencodeValue
{
    std::variant<std::monostate, BencodeInt, BencodeString, BencodeList, BencodeDictionary> value;
};

BencodeValue parseBencodeString(const std::string& str);

BencodeValue parseInteger(std::istream& inputStream);
BencodeValue parseString(std::istream& inputStream);
BencodeValue parseList(std::istream& inputStream);
BencodeValue parseDictionary(std::istream& inputStream);

} // namespace bencode
