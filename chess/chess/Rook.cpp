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
	do {
		if (to.getYPosition() > from.getYPosition()) {
			cell.changeYPosition(1);
		}
		else if (to.getYPosition() < from.getYPosition()) {
			cell.changeYPosition(-1);
		}
		if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on vertical path! Rook can't jump over it!\n");
	} while (cell.getYPosition() < to.getYPosition());
}

void Rook::checkHorizontalPath(const Game& game, const Position& from, const Position& to) {
	Position cell = from;
	do {
		if (to.getXPosition() > from.getXPosition()) {
			cell.changeXPosition(1);
		}
		else if (to.getXPosition() < from.getXPosition()) {
			cell.changeXPosition(-1);
		}
		if (!game.getBoard().getCell(cell).isEmpty()) throw std::logic_error("There is another piece on horizontal path! Rook can't jump over it!\n");
	} while (cell.getXPosition() < to.getXPosition());

}