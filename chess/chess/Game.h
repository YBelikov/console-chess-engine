#pragma once

#include "Board.h"
#include "Display.h"

class Game {
public:
	Game();
	void start();
	void restart();
	void processMoveCommand();
private:
	std::unique_ptr<Board> board;
	Display displayer;
	void initializeBoard();
	void checkMove(const Position&, const Position&);
	void makeMove(const Position&, const Position&);

};