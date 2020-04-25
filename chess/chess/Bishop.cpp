#include "Bishop.h"
#include "Game.h"
#include <stdexcept>
#include <cmath>

Bishop::Bishop(Color col) : Piece(PieceType::Bishop, col) {}

void Bishop::canMove(Game& game, const Position& from, const Position& to) {
	try {
		if (abs(to.getXPosition() - from.getXPosition()) == abs(to.getYPosition() - from.getYPosition())) {
			if (to.getXPosition() > from.getXPosition() && to.getYPosition() < from.getYPosition()) {
				checkDiagonalInSomeDirection(game, from, to, 1, -1); //upper-right diagonal
			}
			else if (to.getXPosition() < from.getXPosition() && to.getYPosition() < from.getYPosition()) {
				checkDiagonalInSomeDirection(game, from, to, -1, -1); //upper-left diagonal
			}
			else if (to.getXPosition() < from.getXPosition() && to.getYPosition() > from.getYPosition()) {
				checkDiagonalInSomeDirection(game, from, to, -1, 1); //down-left diagonal
			}
			else if (to.getXPosition() > from.getXPosition() && to.getYPosition() > from.getYPosition()) {
				checkDiagonalInSomeDirection(game, from, to, 1, 1); // down-right diagonal
			}
		}
		else {
			throw std::logic_error("Bishop can't move like that!\n");
		}
	}
	catch (std::logic_error & er) {
		throw;
	}
}

void Bishop::checkDiagonalInSomeDirection(Game& game, const Position& from, const Position& to, int xDelta, int yDelta) {
	Position current = from;
	current.changeXPosition(xDelta);
	current.changeYPosition(yDelta);
	do {
		if (!game.getBoard().getCell(current).isEmpty()) throw std::logic_error("There is another piece on diagonal path!\n");
		current.changeXPosition(xDelta);
		current.changeYPosition(yDelta);
	} while (current != to);
}