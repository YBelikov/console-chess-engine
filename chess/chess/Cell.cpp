#include "Cell.h"
using std::unique_ptr;

Cell::Cell(Position pos, unique_ptr<Piece> p) {
	position = pos;
	piece = std::move(p);
}

unique_ptr<Piece> Cell::getPiece() {
	return std::move(piece);
}

void Cell::setPiece(unique_ptr<Piece> newPiece) {
	piece = std::move(newPiece);
}