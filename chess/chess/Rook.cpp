#include "Rook.h"
#include "Game.h"
#include <stdexcept>

Rook::Rook(Color col) : Piece(PieceType::Rook, col) {}

void Rook::canMove(Game& game, const Position& from, const Position& to) {
	
	try {
		if (from.getXPosition() == to.getXPosition() && from.getYPosition() != to.getYPosition()) {
			if(game.checkVerticalPath(from, to)) throw std::logic_error("There is another piece on vertical path! Rook can't jump over it!\n");
			if (from.getXPosition() == 0) game.disallowCastlingForOneSide(Side::QueenSide);
			else if (from.getXPosition() == game.getBoard().size() - 1) game.disallowCastlingForOneSide(Side::KingSide);
		}
		else if (from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			if (game.checkHorizontalPath(from, to)) throw std::logic_error("There is another piece on horizontal path! Rook can't jump over it!\n");
			if (from.getXPosition() == 0) game.disallowCastlingForOneSide(Side::QueenSide);
			else if (from.getXPosition() == game.getBoard().size() - 1) game.disallowCastlingForOneSide(Side::KingSide);
		}
		else throw std::logic_error("Rook can't move like this!\n");
		
	}
	catch (std::logic_error&) {
		throw;
	}
}
