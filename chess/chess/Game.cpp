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
	const std::regex moveRegex("[a-h][1-8]-[a-h][1-8]");
	string command{};

	do {
		system("cls");
		displayer.display(*board, cout);
		cout << "Now you can use next options in game: (Q)uit, (S)ave, (L)oad, (M)ove: ";
		cin >> command;
		for (auto& c : command) {
			std::tolower(c);
		}
		if (std::regex_match(command, moveRegex)) {
			


			Position from;
			Position to;
			from.changeXPosition(command[0] - 'a');
			from.changeYPosition(command[1]);
			to.changeXPosition(command[3] - 'a');
			to.changeYPosition(command[4]);

		}
		if (command == "refresh") { board = std::make_unique<Board>(8);
			board->intitalize(); 
		}
	} while (command != "quit");
	
}