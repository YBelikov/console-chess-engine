#pragma once
#include <string>
#include <map>
#include "Color.h"
#include "PieceType.h"

class Game;

class Writer {
private:
	std::map<Color, char> colorMap;
	std::map<PieceType, char> piecesMap;
	void createColorMap();
	void createPiecesMap();

public:
	Writer();
	void writeBoardTo(Game&, std::string&);
};