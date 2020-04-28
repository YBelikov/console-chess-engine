#pragma once
#include <string>

class Parser {
private:
	std::string stringToParse;
	void skipWhiteSpaces();
	int position;
public:
	Parser() = default;
	void setStringToParse(std::string&);
	std::string getNextToken();
	bool reachEndOfTheLine();
};
