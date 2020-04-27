#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King() = default;
	~King() = default;
	King(Color);
	bool canMove(Game&, const Position&, const Position&) override;
};