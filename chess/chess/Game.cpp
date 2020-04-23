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
	string command{};
	cin >> command;
	for (auto& c : command) {
		std::tolower(c);
	}
	while (command != "quit") {
		display.show(board);
	}
}