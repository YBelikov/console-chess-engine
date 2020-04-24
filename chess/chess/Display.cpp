#include "Display.h"

Display::Display() {
	
	initializePiecesTypeMap();
	inititalizeColorMap();
}

void Display::initializePiecesTypeMap() {
	piecesTypesMap[PieceType::Pawn] = 'P';
	piecesTypesMap[PieceType::Rook] = 'R';
	piecesTypesMap[PieceType::Knight] = 'N';
	piecesTypesMap[PieceType::Bishop] = 'B';
	piecesTypesMap[PieceType::Queen] = 'Q';
	piecesTypesMap[PieceType::King] = 'K';

}

void Display::inititalizeColorMap() {
	colorMap[Color::Black] = 'B';
	colorMap[Color::White] = 'W';
}


void Display::display(Board& board, std::ostream& out) {
	out << "		White							  \n\n";
	out << "   A     B     C     D     E     F     G     H\n\n";
	int i{7};
	for (int i = 7; i >= 0; --i) {
		if (i % 2 == 0) {
			displayRow(board, i, blackSquare, whiteSquare, out);
		}
		else {
			displayRow(board, i, whiteSquare, blackSquare, out);
		}
	}

	out << '\n';
	out << "   A     B     C     D     E     F     G     H\n\n";
	out << "		Black								\n";
}

void Display::displayRow(Board& board, int row, int firstColor, int nextColor, std::ostream& out) {
	int CELL = 6;
	for (int subline = 0; subline < CELL / 2; ++subline) {
		
		for (int pair = 0; pair < 4; ++pair) {
			
			for (int subcolumn = 0; subcolumn < CELL; ++subcolumn) {
				
				if (subline == 1 && subcolumn == 2) {
					if (board.getCell(Position(row, pair * 2)).isEmpty()) {
						out << char(firstColor);
					}
					else {
						out << colorMap[board.getCell(Position(row, pair * 2)).getPiece().getColorOfPiece()];
						out << piecesTypesMap[board.getCell(Position(row, pair * 2)).getPiece().getPieceType()];
						++subcolumn;
					}
										//out << (board.getCell(Position(row, pair * 2)).isEmpty() == true ? char(firstColor) : piecesTypesMap[board.getCell(Position(row, pair * 2)).getPiece().getPieceType()]);
				}
				else {
					out << char(firstColor);
				}
			}

			for (int subcolumn = 0; subcolumn < CELL; ++subcolumn) {
				if (subline == 1 && subcolumn == 2) {
					if (board.getCell(Position(row, pair * 2)).isEmpty()) {
						out << char(nextColor);
					}
					else {
						out << colorMap[board.getCell(Position(row, pair * 2)).getPiece().getColorOfPiece()];
						out << piecesTypesMap[board.getCell(Position(row, pair * 2)).getPiece().getPieceType()];
						++subcolumn;
					}
					//	out << (board.getCell(Position(row, pair * 2 + 1)).isEmpty() == true ? char(nextColor) : piecesTypesMap[board.getCell(Position(row, pair * 2 + 1)).getPiece().getPieceType()]);
				}
				else {
					out << char(nextColor);
				}
			}
		}
		if (subline == 1)
		{
			out << "   " << row + 1;
		}

		out << '\n';

	}
}