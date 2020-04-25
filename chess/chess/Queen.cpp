#include "Queen.h"
#include "Game.h"

#include <cmath>
#include <stdexcept>

Queen::Queen(Color col) : Piece(PieceType::Queen, col) {}

void Queen::canMove(Game& game, const Position& from, const Position& to) {
	try {
		if (abs(to.getXPosition() - from.getXPosition()) == abs(to.getYPosition() - from.getYPosition())) {
			checkDiagonalPath(game, from, to);
		}else if(from.getXPosition() == to.getXPosition() && from.getYPosition() != to.getYPosition()) {
			checkVerticalPath(game, from, to);
		}
		else if (from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			checkHorizontalPath(game, from, to);
		}
		else {
			throw std::logic_error("Queen can't make this move!\n");
		}
	}
	catch (std::logic_error & ex) {
		throw;
	}
}


void Queen::checkDiagonalPath(Game& game, const Position& from, const Position& to) {
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

void Queen::checkDiagonalInSomeDirection(Game& game, const Position& from, const Position& to, int xDelta, int yDelta) {
	Position current = from;
	current.changeXPosition(xDelta);
	current.changeYPosition(yDelta);
	while (current != to) {
		if (!game.getBoard().getCell(current).isEmpty()) throw std::logic_error("There is another piece on diagonal path!\n");
		current.changeXPosition(xDelta);
		current.changeYPosition(yDelta);
	}
}

void Queen::checkVerticalPath(Game& game, const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getYPosition() > from.getYPosition() ? 1 : -1;
	cell.changeYPosition(difference);
	if (to.getYPosition() > from.getYPosition()) {
		while (cell.getYPosition() < to.getYPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Queen can't jump over it!\n");
			cell.changeYPosition(difference);
		}
	}
	else if (to.getYPosition() < from.getYPosition()) {
		while (cell.getYPosition() > to.getYPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Queen can't jump over it!\n");
			cell.changeYPosition(difference);
		}
	}

}

void Queen::checkHorizontalPath(Game& game, const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getXPosition() > from.getXPosition() ? 1 : -1;
	cell.changeXPosition(difference);
	if (to.getXPosition() > from.getXPosition()) {
		while (cell.getXPosition() < to.getXPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Queen can't jump over it!\n");
			cell.changeXPosition(difference);
		}
	}
	else if (to.getXPosition() < from.getXPosition()) {
		while (cell.getXPosition() > to.getXPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Queen can't jump over it!\n");
			cell.changeXPosition(difference);
		}
	}

}