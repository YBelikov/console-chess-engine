#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen() = default;
	~Queen() = default;
	Queen(Color);
};