#pragma once
#include <vector>
#include "Piece.h"
#include <memory>

class Board {
public:
	void intitalize();
	Board() = default;
	explicit Board(int);
private:
	void createWhitePawns();
	void createWhiteHeavyPieces();
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

	std::vector<std::vector<std::shared_ptr<Piece>>> pieces;
};