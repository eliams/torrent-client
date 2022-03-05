#include <bencode_parser.h>

#include <sstream>
#include <gmock/gmock.h>
#include <variant>

class BencodeParserTest : public testing::Test
{
protected:
    std::stringstream _ss;
};

TEST_F(BencodeParserTest, parseIntegerZero)
{
    _ss.str("i0e");

    auto bvalue = bencode::parseInteger(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeInt>(bvalue.value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>(bvalue.value), testing::Eq(0));
}

TEST_F(BencodeParserTest, parseIntegerPositiveNumber)
{
    _ss.str("i42e");

    auto bvalue = bencode::parseInteger(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeInt>(bvalue.value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>(bvalue.value), testing::Eq(42));
}

TEST_F(BencodeParserTest, parseIntegerNegativeNumber)
{
    _ss.str("i-21e");

    auto bvalue = bencode::parseInteger(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeInt>(bvalue.value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>(bvalue.value), testing::Eq(-21));
}
