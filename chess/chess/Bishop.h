#pragma once
#include "Piece.h"

class Bishop : public Piece {
private:
	/*void checkDiagonalInSomeDirection(Game&, const Position&, const Position&, int, int);*/
public:
	Bishop() = default;
	~Bishop() = default;
	Bishop(Color);
	void canMove(Game&, const Position&, const Position&) override;
};