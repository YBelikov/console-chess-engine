#pragma once
#include "FigureType.h"

class Piece {
protected:
	FigureType type;
	Color color;
	bool isKilled;
public:
	Piece(FigureType type_, Color color_, bool isKilled_ = false) : type(type_), color(color_), isKilled(isKilled_) {}
	virtual ~Piece() {}
};