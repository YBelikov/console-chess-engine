#include "Pawn.h"
#include <stdexcept>
#include <cmath>
#include "Board.h"

using std::logic_error;

void Pawn::canMove(Board& board, const Position& from, const Position& to) {
	if (from.getXPosition() == to.getXPosition()) {
		if ((color == Color::White && to.getYPosition() == from.getYPosition() - 1) ||
			(color == Color::Black && to.getYPosition() == from.getYPosition() + 1)) {
			return;
		}
		else if ((color == Color::White && to.getYPosition() == from.getYPosition() - 2) ||
			(color == Color::Black && to.getYPosition() == from.getYPosition() + 2) ) {
			checkDoubleMove(board, from, to);
		}
		else {
			throw logic_error("Pawn can't make this move\n");
		}
	}
	else if(abs(to.getYPosition() - from.getYPosition()) == 1) {
		checkForCapturing(board, from, to);
	}
	else {
		throw logic_error("Pawn can't move simply by row\n");
	}
	
}

void Pawn::checkDoubleMove(Board& board, const Position& from, const Position& to) {
	if (color == Color::White) {
		checkWhiteDoubleMove(board, from, to);
	}
	else {
		checkBlackDoubleMove(board, from, to);
	}
}

void Pawn::checkWhiteDoubleMove(Board& board, const Position& from, const Position& to) {
	if (!(board.getCell(Position(to.getYPosition() + 1, to.getXPosition())).isEmpty() && board.getCell(Position(to.getYPosition(), to.getXPosition())).isEmpty() &&
		(from.getYPosition() == 6))) {
		throw logic_error("Pawn can't make double move, it's not on origin row\n");
	}
}

void Pawn::checkBlackDoubleMove(Board& board, const Position& from, const Position& to) {
	if (!(board.getCell(Position(to.getYPosition() - 1, to.getXPosition())).isEmpty() && board.getCell(Position(to.getYPosition(), to.getXPosition())).isEmpty() &&
		(from.getYPosition() == 1))) {
		throw logic_error("Pawn can't make double move, it's not on origin row\n");
	}
}

void Pawn::checkForCapturing(Board& board, const Position& from, const Position& to) {
	if ((color == Color::White && to.getYPosition() == from.getYPosition() - 1) ||
		(color == Color::Black && to.getYPosition() == from.getYPosition() + 1)) {
		if (board.getCell(to).isEmpty()) {
			throw logic_error("Pawn can't move on diagonals\n");
		}
	}
}