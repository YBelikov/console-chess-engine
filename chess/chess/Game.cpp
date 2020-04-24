#include "Game.h"
#include <iostream>
#include <string>
#include <regex>

using std::string;
using std::cin;
using std::cout;
using std::regex;

Game::Game() {
	board = std::make_unique<Board>(8);
	
}



void Game::initializeBoard() {
	board->intitalize();
}

void Game::start() {
	initializeBoard();
	
	const std::regex allowedCommandsRegex("qslm");
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
		Position from(moveCommand[1], moveCommand[0] - 'a');
		Position to(moveCommand[4], moveCommand[3] - 'a');
		try {
			board.movePiece(from, to);
		}catch(...){

		}
	}

}