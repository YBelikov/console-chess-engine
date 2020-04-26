#include "Game.h"
#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>
#include <memory>

using std::string;
using std::cin;
using std::cout;
using std::regex;
using std::logic_error;

Game::Game() {
	board = std::make_unique<Board>(8);
	writer = std::make_unique<Writer>();
	createCastlingsTable();
	gameStopped = false;
	gameSaved = false;
}


void Game::createCastlingsTable() {
	kingSideCastlingsApplied[Color::White] = false;
	kingSideCastlingsApplied[Color::Black] = false;
	queenSideCastlingsApplied[Color::White] = false;
	queenSideCastlingsApplied[Color::Black] = false;
}


void Game::initializeBoard() {
	board->intitalize();
}

void Game::start() {
	initializeBoard();
	const std::regex allowedCommandsRegex("[qslm]");
	char commandChar;
	int turnCounter{1};
	do {
		if (turnCounter % 2 == 0) turnColor = Color::Black;
		else turnColor = Color::White;
		system("cls");
		displayer.display(*board, cout);
		if (doesKingInCheck()) {
			if (checkMate()) {
				showWinningMessage();
				gameStopped = true;
			}
			else showMessageAboutCheck();
		}
		cout << "Now you can use next options in game: (Q)uit, (S)ave, (L)oad, (M)ove: ";
		cin >> commandChar;
		std::tolower(commandChar);
		if (!std::regex_match(string{ commandChar }, allowedCommandsRegex)) {
			cout << "Wrong option\n";
		}
		else {
			switch (commandChar) {
			case 'm':
				if (!gameStopped) {
					processMoveCommand();
					gameSaved = false;
					break;
				}
				cout << "Game stopped! You can't make moves anymore!\n";
				break;
			case 's':
				processSaveCommand();
				break;
			}
		}
		++turnCounter;
	} while (commandChar != 'q');
	
}

void Game::processMoveCommand() {
	const std::regex moveRegex("[a-h][1-8]-[a-h][1-8]");
	string moveCommand{};
	cin >> moveCommand;
	for (auto& c : moveCommand) {
		std::tolower(c);
	}
	if (!std::regex_match(moveCommand, moveRegex)) {
		cout << "Wrong format of move\n";
	}
	else {
		Position from(board->size() -  (moveCommand[1] - '0'), int(moveCommand[0]) - int('a'));
		Position to(board->size() - (moveCommand[4] - '0'), int(moveCommand[3]) - int('a'));
		try {
			checkMove(from, to);
			makeMove(from, to);
			addMoveToStory(from, to);
			
		}catch(logic_error& ex){
			cout << ex.what();
			processMoveCommand();
		}
	}

}

void Game::checkMove(const Position& from, const Position& to) {
	try {
		if (board->getCell(from).isEmpty()) throw logic_error("The starting cell is empty\n");
		if (board->getCell(from).getPiece().getColorOfPiece() != turnColor) throw logic_error("You're trying to move opponent's piece!\n");
		checkDoesNextCellOcupiedByPieceOfSameColor(from, to);
		board->getCell(from).getPiece().canMove(*this, from, to);
		if (wouldKingBeInCheck(from, to)) throw logic_error("King would be in check after this move! Can't move the piece!\n");
	}
	catch (logic_error & ex) {
		throw;
	}
}

bool Game::checkHorizontalPath(const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getXPosition() > from.getXPosition() ? 1 : -1;
	cell.changeXPosition(difference);
	if (to.getXPosition() > from.getXPosition()) {
		while (cell.getXPosition() < to.getXPosition()) {
			if (!board->getCell(cell).isEmpty()) return true;
			cell.changeXPosition(difference);
		}
	}
	else if (to.getXPosition() < from.getXPosition()) {
		while (cell.getXPosition() > to.getXPosition()) {
			if (!board->getCell(cell).isEmpty()) return true;
			cell.changeXPosition(difference);
		}
	}
	return false;
}

bool Game::checkVerticalPath(const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getYPosition() > from.getYPosition() ? 1 : -1;
	cell.changeYPosition(difference);
	if (to.getYPosition() > from.getYPosition()) {
		while (cell.getYPosition() < to.getYPosition()) {
			if (!board->getCell(cell).isEmpty()) return true;
			cell.changeYPosition(difference);
		}
	}
	else if (to.getYPosition() < from.getYPosition()) {
		while (cell.getYPosition() > to.getYPosition()) {
			if (!board->getCell(cell).isEmpty()) return true;
			cell.changeYPosition(difference);
		}
	}
	return false;
}



