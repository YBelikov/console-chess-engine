#include <gtest/gtest.h>
#include "../chess/Rook.h"
#include "../chess/Game.h"

TEST(RookTest, inValidWhiteRookMove) {
	Game game;
	game.getBoard().intitalize();
	Rook rook(Color::White);
	ASSERT_FALSE(rook.canMove(game, Position(0, 0), Position(0, 2)));
	ASSERT_FALSE(rook.canMove(game, Position(0, 7), Position(3, 7)));
}

TEST(RookTest, inValidBlackRookMove) {
	Game game;
	game.getBoard().intitalize();
	Rook rook(Color::Black);
	ASSERT_FALSE(rook.canMove(game, Position(7, 0), Position(5, 0)));
	ASSERT_FALSE(rook.canMove(game, Position(7, 0), Position(7, 2)));
}

TEST(RookTest, validWhiteRookMove) {
	Game game;
	game.getBoard().intitalize();
	Rook rook(Color::White);
	game.makeMove(Position(1, 0), Position(3, 0));
	ASSERT_TRUE(rook.canMove(game, Position(0, 0), Position(2, 0)));
}


TEST(RookTest, validBlackRookMove) {
	Game game;
	game.getBoard().intitalize();
	Rook rook(Color::Black);
	game.makeMove(Position(6, 0), Position(4, 0));
	ASSERT_TRUE(rook.canMove(game, Position(7, 0), Position(5, 0)));
}