#include "Loader.h"
#include "Game.h"
#include "Color.h"
#include <fstream>

#include "Rook.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

Loader::Loader() {
	createPiecesTable();
}

void Loader::createPiecesTable() {
	pieces['p'] = PieceType::Pawn;
	pieces['r'] = PieceType::Rook;
	pieces['n'] = PieceType::Knight;
	pieces['b'] = PieceType::Bishop;
	pieces['q'] = PieceType::Queen;
	pieces['k'] = PieceType::King;
}

void Loader::load(Game& game, std::string& filePath) {
	std::ifstream in(filePath.c_str());
	if (!in) {
		throw std::domain_error("Error with file opening!\n");
	}
	game.getBoard().clear();
	std::string gameLine{};
	std::getline(in, gameLine);
	parser.setStringToParse(gameLine);
	turn = std::stoi(parser.getNextToken());
	while(in) {
		while (!parser.reachEndOfTheLine()) {
			std::string token = parser.getNextToken();
			if(token != "") loadNextPiece(game, token);
		}
		std::getline(in, gameLine);
		parser.setStringToParse(gameLine);
	}
}

void Loader::loadNextPiece(Game& game, std::string& token){
	std::string pieceDescription = token.substr(0, 2);
	std::string positionDescription = token.substr(2);
	char colorChar = pieceDescription[0];
	char piece = pieceDescription[1];
	int y = std::stoi(positionDescription.substr(0, 1));
	int x = std::stoi(positionDescription.substr(1, 1));
	Color color;
	if (colorChar == 'w') color = Color::White;
	else if (colorChar == 'b') color = Color::Black;

	createPiece(game, color, Position(y, x), pieces[piece]);
}

void Loader::createPiece(Game& game, Color color, Position pos, PieceType type) {
	if (type == PieceType::Pawn) {
		game.getBoard().getCell(pos).setPiece(std::make_unique<Pawn>(color)); 
	}
	else if (type == PieceType::Rook) {
		game.getBoard().getCell(pos).setPiece(std::make_unique<Rook>(color));
	}
	else if (type == PieceType::Knight) {
		game.getBoard().getCell(pos).setPiece(std::make_unique<Knight>(color));
	}
	else if (type == PieceType::Bishop) {
		game.getBoard().getCell(pos).setPiece(std::make_unique<Bishop>(color));
	}
	else if (type == PieceType::Queen) {
		game.getBoard().getCell(pos).setPiece(std::make_unique<Queen>(color));
	}
	else if (type == PieceType::King) {
		game.getBoard().getCell(pos).setPiece(std::make_unique<King>(color));
	}
}