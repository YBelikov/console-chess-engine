#include <gtest/gtest.h>
#include "../chess/Game.h"
#include "../chess/King.h"


TEST(KingTest, invalidMove) {
	Game game;
	game.getBoard().intitalize();
	ASSERT_FALSE(game.getBoard().getCell(Position(0, 4)).getPiece().canMove(game, Position(0, 4), Position(0, 0))); // black king
	ASSERT_FALSE(game.getBoard().getCell(Position(7, 4)).getPiece().canMove(game, Position(7, 4), Position(7, 0))); // white king
}


TEST(KingTest, validMove) {
	Game game;
	game.getBoard().intitalize();
	game.makeMove(Position(1, 4), Position(2, 4));
	game.makeMove(Position(6, 4), Position(5, 4));
	ASSERT_TRUE(game.getBoard().getCell(Position(0, 4)).getPiece().canMove(game, Position(0, 4), Position(1, 4))); // black king
	ASSERT_TRUE(game.getBoard().getCell(Position(7, 4)).getPiece().canMove(game, Position(7, 4), Position(6, 4))); // white king
}

