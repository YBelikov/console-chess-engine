#include "King.h"
#include <cmath>
#include "Game.h"
#include <stdexcept>

King::King(Color col) : Piece(PieceType::King, col){}

bool King::canMove(Game& game, const Position& from, const Position& to) {
	if (((abs(from.getXPosition() - to.getXPosition()) == 1 && from.getYPosition() == to.getYPosition()) ||
		abs(from.getYPosition() - to.getYPosition()) == 1 && from.getXPosition() == to.getXPosition() ||
		(abs(from.getYPosition() - to.getYPosition()) == 1 && abs(from.getXPosition() - to.getXPosition()) == 1))) {
		return true;
	}
	else if (to.getYPosition() == from.getYPosition() && abs(to.getXPosition() - from.getXPosition()) == 2) {
		
		if (game.doesKingInCheck()) return false;
		if (to.getXPosition() > from.getXPosition()) {
			if (game.doesCastlingApplied(Side::KingSide)) return false;
			if (game.checkHorizontalPath(from, Position(to.getYPosition(), game.getBoard().size() - 1))) return false;
			if (game.doesCellUnderAttack(Position(from.getYPosition(), from.getXPosition() + 1), game.getCurrentTurn())) return false;
			return true;
		}
		else {
			if (game.doesCastlingApplied(Side::QueenSide)) return false;
			if (game.checkHorizontalPath(from, Position(to.getYPosition(), 0))) return false;
			if (game.doesCellUnderAttack(Position(from.getYPosition(), from.getXPosition() - 1), game.getCurrentTurn())) return false;
		}
		game.applyCastling(from, to);
		game.disallowCastling();
		return true;
	}
	else {
		return false;
	}
	
}