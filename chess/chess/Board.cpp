#include "Board.h"
#include "Position.h"
#include "Color.h"

Board::Board(int size) {
	pieces.resize(size);
	for (auto& pieceRow : pieces) {
		pieceRow.resize(size);
	}
}

void Board::intitalize() {
	createWhitePawns();
	createWhiteHeavyPieces();
	createBlackPawns();
	createBlackHeavyPieces();
}

void Board::createWhitePawns() {
	for (int i = 0; i < pieces.size(); ++i) {
		pieces[pieces.size() - 2][i] = std::make_shared<Pawn>(Position(pieces.size() - 2, i), Color::White);
	}
}


void Board::createWhiteHeavyPieces() {
	createWhiteRooks();
	createWhiteKnights();
	createWhiteBishops();
	createWhiteKing();
	createWhiteQueen();
}

void Board::createWhiteRooks() {
	pieces[pieces.size() - 1][0] = std::make_shared<Rook>(Position(pieces.size() - 1, 0), Color::White);
	pieces[pieces.size() - 1][pieces.size() - 1] = std::make_shared<Rook>(Position(pieces.size() - 1, pieces.size() - 1), Color::White);
}

void Board::createWhiteKnights() {
	pieces[pieces.size() - 1][1] = std::make_shared<Knight>(Position(pieces.size() - 1, 1), Color::White);
	pieces[pieces.size() - 1][pieces.size() - 2] = std::make_shared<Knight>(Position(pieces.size() - 1, pieces.size() - 2), Color::White);
}

void Board::createWhiteBishops() {
	pieces[pieces.size() - 1][2] = std::make_shared<Bishop>(Position(pieces.size() - 1, 2), Color::White);
	pieces[pieces.size() - 1][pieces.size() - 3] = std::make_shared<Bishop>(Position(pieces.size() - 1, pieces.size() - 3), Color::White);
}

void Board::createWhiteQueen() {
	pieces[pieces.size() - 1][3] = std::make_shared<Queen>(Position(pieces.size() - 1, 3), Color::White);
}

void Board::createWhiteKing() {
	pieces[pieces.size() - 1][4] = std::make_shared<King>(Position(pieces.size() - 1, 4), Color::White);
}



void Board::createBlackPawns() {
	for (int i = 0; i < pieces.size(); ++i) {
		pieces[1][i] = std::make_shared<Pawn>(Position(0, i), Color::Black);
	}
}

void Board::createBlackHeavyPieces() {
	createBlackRooks();
	createBlackKnights();
	createBlackBishops();
	createBlackKing();
	createBlackQueen();
}
void Board::createBlackRooks() {
	pieces[0][0] = std::make_shared<Rook>(Position(0, 0), Color::Black);
	pieces[0][pieces.size() - 1] = std::make_shared<Rook>(Position(0, pieces.size() - 1), Color::Black);
}

void Board::createBlackKnights() {
	pieces[0][1] = std::make_shared<Knight>(Position(0, 1), Color::Black);
	pieces[0][pieces.size() - 2] = std::make_shared<Knight>(Position(0, pieces.size() - 2), Color::Black);
}

void Board::createBlackBishops() {
	pieces[0][2] = std::make_shared<Bishop>(Position(0, 2), Color::Black);
	pieces[0][pieces.size() - 3] = std::make_shared<Bishop>(Position(0, pieces.size() - 3), Color::Black);
}

void Board::createBlackQueen() {
	pieces[0][3] = std::make_shared<Queen>(Position(0, 3), Color::Black);
}

void Board::createBlackKing() {
	pieces[0][4] = std::make_shared<King>(Position(0, 4), Color::Black);
}






