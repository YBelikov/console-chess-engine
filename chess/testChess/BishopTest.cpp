#include <gtest/gtest.h>
#include "../chess/Bishop.h"
#include "../chess/Game.h"


TEST(BishopTest, inValidBishopMove) {
	Game game;
	game.getBoard().intitalize();
	ASSERT_FALSE(game.getBoard().getCell(Position(0, 2)).getPiece().canMove(game, Position(0, 2), Position(2, 2))); // black bishop
	ASSERT_FALSE(game.getBoard().getCell(Position(7, 2)).getPiece().canMove(game, Position(7, 2), Position(5, 2))); // white bishop
}

TEST(BishopTest, validBishopMove) {
	Game game;
	game.getBoard().intitalize();
	game.makeMove(Position(1, 3), Position(2, 3));
	game.makeMove(Position(6, 3), Position(5, 3));
	ASSERT_TRUE(game.getBoard().getCell(Position(0, 2)).getPiece().canMove(game, Position(0, 2), Position(2, 4))); // black bishop
	ASSERT_TRUE(game.getBoard().getCell(Position(7, 2)).getPiece().canMove(game, Position(7, 2), Position(6, 3))); // white bishop
}