#include "Queen.h"
#include "Game.h"

#include <cmath>
#include <stdexcept>

Queen::Queen(Color col) : Piece(PieceType::Queen, col) {}

bool Queen::canMove(Game& game, const Position& from, const Position& to) {
		if (abs(to.getXPosition() - from.getXPosition()) == abs(to.getYPosition() - from.getYPosition())) {
			if (game.checkDiagonalPath(from, to)) return false;
			return true;
		}else if(from.getXPosition() == to.getXPosition() && from.getYPosition() != to.getYPosition()) {
			if (game.checkVerticalPath(from, to)) return false;
			return true;
		}
		else if (from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			if (game.checkHorizontalPath(from, to))  return false;
			return true;
		}
		else {
			return false;
		}
}