bool Game::checkDiagonalPath(const Position& from, const Position& to) {
	if (to.getXPosition() > from.getXPosition() && to.getYPosition() < from.getYPosition()) {
		return checkDiagonalInSomeDirection(from, to, 1, -1); //upper-right diagonal
	}
	else if (to.getXPosition() < from.getXPosition() && to.getYPosition() < from.getYPosition()) {
		return checkDiagonalInSomeDirection(from, to, -1, -1); //upper-left diagonal
	}
	else if (to.getXPosition() < from.getXPosition() && to.getYPosition() > from.getYPosition()) {
		return checkDiagonalInSomeDirection(from, to, -1, 1); //down-left diagonal
	}
	else if (to.getXPosition() > from.getXPosition() && to.getYPosition() > from.getYPosition()) {
		return checkDiagonalInSomeDirection(from, to, 1, 1); // down-right diagonal
	}
}


bool Game::checkDiagonalInSomeDirection(const Position& from, const Position& to, int xOffset, int yOffset) {
	Position current = from;
	current.changeXPosition(xOffset);
	current.changeYPosition(yOffset);
	while (current != to) {
		if (!board->getCell(current).isEmpty()) return true;
		current.changeXPosition(xOffset);
		current.changeYPosition(yOffset);
	}
	return false;
}

void Game::checkBetweenCells(const Position& from, const Position& to) {
	return;
}

void Game::checkDoesNextCellOcupiedByPieceOfSameColor(const Position& from, const Position& to) {
	if (!board->getCell(to).isEmpty()) {
		if (board->getCell(to).getPiece().getColorOfPiece() == board->getCell(from).getPiece().getColorOfPiece()) 
			throw logic_error("Cell occupied by piece of the same color\n");
	}
}


void Game::makeMove(const Position& from, const Position& to) {
	auto ptr = board->getCell(from).releasePiece();
	board->getCell(to).setPiece(std::move(ptr));
}

void Game::makePromotionForPawnAtPosition(const Position& from, const Position& to) {
	std::regex pieceRegex("[qnbr]");
	cout << "Your pawn should be promoted! Choose new figure(Q, N, B, R): ";
	char pieceChar{};
	cin >> pieceChar;
	std::tolower(pieceChar);
	if (!std::regex_match(std::string{ pieceChar }, pieceRegex)) {
		cout << "You can choose only from proposed pieces! Try again!\n";
		makePromotionForPawnAtPosition(from, to);
	}
	Color col = board->getCell(from).getPiece().getColorOfPiece();
	board->getCell(from).releasePiece();
	board->setNewPiece(pieceChar, to, col);
}

void Game::addMoveToStory(Position& from, Position& to) {
	movesStory.push_back(std::make_pair(from, to));
}

std::pair<Position, Position> Game::getLastMoveFromStory() const {
	return movesStory.back();
}

bool Game::doesKingInCheck() {
	Position kingPosition = findKingPosition(turnColor);
	return doesCellUnderAttack(kingPosition);
}

Position Game::findKingPosition(Color& turnColor) {
	for (auto& row : *board) {
		for (auto& cell : row) {
			if (!cell.isEmpty()) {
				if (cell.getPiece().getPieceType() == PieceType::King && turnColor == cell.getPiece().getColorOfPiece())
					return cell.getPosition();
			}
		}
	}
	throw std::logic_error("Something with your king!\n");
}

bool Game::doesCellUnderAttack(const Position& pos) {
	return checkHorizontalAttackers(pos) || checkVerticalAttackers(pos) 
		|| checkDiagonalAttackers(pos) || checkLShapedAttackers(pos);
}

bool Game::checkHorizontalAttackers(const Position& pos) {
	return checkHorizontalEnemies(pos, 1) || checkHorizontalEnemies(pos, -1);
}

bool Game::checkVerticalAttackers(const Position& pos) {
	return checkVerticalEnemies(pos, 1) || checkVerticalEnemies(pos, -1);
}

bool Game::checkDiagonalAttackers(const Position& pos){
	return checkDiagonalEnemies(pos, 1, 1) || checkDiagonalEnemies(pos, -1, 1) 
	|| checkDiagonalEnemies(pos, 1, -1) || checkDiagonalEnemies(pos, -1, -1);
}

bool Game::checkHorizontalEnemies(const Position& start, int xOffset) {
	Position current = start;
	current.changeXPosition(xOffset);
	while (current.getXPosition() < board->size() && current.getXPosition() >= 0) {
		if (!board->getCell(current).isEmpty()) {
			if (board->getCell(current).getPiece().getColorOfPiece() == turnColor) break;
			else {
				if (board->getCell(current).getPiece().getPieceType() == PieceType::Queen ||
					board->getCell(current).getPiece().getPieceType() == PieceType::Rook) {
					return true;
				}
			}
		}
		current.changeXPosition(xOffset);
	}
	return false;
}

