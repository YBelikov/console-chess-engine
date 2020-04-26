#pragma once

#include "Board.h"
#include "Display.h"
#include <vector>

class Game {
public:
	Game();
	void start();
	void restart();
	void processMoveCommand();
	void makePromotionForPawnAtPosition(const Position&, const Position&);
	Board& getBoard() const { return *board; }
	std::pair<Position, Position> getLastMoveFromStory() const;
	

private:
	std::unique_ptr<Board> board;
	std::vector<std::pair<Position, Position>> movesStory;
	Display displayer;

	void initializeBoard();
	void checkMove(const Position&, const Position&);
	void makeMove(const Position&, const Position&);
	void checkBetweenCells(const Position&, const Position&);
	void checkDoesNextCellOcupiedByPieceOfSameColor(const Position&, const Position&);
	void addMoveToStory(Position&, Position&);
	void checkDiagonalInSomeDirection(const Position&, const Position&, int, int);
	
};