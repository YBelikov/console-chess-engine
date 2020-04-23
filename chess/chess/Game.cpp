#include "Game.h"
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;


Game::Game() {
	board = std::make_unique<Board>(8);
}

void Game::initializeBoard() {
	board->intitalize();
}

void Game::start() {
	initializeBoard();
	string command{};
	do {
		displayer.display(*board, cout);
		cin >> command;
		for (auto& c : command) {
			std::tolower(c);
		}
	} while (command != "quit");
	
}