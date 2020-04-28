#pragma once
#include <string>
#include <map>
#include <memory>
#include "Parser.h"
#include "Piece.h"

class Game;

class Loader {
private:
	std::map<char, PieceType> pieces;
	int turn;
	void loadNextPiece(Game&, std::string&);
	void createPiecesTable();
	void createPiece(Game&, Color, Position, PieceType);
	Parser parser;
	
public:
	Loader();
	void load(Game&, std::string&);
	int getTurn() const { return turn; }
};