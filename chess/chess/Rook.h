#pragma once
#include "Piece.h"
#include "Color.h"

class Rook : public Piece{

private:
	void checkVerticalPath(const Game&, const Position&, const Position&);
	void checkHorizontalPath(const Game&, const Position&, const Position&);
public:
	Rook() = default;
	~Rook() = default;
	Rook(Color);
	void canMove(Game&, const Position&, const Position&) override;
};

