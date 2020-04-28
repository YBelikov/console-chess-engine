#include <gtest/gtest.h>
#include "../chess/Board.h"
#include "../chess/Color.h"

TEST(BoardTest, checkBlackHeavyPiecesPositions) {
	Board board(8);
	board.intitalize();
	ASSERT_EQ(board.getCell(Position(0, 0)).getPiece().getPieceType(), PieceType::Rook);
	ASSERT_EQ(board.getCell(Position(0, 1)).getPiece().getPieceType(), PieceType::Knight);
	ASSERT_EQ(board.getCell(Position(0, 2)).getPiece().getPieceType(), PieceType::Bishop);
	ASSERT_EQ(board.getCell(Position(0, 3)).getPiece().getPieceType(), PieceType::Queen);
	ASSERT_EQ(board.getCell(Position(0, 4)).getPiece().getPieceType(), PieceType::King);
	ASSERT_EQ(board.getCell(Position(0, 5)).getPiece().getPieceType(), PieceType::Bishop);
	ASSERT_EQ(board.getCell(Position(0, 6)).getPiece().getPieceType(), PieceType::Knight);
	ASSERT_EQ(board.getCell(Position(0, 7)).getPiece().getPieceType(), PieceType::Rook);
}

TEST(BoardTest, checkBlackPawnsPositions) {
	Board board(8);
	board.intitalize();
	ASSERT_EQ(board.getCell(Position(1, 0)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 1)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 2)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 3)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 4)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 5)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 6)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(1, 7)).getPiece().getPieceType(), PieceType::Pawn);
}

TEST(BoardTest, checkWhiteHeavyPiecesPositions) {
	Board board(8);
	board.intitalize();
	ASSERT_EQ(board.getCell(Position(7, 0)).getPiece().getPieceType(), PieceType::Rook);
	ASSERT_EQ(board.getCell(Position(7, 1)).getPiece().getPieceType(), PieceType::Knight);
	ASSERT_EQ(board.getCell(Position(7, 2)).getPiece().getPieceType(), PieceType::Bishop);
	ASSERT_EQ(board.getCell(Position(7, 3)).getPiece().getPieceType(), PieceType::Queen);
	ASSERT_EQ(board.getCell(Position(7, 4)).getPiece().getPieceType(), PieceType::King);
	ASSERT_EQ(board.getCell(Position(7, 5)).getPiece().getPieceType(), PieceType::Bishop);
	ASSERT_EQ(board.getCell(Position(7, 6)).getPiece().getPieceType(), PieceType::Knight);
	ASSERT_EQ(board.getCell(Position(7, 7)).getPiece().getPieceType(), PieceType::Rook);
}


TEST(BoardTest, checkWhitePawnsPositions) {
	Board board(8);
	board.intitalize();
	ASSERT_EQ(board.getCell(Position(6, 0)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 1)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 2)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 3)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 4)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 5)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 6)).getPiece().getPieceType(), PieceType::Pawn);
	ASSERT_EQ(board.getCell(Position(6, 7)).getPiece().getPieceType(), PieceType::Pawn);
}



TEST(BoardTest, checkEmptyCells) {
	Board board(8);
	board.intitalize();
	for (int y = 2; y < board.size() - 2; ++y) {
		for (int x = 0; x < board.size(); ++x) {
			ASSERT_TRUE(board.getCell(Position(y, x)).isEmpty());
		}
	}
}