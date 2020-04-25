#include "Pawn.h"
#include <stdexcept>
#include <cmath>
#include "Game.h"

using std::logic_error;

void Pawn::canMove(Game& game, const Position& from, const Position& to) {
	if (from.getXPosition() == to.getXPosition()) {
		if ((color == Color::White && to.getYPosition() == from.getYPosition() - 1) ||
			(color == Color::Black && to.getYPosition() == from.getYPosition() + 1)) {
			return;
		}
		else if ((color == Color::White && to.getYPosition() == from.getYPosition() - 2) ||
			(color == Color::Black && to.getYPosition() == from.getYPosition() + 2) ) {
			checkDoubleMove(game, from, to);
		}
		else {
			throw logic_error("Pawn can't make this move\n");
		}
	}
	else if(abs(to.getYPosition() - from.getYPosition()) == 1) {
		checkForCapturing(game, from, to);
	}
	else {
		throw logic_error("Pawn can't move simply by row\n");
	}
	
}

void Pawn::checkDoubleMove(Game& game, const Position& from, const Position& to) {
	if (color == Color::White) {
		checkWhiteDoubleMove(game, from, to);
	}
	else {
		checkBlackDoubleMove(game, from, to);
	}
}

void Pawn::checkWhiteDoubleMove(Game& game, const Position& from, const Position& to) {
	if (!(game.getBoard().getCell(Position(to.getYPosition() + 1, to.getXPosition())).isEmpty() && game.getBoard().getCell(Position(to.getYPosition(), to.getXPosition())).isEmpty() &&
		(from.getYPosition() == 6))) {
		throw logic_error("Pawn can't make double move, it's not on origin row\n");
	}
}

void Pawn::checkBlackDoubleMove(Game& game, const Position& from, const Position& to) {
	if (!(game.getBoard().getCell(Position(to.getYPosition() - 1, to.getXPosition())).isEmpty() && game.getBoard().getCell(Position(to.getYPosition(), to.getXPosition())).isEmpty() &&
		(from.getYPosition() == 1))) {
		throw logic_error("Pawn can't make double move, it's not on origin row\n");
	}
}

void Pawn::checkForCapturing(Game& game, const Position& from, const Position& to) {
	if ((color == Color::White && to.getYPosition() == from.getYPosition() - 1) ||
		(color == Color::Black && to.getYPosition() == from.getYPosition() + 1)) {
		if (game.getBoard().getCell(to).isEmpty()) {
			throw logic_error("Pawn can't move on diagonals\n");
		}
	}
}

void Pawn::checkForPromotion(Game& game, Board& board, const Position& from, const Position& to) {
	if ((color == Color::White && to.getYPosition() == 0) || (color == Color::Black && to.getYPosition() == board.size() - 1)) {
		game.makePromotionForPawnAtPosition(from, to);
	}
}