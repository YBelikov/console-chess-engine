#include "Writer.h"
#include "Game.h"
#include <fstream>
#include <stdexcept>

Writer::Writer() {
	createColorMap();
	createPiecesMap();
}

void Writer::writeBoardTo(Game& game, std::string& str) {
	std::ofstream out(str.c_str());
	if (!out) {
		throw std::domain_error("Can't create a file!\n");
	}
	if (game.getCurrentTurn() == Color::White) out << 1 << '\n';
	else if (game.getCurrentTurn() == Color::Black) out << 2 << '\n';
	for (auto& row : game.getBoard()) {
		for (auto& cell : row) {
			if (!cell.isEmpty()) {
				out << colorMap[cell.getPiece().getColorOfPiece()] << piecesMap[cell.getPiece().getPieceType()]
					<< cell.getPosition().getYPosition() << cell.getPosition().getXPosition() << " ";
			}
		}
		out << '\n';
	}
}

void Writer::createColorMap() {

	colorMap[Color::White] = 'w';
	colorMap[Color::Black] = 'b';
}

void Writer::createPiecesMap() {
	piecesMap[PieceType::Pawn] = 'p';
	piecesMap[PieceType::Rook] = 'r';
	piecesMap[PieceType::Knight] = 'n';
	piecesMap[PieceType::Bishop] = 'b';
	piecesMap[PieceType::Queen] = 'q';
	piecesMap[PieceType::King] = 'k';
}