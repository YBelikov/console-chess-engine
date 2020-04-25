#pragma once
#include "Piece.h"

class Queen : public Piece {
private:
	void checkDiagonalPath(Game&, const Position&, const Position&);
	void checkDiagonalInSomeDirection(Game&, const Position&, const Position&, int, int);
	void checkVerticalPath(Game&, const Position&, const Position&);
	void checkHorizontalPath(Game&, const Position&, const Position&);
public:
	Queen() = default;
	~Queen() = default;
	Queen(Color);
	void canMove(Game&, const Position&, const Position&) override;
};