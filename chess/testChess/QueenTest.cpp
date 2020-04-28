#include <gtest/gtest.h>
#include "../chess/Queen.h"
#include "../chess/Game.h"

TEST(QueenTest, invalidMove) {
	Game game;
	game.getBoard().intitalize();
	ASSERT_FALSE(game.getBoard().getCell(Position(0, 3)).getPiece().canMove(game, Position(0, 3), Position(5, 0))); // black queen
	ASSERT_FALSE(game.getBoard().getCell(Position(7, 3)).getPiece().canMove(game, Position(7, 3), Position(5, 3))); // white queen
}

TEST(QueenTest, validMove) {
	Game game;
	game.getBoard().intitalize();
	game.makeMove(Position(1, 4), Position(2, 4));
	game.makeMove(Position(6, 4), Position(5, 4));
	ASSERT_TRUE(game.getBoard().getCell(Position(0, 3)).getPiece().canMove(game, Position(0, 3), Position(1, 4))); // black queen
	ASSERT_TRUE(game.getBoard().getCell(Position(7, 3)).getPiece().canMove(game, Position(7, 3), Position(6, 4))); // white queen
}
