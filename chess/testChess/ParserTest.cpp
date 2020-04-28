#include <gtest/gtest.h>
#include "../chess/Game.h"
#include <string>

TEST(ParserTest, skipWhiteSpacesTest) {
	Parser parser;
	std::string str = "    br00 bk01 bb02";
	parser.setStringToParse(str);
	std::string expected = "br00";
	ASSERT_EQ(parser.getNextToken(), expected);
	expected = "bk01";
	ASSERT_EQ(parser.getNextToken(), expected);
	expected = "bb02";
	ASSERT_EQ(parser.getNextToken(), expected);
	expected = "";
	ASSERT_EQ(parser.getNextToken(), expected);
}