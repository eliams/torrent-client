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

TEST_F(BencodeParserTest, parseStringInvalidSize)
{
    _ss.str("abc:def");

    auto bvalue = bencode::parseString(_ss);

    EXPECT_THAT(std::holds_alternative<std::monostate>(bvalue.value), testing::IsTrue());
}

TEST_F(BencodeParserTest, parseStringInvalidSeparator)
{
    _ss.str("3-abc");

    auto bvalue = bencode::parseString(_ss);

    EXPECT_THAT(std::holds_alternative<std::monostate>(bvalue.value), testing::IsTrue());
}

TEST_F(BencodeParserTest, parseListOneInteger)
{
    _ss.str("li34ee");

    auto bvalue = bencode::parseList(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeList>(bvalue.value), testing::IsTrue());

    auto list = std::get<bencode::BencodeList>(bvalue.value);

    EXPECT_THAT(list.size(), testing::Eq(1));
    EXPECT_THAT(std::holds_alternative<bencode::BencodeInt>(list.front().value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>(list.front().value), testing::Eq(34));
}

TEST_F(BencodeParserTest, parseListOneString)
{
    _ss.str("l5:helloe");

    auto bvalue = bencode::parseList(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeList>(bvalue.value), testing::IsTrue());

    auto list = std::get<bencode::BencodeList>(bvalue.value);

    EXPECT_THAT(list.size(), testing::Eq(1));
    EXPECT_THAT(std::holds_alternative<bencode::BencodeString>(list.front().value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeString>(list.front().value), testing::StrEq("hello"));
}

TEST_F(BencodeParserTest, parseListTwoIntegers)
{
    _ss.str("li1ei2ee");

    auto bvalue = bencode::parseList(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeList>(bvalue.value), testing::IsTrue());

    auto list = std::get<bencode::BencodeList>(bvalue.value);
    auto it = list.cbegin();

    EXPECT_THAT(list.size(), testing::Eq(2));
    EXPECT_THAT(std::holds_alternative<bencode::BencodeInt>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>((*it).value), testing::Eq(1));

    it++;

    EXPECT_THAT(std::holds_alternative<bencode::BencodeInt>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>((*it).value), testing::Eq(2));
}

TEST_F(BencodeParserTest, parseListTwoStrings)
{
    _ss.str("l5:hello5:worlde");

    auto bvalue = bencode::parseList(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeList>(bvalue.value), testing::IsTrue());

    auto list = std::get<bencode::BencodeList>(bvalue.value);
    auto it = list.cbegin();

    EXPECT_THAT(list.size(), testing::Eq(2));
    EXPECT_THAT(std::holds_alternative<bencode::BencodeString>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeString>((*it).value), testing::StrEq("hello"));

    it++;

    EXPECT_THAT(std::holds_alternative<bencode::BencodeString>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeString>((*it).value), testing::StrEq("world"));
}

TEST_F(BencodeParserTest, parseListMultipleElements)
{
    _ss.str("l5:helloi12e5:worldi56ee");

    auto bvalue = bencode::parseList(_ss);

    ASSERT_THAT(std::holds_alternative<bencode::BencodeList>(bvalue.value), testing::IsTrue());

    auto list = std::get<bencode::BencodeList>(bvalue.value);
    auto it = list.cbegin();

    EXPECT_THAT(list.size(), testing::Eq(4));
    EXPECT_THAT(std::holds_alternative<bencode::BencodeString>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeString>((*it).value), testing::StrEq("hello"));

    it++;

    EXPECT_THAT(std::holds_alternative<bencode::BencodeInt>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>((*it).value), testing::Eq(12));

    it++;

    EXPECT_THAT(std::holds_alternative<bencode::BencodeString>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeString>((*it).value), testing::StrEq("world"));

    it++;

    EXPECT_THAT(std::holds_alternative<bencode::BencodeInt>((*it).value), testing::IsTrue());
    EXPECT_THAT(std::get<bencode::BencodeInt>((*it).value), testing::Eq(56));
}