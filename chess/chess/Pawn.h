#pragma once
#include "Piece.h"
#include <vector>

class Pawn : public Piece {
private:
	void checkWhiteDoubleMove(Board&, const Position&, const Position&);
	void checkBlackDoubleMove(Board&, const Position&, const Position&);
public:
	Pawn() = default;
	~Pawn() = default;
	Pawn(Color col) : Piece(PieceType::Pawn, col) {}
	void canMove(Board&, const Position&, const Position&) override;
	void checkDoubleMove(Board&, const Position&, const Position&);
	void checkForCapturing(Board&, const Position&, const Position&);
};