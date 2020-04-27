#pragma once
#include "Piece.h"

class Queen : public Piece {

public:
	Queen() = default;
	~Queen() = default;
	Queen(Color);
	bool canMove(Game&, const Position&, const Position&) override;
};