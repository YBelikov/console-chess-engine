#pragma once

#include "Board.h"
#include "Display.h"
#include "Writer.h"
#include <vector>

enum class Side { QueenSide, KingSide };
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
	Color getCurrentTurn() const { return turnColor; }
	bool checkDiagonalPath(const Position&, const Position&);
	bool checkVerticalPath(const Position&, const Position&);
	bool checkHorizontalPath(const Position&, const Position&);
	bool doesCellUnderAttack(const Position&);
	bool doesCastlingApplied(Side side);
	void disallowCastling();
	void disallowCastlingForOneSide(Side side);
	void applyCastling(const Position&, const Position&);
	
private:

	std::unique_ptr<Board> board;
	std::vector<std::pair<Position, Position>> movesStory;
	std::vector<Position> attackersPositions;
	int numberOfAttackers;

	std::unique_ptr<Writer> writer;
	Display displayer;
	Color turnColor;
	std::map<Color, bool> kingSideCastlingsApplied;
	std::map<Color, bool> queenSideCastlingsApplied;
	bool gameStopped;
	bool gameSaved;
	int turnCounter;

	void initializeBoard();
	void checkMove(const Position&, const Position&);
	void makeMove(const Position&, const Position&);
	void checkBetweenCells(const Position&, const Position&);
	void checkDoesNextCellOcupiedByPieceOfSameColor(const Position&, const Position&);
	void addMoveToStory(Position&, Position&);
	void createCastlingsTable();

	bool wouldKingBeInCheck(const Position&, const Position&);

	bool checkDiagonalInSomeDirection(const Position&, const Position&, int, int);
	
	Position findKingPosition(Color&);

	bool checkHorizontalAttackers(const Position&);
	bool checkVerticalAttackers(const Position&);
	bool checkDiagonalAttackers(const Position&);
	bool checkLShapedAttackers(const Position&);
	bool checkHorizontalEnemies(const Position&, int);
	bool checkVerticalEnemies(const Position&, int);
	bool checkDiagonalEnemies(const Position&, int, int);

	bool checkMate();
	void showWinningMessage();
	void showMessageAboutCheck();

	void processSaveCommand();
	void processRestartCommand();
};