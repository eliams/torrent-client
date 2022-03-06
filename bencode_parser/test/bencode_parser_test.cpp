#include <bencode_parser.h>

#include <gmock/gmock.h>
#include <sstream>
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

TEST_F(BencodeParserTest, parseIntegerInvalidValue)
{
    _ss.str("iabce");

    auto bvalue = bencode::parseInteger(_ss);

    EXPECT_THAT(std::holds_alternative<std::monostate>(bvalue.value), testing::IsTrue());
}

TEST_F(BencodeParserTest, parseIntegerInvalidPrefix)
{
    _ss.str("a123e");

    auto bvalue = bencode::parseInteger(_ss);

    EXPECT_THAT(std::holds_alternative<std::monostate>(bvalue.value), testing::IsTrue());
}

TEST_F(BencodeParserTest, parseStringSimple)
{
    _ss.str("5:hello");

    auto bvalue = bencode::parseString(_ss);
    
    ASSERT_THAT(std::holds_alternative<bencode::BencodeString>(bvalue.value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeString>(bvalue.value), testing::StrEq("hello"));
}
