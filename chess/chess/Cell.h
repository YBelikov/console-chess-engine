#pragma once
#include "Position.h"
#include <memory>
#include "Piece.h"

class Cell {
private:
	Position position;
	std::unique_ptr<Piece> piece;

public:
	Cell() = default;
	Cell(Position, std::unique_ptr<Piece>);
	void setPiece(std::unique_ptr<Piece>);
	Piece& getPiece();
	bool isEmpty();
};