#pragma once

#include "Board.h"
#include "Display.h"

class Game {
public:
	Game();
	void start();
	void restart();
	void processMoveCommand();
	void makePromotionForPawnAtPosition(const Position&, const Position&);
	Board& getBoard() const { return *board; }
private:
	std::unique_ptr<Board> board;
	Display displayer;
	void initializeBoard();
	void checkMove(const Position&, const Position&);
	void makeMove(const Position&, const Position&);
	void checkBetweenCells(const Position&, const Position&);
	void checkDoesNextCellOcupiedByPieceOfSameColor(const Position&, const Position&);
};