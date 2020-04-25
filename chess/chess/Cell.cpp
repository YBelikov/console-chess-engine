#include "Cell.h"
using std::unique_ptr;

Cell::Cell(Position pos, unique_ptr<Piece> p) {
	position = pos;
	piece = std::move(p);
}

Piece& Cell::getPiece() {
	return *piece;
}

void Cell::setPiece(unique_ptr<Piece> newPiece) {
	std::cout << "set piece\n";
	piece = std::move(newPiece);
}

bool Cell::isEmpty() {
	if (!piece) return true;
	return false;
}