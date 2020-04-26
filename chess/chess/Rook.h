#pragma once
#include "Piece.h"
#include "Color.h"

class Rook : public Piece{


public:
	Rook() = default;
	~Rook() = default;
	Rook(Color);
	void canMove(Game&, const Position&, const Position&) override;
};