bool Game::checkVerticalEnemies(const Position& start, int yOffset) {
	Position current = start; 
	current.changeYPosition(yOffset);
	while (current.getYPosition() < board->size() && current.getYPosition() >= 0) {	
		if (!board->getCell(current).isEmpty()) {
			if (board->getCell(current).getPiece().getColorOfPiece() == turnColor) break;
			else {
				if (board->getCell(current).getPiece().getPieceType() == PieceType::Queen ||
					board->getCell(current).getPiece().getPieceType() == PieceType::Rook) {
					return true;
				}
			}
		}
		current.changeYPosition(yOffset);
	}
	return false;
}

bool Game::checkDiagonalEnemies(const Position& start, int xOffset, int yOffset) {
	Position current = start;
	current.changeXPosition(xOffset);
	current.changeYPosition(yOffset);
	while (current.getXPosition() < board->size() && current.getXPosition() >= 0
		&& current.getYPosition() < board->size() && current.getYPosition() >= 0) {
		if (!board->getCell(current).isEmpty()) {
			if (board->getCell(current).getPiece().getColorOfPiece() == turnColor) break;
			else {
				if (board->getCell(current).getPiece().getPieceType() == PieceType::Bishop ||
					board->getCell(current).getPiece().getPieceType() == PieceType::Queen) {
					return true;
				}
			}
		}
		current.changeXPosition(xOffset);
		current.changeYPosition(yOffset);
	}
	return false;
}

bool Game::checkLShapedAttackers(const Position& pos) {
	std::vector<Position> knightMoves = { Position(1, 2), Position(-1, 2), Position(1, -2), Position(-1, -2),
										Position(2, 1), Position(2, -1), Position(-2, 1), Position(-2, -1) };
	Position possibleEnemyPosition = pos;
	for (auto& move : knightMoves) {
		possibleEnemyPosition.changeXPosition(move.getXPosition());
		possibleEnemyPosition.changeYPosition(move.getYPosition());
		if (possibleEnemyPosition.getXPosition() < board->size() && possibleEnemyPosition.getXPosition() > 0
			&& possibleEnemyPosition.getYPosition() < board->size() && possibleEnemyPosition.getYPosition() > 0) {
			if (!board->getCell(possibleEnemyPosition).isEmpty()) {
				if (board->getCell(possibleEnemyPosition).getPiece().getColorOfPiece() != turnColor
					&& board->getCell(possibleEnemyPosition).getPiece().getPieceType() == PieceType::Knight) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Game::wouldKingBeInCheck(const Position& from, const Position& to) {
	makeMove(from, to);
	if (doesKingInCheck()) {
		makeMove(to, from);
		return true;
	}
	makeMove(to, from);
	return false;
}

bool Game::doesCastlingApplied(Side side) {
	if (side == Side::KingSide) {
		return kingSideCastlingsApplied[turnColor];
	}
	else {
		return queenSideCastlingsApplied[turnColor];
	}
}

void Game::disallowCastling() {
	kingSideCastlingsApplied[turnColor] = true;
	queenSideCastlingsApplied[turnColor] = true;
}

void Game::disallowCastlingForOneSide(Side side) {
	if (side == Side::KingSide) kingSideCastlingsApplied[turnColor] = true;
	else if (side == Side::QueenSide) queenSideCastlingsApplied[turnColor] = true;
}

void Game::applyCastling(const Position& from, const Position& to) {
	if (from.getXPosition() < to.getXPosition()) {
		Position kingSideRookPosition(to.getYPosition(), board->size() - 1);
		makeMove(kingSideRookPosition, Position(to.getYPosition(), to.getXPosition() - 1));
	}
	else {
		Position queenSideRookPosition(to.getYPosition(), 0);
		makeMove(queenSideRookPosition, Position(to.getYPosition(), to.getXPosition() + 1));
	}
}

void Game::showMessageAboutCheck() {
	if (turnColor == Color::White) {
		cout << "White king in check!\n";
	}
	else if (turnColor == Color::Black) {
		cout << "Black king in check!\n";
	}
}

void Game::showWinningMessage() {
	if (turnColor == Color::White) {
		cout << "Checkmate! Black wins!\n";
	}
	else if (turnColor == Color::Black) {
		cout << "Checkmate! White wins!\n";
	}
}

bool Game::checkMate(){
	return false;
}


void Game::processSaveCommand() {
	if (gameSaved) {
		cout << "Game has been already saved!\n";
		return;
	}
	cout << "Now type name of file(without extention) where you would like to save the game: ";
	string fileName{};
	cin >> fileName;
	fileName += ".txt";
	try {
		writer->writeBoardTo(*this, fileName);
		gameSaved = true;
	}
	catch (std::domain_error & er) {
		cout << er.what();
		cout << "Try again!\n";
		processSaveCommand();
	}
}