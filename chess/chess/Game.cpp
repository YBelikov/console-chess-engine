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
}



void Game::initializeBoard() {
	board->intitalize();
}

void Game::start() {
	initializeBoard();
	const std::regex allowedCommandsRegex("[qslm]");
	char commandChar;
	do {
		system("cls");
		displayer.display(*board, cout);
		cout << "Now you can use next options in game: (Q)uit, (S)ave, (L)oad, (M)ove: ";
		cin >> commandChar;
		std::tolower(commandChar);
		if (!std::regex_match(string{ commandChar }, allowedCommandsRegex)) {
			cout << "Wrong option\n";
		}
		else {
			switch (commandChar) {
			case 'm':
				processMoveCommand();
				break;
			}
		}
	} while (commandChar != 'q');
	
}

void Game::processMoveCommand() {
	const std::regex moveRegex("[a-h][1-8]-[a-h][1-8]");
	string moveCommand{};
	cin >> moveCommand;
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
		checkDoesNextCellOcupiedByPieceOfSameColor(from, to);
		board->getCell(from).getPiece().canMove(*this, from, to);
	}
	catch (logic_error & ex) {
		throw;
	}
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
