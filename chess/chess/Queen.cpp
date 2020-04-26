#include "Queen.h"
#include "Game.h"

#include <cmath>
#include <stdexcept>

Queen::Queen(Color col) : Piece(PieceType::Queen, col) {}

void Queen::canMove(Game& game, const Position& from, const Position& to) {
	try {
		if (abs(to.getXPosition() - from.getXPosition()) == abs(to.getYPosition() - from.getYPosition())) {
			if(game.checkDiagonalPath(from, to)) throw std::logic_error("There is another piece on diagonal path! Queen can't jump over it!\n");
		}else if(from.getXPosition() == to.getXPosition() && from.getYPosition() != to.getYPosition()) {
			if(game.checkVerticalPath(from, to)) throw std::logic_error("There is another piece on vertical path! Queen can't jump over it!\n");;
		}
		else if (from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			if(game.checkHorizontalPath(from, to))  throw std::logic_error("There is another piece on horizontal path! Queen can't jump over it!\n");
		}
		else {
			throw std::logic_error("Queen can't make this move!\n");
		}
	}
	catch (std::logic_error&) {
		throw;
	}
}
