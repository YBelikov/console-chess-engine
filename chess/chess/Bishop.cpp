#include "Bishop.h"
#include "Game.h"
#include <stdexcept>
#include <cmath>

Bishop::Bishop(Color col) : Piece(PieceType::Bishop, col) {}

void Bishop::canMove(Game& game, const Position& from, const Position& to) {
	try {
		if (abs(to.getXPosition() - from.getXPosition()) == abs(to.getYPosition() - from.getYPosition())) {
			if (game.checkDiagonalPath(from, to)) throw std::logic_error("There is a piece on diagonal! Bishop can't jump over it!\n");
		}
		else {
			throw std::logic_error("Bishop can't move like that!\n");
		}
	}
	catch (std::logic_error & er) {
		throw;
	}
}
