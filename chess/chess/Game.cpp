#include "Game.h"
#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>

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
		cout << "Wrong format of move";
	}
	else {
		Position from(moveCommand[1] - '0' - 1, int(moveCommand[0]) - int('a'));
		Position to(moveCommand[4] - '0' - 1, int(moveCommand[3]) - int('a'));
		try {
			checkMove(from, to);
			makeMove(from, to);

		}catch(logic_error& ex){
			cout << ex.what();
			processMoveCommand();
		}
	}

}

void Game::checkMove(const Position& from, const Position& to) {
	try {
		if (board->getCell(from).isEmpty()) throw logic_error("The starting cell is empty\n");
		board->getCell(from).getPiece().canMove(*board, from, to);
	}
	catch (logic_error & ex) {
		throw;
	}
}

void Game::makeMove(const Position& from, const Position& to) {
	board->getCell(to).setPiece(std::unique_ptr<Piece>(board->getCell(from).releasePiece()));
}