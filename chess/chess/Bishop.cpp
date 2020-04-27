#include "Bishop.h"
#include "Game.h"
#include <stdexcept>
#include <cmath>

Bishop::Bishop(Color col) : Piece(PieceType::Bishop, col) {}

bool Bishop::canMove(Game& game, const Position& from, const Position& to) {
		if (abs(to.getXPosition() - from.getXPosition()) == abs(to.getYPosition() - from.getYPosition())) {
			if (game.checkDiagonalPath(from, to)) return false;
			return true;
		}
		else {
			return false;
		}
}
