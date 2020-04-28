#include <gtest/gtest.h>
#include "../chess/Game.h"
#include "../chess/Pawn.h"

TEST(PawnTest, inValidWhitePawnMove) {
	Game game;
	game.getBoard().intitalize();
	Pawn pawn(Color::White);
	ASSERT_FALSE(pawn.canMove(game, Position(1, 4), Position(2, 5)));
}

TEST(PawnTest, inValidBlackPawnMove) {
	Game game;
	game.getBoard().intitalize();
	Pawn pawn(Color::Black);
	ASSERT_FALSE(pawn.canMove(game, Position(6, 4), Position(5, 5)));
}