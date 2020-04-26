#include "King.h"
#include <cmath>
#include "Game.h"
#include <stdexcept>

King::King(Color col) : Piece(PieceType::King, col){}

void King::canMove(Game& game, const Position& from, const Position& to) {
	if (!((abs(from.getXPosition() - to.getXPosition()) == 1 && from.getYPosition() == to.getYPosition()) ||
		abs(from.getYPosition() - to.getYPosition()) == 1 && from.getXPosition() == to.getXPosition() ||
		(abs(from.getYPosition() - to.getYPosition()) == 1 && abs(from.getXPosition() - to.getXPosition()) == 1))) {
		throw std::logic_error("King can't make this move!\n");
	}
}