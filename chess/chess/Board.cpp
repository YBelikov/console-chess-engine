#include "Board.h"
#include "Position.h"
#include "Color.h"
#include "Rook.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

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
		pieces[pieces.size() - 2][i] = Cell(Position(pieces.size() - 2, i), std::make_unique<Pawn>(Color::White));
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
	pieces[pieces.size() - 1][0] = Cell(Position(pieces.size() - 1, 0), std::make_unique<Rook>(Color::White));
	pieces[pieces.size() - 1][pieces.size() - 1] = Cell(Position(pieces.size() - 1, pieces.size() - 1), std::make_unique<Rook>(Color::White));
}

void Board::createWhiteKnights() {
	pieces[pieces.size() - 1][1] = Cell(Position(pieces.size() - 1, 1), std::make_unique<Knight>(Color::White));
	pieces[pieces.size() - 1][pieces.size() - 2] = Cell(Position(pieces.size() - 1, pieces.size() - 2), std::make_unique<Knight>(Color::White));
}

void Board::createWhiteBishops() {
	pieces[pieces.size() - 1][2] = Cell(Position(pieces.size() - 1, 2), std::make_unique<Bishop>(Color::White));
	pieces[pieces.size() - 1][pieces.size() - 3] = Cell(Position(pieces.size() - 1, pieces.size() - 3), std::make_unique<Bishop>(Color::White));
}

void Board::createWhiteQueen() {
	pieces[pieces.size() - 1][3] = Cell(Position(pieces.size() - 1, 3), std::make_unique<Queen>(Color::White));
}

void Board::createWhiteKing() {
	pieces[pieces.size() - 1][4] = Cell(Position(pieces.size() - 1, 4), std::make_unique<King>(Color::White));
}



void Board::createBlackPawns() {
	for (int i = 0; i < pieces.size(); ++i) {
		pieces[1][i] = Cell(Position(0, i), std::make_unique<Pawn>(Color::Black));
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
	pieces[0][0] = Cell(Position(0, 0), std::make_unique<Rook>(Color::Black));
	pieces[0][pieces.size() - 1] = Cell(Position(0, pieces.size() - 1), std::make_unique<Rook>(Color::Black));
}

void Board::createBlackKnights() {
	pieces[0][1] = Cell(Position(0, 1), std::make_unique<Knight>(Color::Black));
	pieces[0][pieces.size() - 2] = Cell(Position(0, pieces.size() - 2), std::make_unique<Knight>(Color::Black));
}

void Board::createBlackBishops() {
	pieces[0][2] = Cell(Position(0, 2), std::make_unique<Bishop>(Color::Black));
	pieces[0][pieces.size() - 3] = Cell(Position(0, pieces.size() - 3), std::make_unique<Bishop>(Color::Black));
}

void Board::createBlackQueen() {
	pieces[0][3] = Cell(Position(0, 3), std::make_unique<Queen>(Color::Black));
}

void Board::createBlackKing() {
	pieces[0][4] = Cell(Position(0, 4), std::make_unique<King>(Color::Black));
}







