#pragma once
#include "PieceType.h"
#include "Color.h"

class Piece {
protected:
	PieceType type;
	Color color;
	bool isKilled;
public:
	Piece(PieceType type_, Color color_, bool isKilled_ = false) : type(type_), color(color_), isKilled(isKilled_) {}
	PieceType getPieceType() const noexcept { return type; }
	Color getColorOfPiece() const noexcept { return color; }
	bool isKilled() const noexcept { return isKilled; }
	void setKilled() noexcept { isKilled = true; }
	virtual ~Piece() {}
	
};