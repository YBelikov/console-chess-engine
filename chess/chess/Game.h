#pragma once

#include "Board.h"

class Game {
public:
	Game();
	void start();
	void restart();
private:
	std::unique_ptr<Board> board;
	Display display;
	void initializeBoard();

};