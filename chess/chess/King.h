#pragma once
#include "Piece.h"

class King : public Piece {
public:
	King() = default;
	~King() = default;
	King(Color);
	void canMove(Game&, const Position&, const Position&) override;
};