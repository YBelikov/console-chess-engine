#pragma once
#include "Piece.h"

class Queen : public Piece {
	Queen() = default;
	~Queen() = default;
	Queen(Color);
};