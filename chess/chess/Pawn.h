#pragma once
#include "Piece.h"
#include <vector>

class Pawn : public Piece {
private:
	void checkWhiteDoubleMove(Game&, const Position&, const Position&);
	void checkBlackDoubleMove(Game&, const Position&, const Position&);
public:
	Pawn() = default;
	~Pawn() = default;
	Pawn(Color col) : Piece(PieceType::Pawn, col) {}
	void canMove(Game&, const Position&, const Position&) override;
	void checkDoubleMove(Game&, const Position&, const Position&);
	void checkForCapturing(Game&, const Position&, const Position&);
	void checkForPromotion(Game&, Board&, const Position&, const Position&);
};