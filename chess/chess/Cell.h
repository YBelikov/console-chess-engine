#pragma once
#include "Position.h"
#include <memory>
#include "Piece.h"
#include <iostream>


class Cell {
private:
	Position position;
	std::unique_ptr<Piece> piece;

public:
	Cell() = default;
	Cell(Position, std::unique_ptr<Piece>);
	Cell(Position);
	void setPiece(std::unique_ptr<Piece>);
	Piece& getPiece();
	std::unique_ptr<Piece> releasePiece() {	return std::move(piece); }
	Position getPosition() const { return position; }
	bool isEmpty();
};