#pragma once
#include "Piece.h"

class Bishop : public Piece {
private:
	void checkUpperRightDiagonalPath(Game&, const Position&, const Position&);
	void checkUpperLeftDiagonalPath(Game&, const Position&, const Position&);
	void checkDownLeftDiagonalPath(Game&, const Position&, const Position&);
	void checkDownRightDiagonalPath(Game&, const Position&, const Position&);
	void checkDiagonalInSomeDirection(Game&, const Position&, const Position&, int, int);
public:
	Bishop() = default;
	~Bishop() = default;
	Bishop(Color);
	void canMove(Game&, const Position&, const Position&) override;
};