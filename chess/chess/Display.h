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
	void displayRow(Board&, int, int, int, std::ostream&);
private:
	void initializePiecesTypeMap();
	void inititalizeColorMap();
	std::map<PieceType, char> piecesTypesMap;
	std::map<Color, char> colorMap;
	const int whiteSquare = 0xDB;
	const int blackSquare = 0xFF;
	const int subcells = 6;
};

