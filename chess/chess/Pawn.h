#pragma once
#include "Piece.h"
#include <vector>

class Pawn : public Piece {
public:
	Pawn() = default;
	~Pawn() = default;
	Pawn(Color col) : Piece(PieceType::Pawn, col) {}
};