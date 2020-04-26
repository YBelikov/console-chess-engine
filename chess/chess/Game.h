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
	bool doesKingInCheck();
	Board& getBoard() const { return *board; }
	std::pair<Position, Position> getLastMoveFromStory() const;
	bool checkDiagonalPath(const Position&, const Position&);

private:

	std::unique_ptr<Board> board;
	std::vector<std::pair<Position, Position>> movesStory;
	Display displayer;
	Color turnColor;
	void initializeBoard();
	void checkMove(const Position&, const Position&);
	void makeMove(const Position&, const Position&);
	void checkBetweenCells(const Position&, const Position&);
	void checkDoesNextCellOcupiedByPieceOfSameColor(const Position&, const Position&);
	void addMoveToStory(Position&, Position&);
	
	bool checkDiagonalInSomeDirection(const Position&, const Position&, int, int);

	Position findKingPosition(Color&);
	bool doesCellUnderAttack(const Position&);
	
	bool checkHorizontalAttackers(const Position&);
	bool checkVerticalAttackers(const Position&);
	bool checkDiagonalAttackers(const Position&);
	bool checkLShapedAttackers(const Position&);
	bool checkHorizontalEnemies(const Position&, int);
	bool checkVerticalEnemies(const Position&, int);
	bool checkDiagonalEnemies(const Position&, int, int);

};