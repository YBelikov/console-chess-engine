#include "Display.h"

Display::Display() {
	
	initializePiecesTypeMap();
	inititalizeColorMap();
}

void Display::initializePiecesTypeMap() {
	piecesTypesMap[PieceType::Pawn] = "P";
	piecesTypesMap[PieceType::Rook] = "R";
	piecesTypesMap[PieceType::Knight] = "N";
	piecesTypesMap[PieceType::Bishop] = "B";
	piecesTypesMap[PieceType::Queen] = "Q";
	piecesTypesMap[PieceType::King] = "K";

}

void Display::inititalizeColorMap() {
	colorMap[Color::Black] = "B";
	colorMap[Color::White] = "W";
}


void Display::display(Board& board, std::ostream& out) {
	out << "A	B	C	D	E	F	G	H\n";
	out << "|----|----|----|----|----|----|----|----|\n";
	int i{};
	for (auto& row : board) {
		out << board.size() - i << "|";
		for (auto& cell : row) {
			out << colorMap[cell.getPiece().getColorOfPiece()] << piecesTypesMap[cell.getPiece().getPieceType()] << "|";
		}
		out << '\n';
	}
	out << "|----|----|----|----|----|----|----|----|\n";
}