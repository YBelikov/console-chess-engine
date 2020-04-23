#pragma once
#include <iostream>
#include <map>
#include "Board.h"
#include <string>

class Display
{
public:
	Display();
	void display(Board&, std::ostream&);
private:
	void initializePiecesTypeMap();
	void inititalizeColorMap();
	std::map<PieceType, std::string> piecesTypesMap;
	std::map<Color, std::string> colorMap;
};

