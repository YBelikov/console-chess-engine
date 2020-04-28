#include <gtest/gtest.h>
#include "../chess/Knight.h"
#include "../chess/Game.h"

TEST(KhightTest, inValidKnightMove) {
	Game game;
	game.getBoard().intitalize();
	ASSERT_FALSE(game.getBoard().getCell(Position(0, 1)).getPiece().canMove(game, Position(0, 1), Position(2, 3))); // black knight
	ASSERT_FALSE(game.getBoard().getCell(Position(0, 1)).getPiece().canMove(game, Position(7, 1), Position(5, 3))); // white knight
}

TEST(KhightTest, validKnightMove) {
	Game game;
	game.getBoard().intitalize();
	ASSERT_TRUE(game.getBoard().getCell(Position(0, 1)).getPiece().canMove(game, Position(0, 1), Position(2, 0))); // black knight
	ASSERT_TRUE(game.getBoard().getCell(Position(0, 1)).getPiece().canMove(game, Position(7, 1), Position(5, 2))); // white knight
}
