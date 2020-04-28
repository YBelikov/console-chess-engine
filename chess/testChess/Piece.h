#pragma once
#include "PieceType.h"
#include "Color.h"

#include "Position.h"
class Board;
class Game;

class Piece {
protected:
	PieceType type;
	Color color;
public:
	Piece(PieceType type_, Color color_) : type(type_), color(color_) {}
	PieceType getPieceType() const noexcept { return type; }
	Color getColorOfPiece() const noexcept { return color; }
	virtual bool canMove(Game&, const Position&, const Position&) { return true; }
	virtual ~Piece() {}
	
};