#include <bencode_parser.h>

#include <sstream>
#include <gmock/gmock.h>
#include <variant>

TEST(BencodeParser, parseIntegerZero)
{
    std::stringstream ss;
    ss.str("i0e");

    auto bvalue = bencode::parseInteger(ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeInt>(bvalue.value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>(bvalue.value), testing::Eq(0));
}
