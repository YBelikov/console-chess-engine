#pragma once
#include "PieceType.h"
#include "Color.h"

#include "Position.h"
class Board;

class Piece {
protected:
	PieceType type;
	Color color;
	bool killed;
public:
	Piece(PieceType type_, Color color_, bool killed_ = false) : type(type_), color(color_), killed(killed_) {}
	PieceType getPieceType() const noexcept { return type; }
	Color getColorOfPiece() const noexcept { return color; }
	bool isKilled() const noexcept { return killed; }
	void setKilled() noexcept { killed = true; }
	virtual bool canMove(Board&, const Position&, const Position&) { return true; };
	virtual ~Piece() {}
	
};