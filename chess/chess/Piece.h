#pragma once
#include "Position.h"

class Piece {
protected:

	bool isKilled;
public:
	virtual void makeMove(Position);
	virtual bool canBeMovedToPosition(Position);
	virtual ~Piece();
};