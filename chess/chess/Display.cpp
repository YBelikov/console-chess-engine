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

void Display::show(Board& board, std::ostream& out) {
	for (auto& row : board) {
		for (auto& cell : row) {
			if (!cell.isEmpty()) {
				out << colorMap[cell.getPiece().getColorOfPiece()];
				out << piecesTypesMap[cell.getPiece().getPieceType()];
			}
			else {
				out << "  ";
			}
		}
		out << '\n';
	}
}

void Display::display(Board& board, std::ostream& out) {

	out << "		Black							  \n\n";
	out << "   A     B     C     D     E     F     G     H\n\n";
	
	for (int i = 0; i < board.size(); ++i) {
		if ((i+1) % 2 == 0) {
			displayRow(board, i, blackSquare, whiteSquare, out);
		}
		else {
			displayRow(board, i, whiteSquare, blackSquare, out);
		}
	}

	out << '\n';
	out << "   A     B     C     D     E     F     G     H\n\n";
	out << "		White								\n";
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
				}
				else {
					out << char(firstColor);
				}
			}

			for (int subcolumn = 0; subcolumn < CELL; ++subcolumn) {
				if (subline == 1 && subcolumn == 2) {
					if (board.getCell(Position(row, pair * 2 + 1)).isEmpty()) {
						out << char(nextColor);
					}
					else {
						out << colorMap[board.getCell(Position(row, pair * 2 + 1)).getPiece().getColorOfPiece()];
						out << piecesTypesMap[board.getCell(Position(row, pair * 2 + 1)).getPiece().getPieceType()];
						++subcolumn;
					}
				}
				else {
					out << char(nextColor);
				}
			}
		}
		if (subline == 1)
		{
			out << "   " << board.size() - row ;
		}

		out << '\n';

	}
}