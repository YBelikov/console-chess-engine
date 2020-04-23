#pragma once

#include "Board.h"

class Game {
private:
	Board board;
	void initializeBoard();

public:
	void start();
	void restart();
};