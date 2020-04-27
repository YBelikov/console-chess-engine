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
	gameSaved = true;
	numberOfAttackers = 0;
	turnCounter = 1;
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
	const std::regex allowedCommandsRegex("[qslrm]");
	char commandChar;
	
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
		cout << "Now you can use next options in game: (Q)uit, (S)ave, (L)oad, (M)ove, (R)estart: ";
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
					++turnCounter;
					break;
				}
				cout << "Game stopped! You can't make moves anymore!\n";
				break;
			case 's':
				processSaveCommand();
				break;
			case 'r':
				processRestartCommand();
				break;
			case 'l':
				processLoadCommand();
				break;
			}
		}
	} while (commandChar != 'q');
	
}

void Game::processMoveCommand() {
	cout << "Now type move in format a1-b1: ";
	string moveCommand{};
	cin >> moveCommand;
	try {
		validateMoveCommand(moveCommand);
		Position from(board->size() - (moveCommand[1] - '0'), int(moveCommand[0]) - int('a'));
		Position to(board->size() - (moveCommand[4] - '0'), int(moveCommand[3]) - int('a'));
		checkMove(from, to);
		makeMove(from, to);
		addMoveToStory(from, to);
	}
	catch (std::logic_error& er) {
		cout << er.what();
		cout << "Try again!\n";
		processMoveCommand();
	}
	
}

void Game::validateMoveCommand(string& moveCommand) {
	const std::regex moveRegex("[a-h][1-8]-[a-h][1-8]");
	for (auto& c : moveCommand) {
		std::tolower(c);
	}
	if (!std::regex_match(moveCommand, moveRegex)) throw std::logic_error("Wrong format of move!\n");

}

