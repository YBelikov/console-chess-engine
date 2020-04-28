#pragma once
#include "Piece.h"

class Knight : public Piece {

public:
	Knight() = default;
	Knight(Color);
	~Knight() = default;
	bool canMove(Game&, const Position&, const Position&) override;
};