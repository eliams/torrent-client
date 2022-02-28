#pragma once

#include <variant>
#include <string>

namespace bencode {

using BencodeValue = std::variant<long, std::string>;

BencodeValue parseBencodeString(const std::string& str);

} // namespace bencode