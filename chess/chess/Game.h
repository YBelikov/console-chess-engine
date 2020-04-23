#pragma once

#include "Board.h"
#include "Display.h"

class Game {
public:
	Game();
	void start();
	void restart();
private:
	std::unique_ptr<Board> board;
	Display displayer;
	void initializeBoard();

};