void Game::checkMove(const Position& from, const Position& to) {
	try {
		if (board->getCell(from).isEmpty()) throw logic_error("The starting cell is empty\n");
		if (board->getCell(from).getPiece().getColorOfPiece() != turnColor) throw logic_error("You're trying to move opponent's piece!\n");
		checkDoesNextCellOcupiedByPieceOfSameColor(from, to);
		if (!board->getCell(from).getPiece().canMove(*this, from, to)) throw logic_error("Piece can't make this move!\n");
		else {
			if(!board->getCell(to).isEmpty() && board->getCell(to).getPiece().getPieceType() == PieceType::King) throw logic_error("Piece can't make this move!\n");
		}
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
	return doesCellUnderAttack(kingPosition, turnColor);
}

Position Game::findKingPosition(Color& turnColor) {
	for (int y = 0; y < board->size(); ++y) {
		for (int x = 0; x < board->size(); ++x) {
			if (!board->getCell(Position(y,x)).isEmpty() 
				&& board->getCell(Position(y, x)).getPiece().getPieceType() == PieceType::King 
				&& turnColor == board->getCell(Position(y, x)).getPiece().getColorOfPiece()) {
				return Position(y, x);
			}
		}
	}
	throw std::logic_error("Something wrong with your king!\n");
}

bool Game::doesCellUnderAttack(const Position& pos, Color color) {
	return checkHorizontalAttackers(pos, color) || checkVerticalAttackers(pos, color) 
		|| checkDiagonalAttackers(pos, color) || checkLShapedAttackers(pos, color);
}

bool Game::checkHorizontalAttackers(const Position& pos, Color color) {
	return checkHorizontalEnemies(pos, 1, color) || checkHorizontalEnemies(pos, -1, color);
}

bool Game::checkVerticalAttackers(const Position& pos, Color color) {
	return checkVerticalEnemies(pos, 1, color) || checkVerticalEnemies(pos, -1, color);
}

bool Game::checkDiagonalAttackers(const Position& pos, Color color){
	return checkDiagonalEnemies(pos, 1, 1, color) || checkDiagonalEnemies(pos, -1, 1, color) 
	|| checkDiagonalEnemies(pos, 1, -1, color) || checkDiagonalEnemies(pos, -1, -1, color);
}

bool Game::checkHorizontalEnemies(const Position& start, int xOffset, Color color) {
	Position current = start;
	current.changeXPosition(xOffset);
	while (current.getXPosition() < board->size() && current.getXPosition() >= 0) {
		if (!board->getCell(current).isEmpty()) {
			if (board->getCell(current).getPiece().getColorOfPiece() == color) break;
			else {
				if (board->getCell(current).getPiece().getPieceType() == PieceType::Queen ||
					board->getCell(current).getPiece().getPieceType() == PieceType::Rook) {
					attackersPositions.push_back(Position(current));
					return true;
				}
			}
		}
		current.changeXPosition(xOffset);
	}
	return false;
}

bool Game::checkVerticalEnemies(const Position& start, int yOffset, Color color) {
	Position current = start; 
	current.changeYPosition(yOffset);
	while (current.getYPosition() < board->size() && current.getYPosition() >= 0) {	
		if (!board->getCell(current).isEmpty()) {
			if (board->getCell(current).getPiece().getColorOfPiece() == color) break;
			else {
				if (board->getCell(current).getPiece().getPieceType() == PieceType::Queen ||
					board->getCell(current).getPiece().getPieceType() == PieceType::Rook) {
					attackersPositions.push_back(Position(current));
					return true;
				}
			}
		}
		current.changeYPosition(yOffset);
	}
	return false;
}

bool Game::checkDiagonalEnemies(const Position& start, int xOffset, int yOffset, Color color) {
	Position current = start;
	current.changeXPosition(xOffset);
	current.changeYPosition(yOffset);
	while (current.getXPosition() < board->size() && current.getXPosition() >= 0
		&& current.getYPosition() < board->size() && current.getYPosition() >= 0) {
		if (!board->getCell(current).isEmpty()) {
			if (board->getCell(current).getPiece().getColorOfPiece() == color) break;
			else {
				if (abs(start.getXPosition() - current.getXPosition()) == 1
					&& abs(start.getYPosition() - current.getYPosition()) == 1
					&& board->getCell(current).getPiece().getPieceType() == PieceType::Pawn) {
					attackersPositions.push_back(Position(current));
					return true;
				}
				if (board->getCell(current).getPiece().getPieceType() == PieceType::Bishop ||
					board->getCell(current).getPiece().getPieceType() == PieceType::Queen) {
					attackersPositions.push_back(Position(current));
					return true;
				}
			}
		}
		current.changeXPosition(xOffset);
		current.changeYPosition(yOffset);
	}
	return false;
}

bool Game::checkLShapedAttackers(const Position& pos, Color color) {
	std::vector<Position> knightMoves = { Position(1, 2), Position(-1, 2), Position(1, -2), Position(-1, -2),
										Position(2, 1), Position(2, -1), Position(-2, 1), Position(-2, -1) };
	Position possibleEnemyPosition = pos;
	for (auto& move : knightMoves) {
		possibleEnemyPosition.changeXPosition(move.getXPosition());
		possibleEnemyPosition.changeYPosition(move.getYPosition());
		if (possibleEnemyPosition.getXPosition() < board->size() && possibleEnemyPosition.getXPosition() > 0
			&& possibleEnemyPosition.getYPosition() < board->size() && possibleEnemyPosition.getYPosition() > 0) {
			if (!board->getCell(possibleEnemyPosition).isEmpty()) {
				if (board->getCell(possibleEnemyPosition).getPiece().getColorOfPiece() != color
					&& board->getCell(possibleEnemyPosition).getPiece().getPieceType() == PieceType::Knight) {
					attackersPositions.push_back(Position(possibleEnemyPosition));
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
	std::vector<Position> kingPossibleMoves = { Position(1, -1), Position(1, 1), Position(1, 0), Position(0, 1),
												Position(-1, -1), Position(-1, 1), Position(-1, 0), Position(0, -1) };
	Position currentKingPosition = findKingPosition(turnColor);
	Position testPosition = currentKingPosition;
	for (auto& move : kingPossibleMoves) {
		testPosition.changeXPosition(move.getXPosition());
		testPosition.changeYPosition(move.getYPosition());
		if (testPosition.getXPosition() < 0 || testPosition.getXPosition() > board->size()
			|| testPosition.getYPosition() < 0 || testPosition.getYPosition() > board->size()) continue;
		if (!board->getCell(testPosition).isEmpty()) continue;
		if (!wouldKingBeInCheck(currentKingPosition, testPosition)) return false;
		testPosition = currentKingPosition;
	}
	if (attackersPositions.size() == 1) return doesCellUnderAttack(attackersPositions.front(), getOpponentColor());
	if (!directionCanBeBlocked(currentKingPosition, attackersPositions.front())) return true;

}

Color Game::getOpponentColor() {
	if (turnColor == Color::White) return Color::Black;
	return Color::White;
}

bool Game::directionCanBeBlocked(const Position& from, const Position& to) {
	PieceType type = board->getCell(to).getPiece().getPieceType();
	if (type == PieceType::Knight) return false;
	else if (type == PieceType::Pawn) return false;
	else if (type == PieceType::Rook) {
		if (from.getXPosition() == to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			return doesHorizontalCellsAreReachable(from, to);
		}
		else return doesVerticalCellsAreReachable(from, to);
	}
	else if (type == PieceType::Bishop) {
		return doesDiagonalCellsAreReachable(from, to);
	}
	else if (type == PieceType::Queen) {
		if (from.getXPosition() == to.getXPosition() && from.getYPosition() == to.getYPosition()) {
			return doesHorizontalCellsAreReachable(from, to);
		}
		else if(from.getXPosition() != to.getXPosition() && from.getYPosition() == to.getYPosition())
			return doesVerticalCellsAreReachable(from, to);
		else if (abs(from.getXPosition() - to.getXPosition()) == abs(from.getYPosition() - to.getYPosition())) {
			return doesDiagonalCellsAreReachable(from, to);
		}
	}
	return true;
}


bool Game::doesHorizontalCellsAreReachable(const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getXPosition() > from.getXPosition() ? 1 : -1;
	cell.changeXPosition(difference);
	if (to.getXPosition() > from.getXPosition()) {
		while (cell.getXPosition() < to.getXPosition()) {
			if (!board->getCell(cell).isEmpty() && board->getCell(cell).getPiece().getColorOfPiece() == turnColor) {
				if (board->getCell(cell).getPiece().canMove(*this, board->getCell(cell).getPosition(), cell)) return true;
			}
			cell.changeXPosition(difference);
		}
	}
	else if (to.getXPosition() < from.getXPosition()) {
		while (cell.getXPosition() > to.getXPosition()) {
			if (!board->getCell(cell).isEmpty() && board->getCell(cell).getPiece().getColorOfPiece() == turnColor) {
				if (board->getCell(cell).getPiece().canMove(*this, board->getCell(cell).getPosition(), cell)) return true;
			}
			cell.changeXPosition(difference);
		}
		return false;
	}
	return false;
}


bool Game::doesVerticalCellsAreReachable(const Position& from, const Position& to) {
	Position cell = from;
	int difference = to.getYPosition() > from.getYPosition() ? 1 : -1;
	cell.changeYPosition(difference);
	if (to.getYPosition() > from.getYPosition()) {
		while (cell.getYPosition() < to.getYPosition()) {
			if (!board->getCell(cell).isEmpty() && board->getCell(cell).getPiece().getColorOfPiece() == turnColor) {
				if (board->getCell(cell).getPiece().canMove(*this, board->getCell(cell).getPosition(), cell)) return true;
			}
			cell.changeYPosition(difference);
		}
	}
	else if (to.getYPosition() < from.getYPosition()) {
		while (cell.getYPosition() > to.getYPosition()) {
			if (!board->getCell(cell).isEmpty() && board->getCell(cell).getPiece().getColorOfPiece() == turnColor) {
				if (board->getCell(cell).getPiece().canMove(*this, board->getCell(cell).getPosition(), cell)) return true;
			}
			cell.changeYPosition(difference);
		}
	}
	return false;
}

bool Game::doesDiagonalCellsAreReachable(const Position& from, const Position& to) {
	if (to.getXPosition() > from.getXPosition() && to.getYPosition() < from.getYPosition()) {
		return checkDiagonalReachabilityInSomeDirection(from, to, 1, -1); //upper-right diagonal
	}
	else if (to.getXPosition() < from.getXPosition() && to.getYPosition() < from.getYPosition()) {
		return checkDiagonalReachabilityInSomeDirection(from, to, -1, -1); //upper-left diagonal
	}
	else if (to.getXPosition() < from.getXPosition() && to.getYPosition() > from.getYPosition()) {
		return checkDiagonalReachabilityInSomeDirection(from, to, -1, 1); //down-left diagonal
	}
	else if (to.getXPosition() > from.getXPosition() && to.getYPosition() > from.getYPosition()) {
		return checkDiagonalReachabilityInSomeDirection(from, to, 1, 1); // down-right diagonal
	}
}

bool Game::checkDiagonalReachabilityInSomeDirection(const Position& from, const Position& to, int xOffset, int yOffset) {
	Position current = from;
	current.changeXPosition(xOffset);
	current.changeYPosition(yOffset);
	while (current != to) {
		if (!board->getCell(current).isEmpty() && board->getCell(current).getPiece().getColorOfPiece() == turnColor) {
			if(board->getCell(current).getPiece().canMove(*this, board->getCell(current).getPosition(), current)) return true;
		}
		current.changeXPosition(xOffset);
		current.changeYPosition(yOffset);
	}
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

void Game::processRestartCommand() {
	if (!gameSaved) {
		cout << "This game isn't saved! All progress would be dropped! Would you like to save the game?(Y | N)\n";
		char answer;
		cin >> answer;
		std::tolower(answer);
		if (answer == 'y') {
			processSaveCommand();
			restart();
		}
		else if (answer == 'n') {
			restart();
		}
		else {
			cout << "Hmmm...You have only 2 options to choose! Try again!\n";
			processRestartCommand();
		}
	}
	restart();
}

void Game::restart() {
	board->clear();
	board->intitalize();
	createCastlingsTable();
	gameStopped = false;
	gameSaved = true;
	numberOfAttackers = 0;
	turnCounter = 1;
	movesStory.clear();
	attackersPositions.clear();
}

void Game::processLoadCommand() {
	try {
		cout << "Type name of file(without extension) from which you want to load game: ";
		string fileName{};
		cin >> fileName;
		fileName += ".txt";
		loader = std::make_unique<Loader>();
		loader->load(*this, fileName);
		turnCounter = loader->getTurn();
	}
	catch (std::domain_error & er) {
		cout << er.what();
		processLoadCommand();
	}
}
