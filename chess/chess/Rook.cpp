#include "Rook.h"
#include "Game.h"
#include <stdexcept>

Rook::Rook(Color col) : Piece(PieceType::Rook, col) {}

bool Rook::canMove(Game& game, const Position& from, const Position& to) {
		if (from.getXPosition() == to.getXPosition() && from.getYPosition() != to.getYPosition()) {
			if (game.checkVerticalPath(from, to)) return false;
			if (from.getXPosition() == 0) {
				game.disallowCastlingForOneSide(Side::QueenSide);
				return true;
			}
			else if (from.getXPosition() == game.getBoard().size() - 1) {
				game.disallowCastlingForOneSide(Side::KingSide);
				return true;
			}
		}
		else if (from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			if (game.checkHorizontalPath(from, to)) return false;
			if (from.getXPosition() == 0) {
				game.disallowCastlingForOneSide(Side::QueenSide);
				return true;
			}
			else if (from.getXPosition() == game.getBoard().size() - 1) {
				game.disallowCastlingForOneSide(Side::KingSide);
				return true;
			}
		}
		else return false;	
}
