#include "Parser.h"

void Parser::setStringToParse(std::string& newString) {
	stringToParse = newString;
	position = 0;
}

std::string Parser::getNextToken() {
	skipWhiteSpaces();
	int lastSymbolPosition = position;
	while (!std::isspace(stringToParse[lastSymbolPosition]) && !(lastSymbolPosition >= stringToParse.size())) {
		++lastSymbolPosition;
	}
 	std::string token = stringToParse.substr(position, lastSymbolPosition - position);
	position = lastSymbolPosition;
	return token;
}

void Parser::skipWhiteSpaces() {
	while (std::isspace(stringToParse[position])) {
		++position;
	}
}

bool Parser::reachEndOfTheLine() {
	return position == stringToParse.size();
}