#include "Knight.h"
#include "Game.h"
#include <stdexcept>
#include <cmath>

Knight::Knight(Color col) : Piece(PieceType::Knight, col) {}

bool Knight::canMove(Game& game, const Position& from, const Position& to) {
	if (!((abs(from.getXPosition() - to.getXPosition()) == 1 && abs(from.getYPosition() - to.getYPosition()) == 2) ||
		(abs(from.getXPosition() - to.getXPosition()) == 2 && abs(from.getYPosition() - to.getYPosition()) == 1))) {
		return false;
	}
	return true;
}
