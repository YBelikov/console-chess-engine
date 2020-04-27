#pragma once
#include <vector>
#include "Piece.h"
#include "Cell.h"
#include <memory>

class Board {
public:
	void intitalize();
	Board() = default;
	explicit Board(int);
	auto begin() { return std::begin(pieces); }
	auto end() { return std::end(pieces); }
	auto cbegin() { return std::cbegin(pieces); }
	auto cend() { return std::cend(pieces); }
	int size() const noexcept { return pieces.size(); }
	Cell& getCell(const Position& pos) { return pieces[pos.getYPosition()][pos.getXPosition()]; }
	void setNewPiece(char, const Position&, const Color&);
	void clear();
private:
	void createWhitePawns();
	void createWhiteHeavyPieces();
	void createCellsWithoutPieces();
	void createBlackPawns();
	void createBlackHeavyPieces();

	void createWhiteRooks();
	void createWhiteKnights();
	void createWhiteBishops();
	void createWhiteKing();
	void createWhiteQueen();

	void createBlackRooks();
	void createBlackKnights();
	void createBlackBishops();
	void createBlackKing();
	void createBlackQueen();

	

	std::vector<std::vector<Cell>> pieces;
};