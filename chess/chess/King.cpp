#include "King.h"
#include <cmath>
#include "Game.h"
#include <stdexcept>

King::King(Color col) : Piece(PieceType::King, col){}

void King::canMove(Game& game, const Position& from, const Position& to) {
	if (((abs(from.getXPosition() - to.getXPosition()) == 1 && from.getYPosition() == to.getYPosition()) ||
		abs(from.getYPosition() - to.getYPosition()) == 1 && from.getXPosition() == to.getXPosition() ||
		(abs(from.getYPosition() - to.getYPosition()) == 1 && abs(from.getXPosition() - to.getXPosition()) == 1))) {
		return;
	}
	else if (to.getYPosition() == from.getYPosition() && abs(to.getXPosition() - from.getXPosition()) == 2) {
		
		if (game.doesKingInCheck()) throw std::logic_error("King can make castling unless it in check!\n");
		if (to.getXPosition() > from.getXPosition()) {
			if (game.doesCastlingApplied(Side::KingSide)) throw std::logic_error("Castling is not allowed!\n");
			if (game.checkHorizontalPath(from, Position(to.getYPosition(), game.getBoard().size() - 1))) throw std::logic_error("Can't apply castling! There is a piece between rook and king!\n");
			if (game.doesCellUnderAttack(Position(from.getYPosition(), from.getXPosition() + 1))) throw std::logic_error("Cell near to king is under attack! Can't apply castling!\n");

		}
		else {
			if (game.doesCastlingApplied(Side::QueenSide)) throw std::logic_error("Castling is not allowed!\n");
			if (game.checkHorizontalPath(from, Position(to.getYPosition(), 0))) throw std::logic_error("Can't apply castling! There is a piece between rook and king!\n");
			if (game.doesCellUnderAttack(Position(from.getYPosition(), from.getXPosition() - 1))) throw std::logic_error("Cell near to king is under attack! Can't apply castling!\n");
		}
		game.applyCastling(from, to);
		game.disallowCastling();
	}
	else {
		throw std::logic_error("King can't make this move!\n");
	}
	
}