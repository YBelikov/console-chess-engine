#pragma once
#include "Piece.h"

class Bishop : public Piece {	
public:
	Bishop() = default;
	~Bishop() = default;
	Bishop(Color);
	bool canMove(Game&, const Position&, const Position&) override;
};