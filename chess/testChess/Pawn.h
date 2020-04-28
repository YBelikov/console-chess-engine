#pragma once
#include "Piece.h"
#include <vector>

class Pawn : public Piece {
private:
	bool checkWhiteDoubleMove(Game&, const Position&, const Position&);
	bool checkBlackDoubleMove(Game&, const Position&, const Position&);
public:
	Pawn() = default;
	~Pawn() = default;
	Pawn(Color col) : Piece(PieceType::Pawn, col) {}
	bool canMove(Game&, const Position&, const Position&) override;
	bool checkDoubleMove(Game&, const Position&, const Position&);
	bool checkForCapturing(Game&, const Position&, const Position&);
	void checkForPromotion(Game&, const Position&, const Position&);
	bool checkForEnpassant(Game&, const Position&, const Position&, std::pair<Position, Position>&);
};