#include "Pawn.h"
#include <stdexcept>
#include <cmath>
#include "Game.h"

using std::logic_error;

bool Pawn::canMove(Game& game, const Position& from, const Position& to) {
	if (from.getXPosition() == to.getXPosition()) {
		if ((color == Color::White && to.getYPosition() == from.getYPosition() - 1) ||
			(color == Color::Black && to.getYPosition() == from.getYPosition() + 1)) {
			return true;
		}
		else if ((color == Color::White && to.getYPosition() == from.getYPosition() - 2) ||
			(color == Color::Black && to.getYPosition() == from.getYPosition() + 2) ) {
			return checkDoubleMove(game, from, to);
		}
		else {
			return false;
		}
	}
	else if (color == Color::White && from.getYPosition() == 3 && to.getYPosition() == 2 && abs(from.getXPosition() - to.getXPosition()) == 1 ||
		color == Color::Black && from.getYPosition() == 4 && to.getYPosition() == 5 && abs(from.getXPosition() - to.getXPosition()) == 1) {
		auto lastMove = game.getLastMoveFromStory();
		if (!checkForEnpassant(game, from, to, lastMove)) return false;
		game.getBoard().getCell(lastMove.second).releasePiece();
	}
	else if(abs(to.getYPosition() - from.getYPosition()) == 1) {
		return checkForCapturing(game, from, to);
	}
	else {
		return false;
	}
	
}

bool Pawn::checkDoubleMove(Game& game, const Position& from, const Position& to) {
	if (color == Color::White) {
		return checkWhiteDoubleMove(game, from, to);
	}
	else {
		return checkBlackDoubleMove(game, from, to);
	}
}

bool Pawn::checkWhiteDoubleMove(Game& game, const Position& from, const Position& to) {
	if (!(game.getBoard().getCell(Position(to.getYPosition() + 1, to.getXPosition())).isEmpty() && game.getBoard().getCell(Position(to.getYPosition(), to.getXPosition())).isEmpty() &&
		(from.getYPosition() == 6))) {
		return false;
	}
	return true;
}

bool Pawn::checkBlackDoubleMove(Game& game, const Position& from, const Position& to) {
	if (!(game.getBoard().getCell(Position(to.getYPosition() - 1, to.getXPosition())).isEmpty() && game.getBoard().getCell(Position(to.getYPosition(), to.getXPosition())).isEmpty() &&
		(from.getYPosition() == 1))) {
		return false;
	}
	return true;
}

bool Pawn::checkForCapturing(Game& game, const Position& from, const Position& to) {
	if ((color == Color::White && to.getYPosition() == from.getYPosition() - 1) ||
		(color == Color::Black && to.getYPosition() == from.getYPosition() + 1)) {
		if (game.getBoard().getCell(to).isEmpty()) {
			return false;
		}
	}
	return true;
}

void Pawn::checkForPromotion(Game& game, const Position& from, const Position& to) {
	if ((color == Color::White && to.getYPosition() == 0) || (color == Color::Black && to.getYPosition() == game.getBoard().size() - 1)) {
		game.makePromotionForPawnAtPosition(from, to);
	}
}

bool Pawn::checkForEnpassant(Game& game, const Position& from, const Position& to, std::pair<Position, Position>& lastMove) {
	auto lastPosition = lastMove.second;
	if (game.getBoard().getCell(lastPosition).getPiece().getPieceType() != PieceType::Pawn) return false;
	if (!(abs(lastMove.first.getYPosition() - lastMove.second.getYPosition()) == 2 && abs(from.getXPosition() - lastPosition.getXPosition()) == 1))
		return false;
}