#include "Rook.h"
#include "Game.h"
#include <stdexcept>

Rook::Rook(Color col) : Piece(PieceType::Rook, col) {}

void Rook::canMove(Game& game, const Position& from, const Position& to) {
	
	try {
		if (from.getXPosition() == to.getXPosition() && from.getYPosition() != to.getYPosition()) {
			checkVerticalPath(game, from, to);
		}
		else if (from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			checkHorizontalPath(game, from, to);
		}
		else throw std::logic_error("Rook can't move like this!\n");
	}
	catch (std::logic_error & er) {
		throw;
	}
}

void Rook::checkVerticalPath(const Game& game, const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getYPosition() > from.getYPosition() ? 1 : -1;
	cell.changeYPosition(difference);
	if (to.getYPosition() > from.getYPosition()) {
		while (cell.getYPosition() < to.getYPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Rook can't jump over it!\n");
			cell.changeYPosition(difference);
		}
	}
	else if (to.getYPosition() < from.getYPosition()) {
		while (cell.getYPosition() > to.getYPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Roo can't jump over it!\n");
			cell.changeYPosition(difference);
		}
	}
}

void Rook::checkHorizontalPath(const Game& game, const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getXPosition() > from.getXPosition() ? 1 : -1;
	cell.changeXPosition(difference);
	if (to.getXPosition() > from.getXPosition()) {
		while (cell.getXPosition() < to.getXPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Piece can't jump over it!\n");
			cell.changeXPosition(difference);
		}
	}
	else if (to.getXPosition() < from.getXPosition()) {
		while (cell.getXPosition() > to.getXPosition()) {
			if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Piece can't jump over it!\n");
			cell.changeXPosition(difference);
		}
	}

}