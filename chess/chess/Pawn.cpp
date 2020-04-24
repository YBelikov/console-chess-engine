#include "Pawn.h"
#include <stdexcept>
#include <cmath>
#include "Board.h"

using std::logic_error;

bool Pawn::canMove(Board& board, const Position& from, const Position& to) {

	if (pow(from.getXPosition() - to.getXPosition(), 2) + pow(from.getYPosition() - to.getYPosition(), 2) > 2) {
		throw logic_error("You can't move the pawn so far\n");
	}
	if (abs(from.getYPosition() - to.getYPosition()) == 1 && abs(from.getXPosition() - to.getXPosition()) != 0) {
		throw logic_error("You can't simply move pawn on Y coordinates\n");
	}
	if (!board.getCell(to).isEmpty()) {
		if (board.getCell(to).getPiece().getColorOfPiece() == board.getCell(from).getPiece().getColorOfPiece()) {
			throw logic_error("The cell occupied by piece of your color\n");
		}
		if (board.getCell(from).getPiece().getColorOfPiece() == Color::Black && from.getYPosition() == 1 && abs(from.getYPosition() - to.getYPosition()) == 2 && abs(from.getXPosition() - to.getXPosition()) == 0) {
			return true;
		}
		if (board.getCell(from).getPiece().getColorOfPiece() == Color::White && from.getYPosition() == board.size() - 2 && abs(from.getYPosition() - to.getYPosition()) == 2 && abs(from.getXPosition() - to.getXPosition()) == 0) {
			return true;
		}
	}
	return true;
}