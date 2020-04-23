#pragma once
struct Position {
	int xPos;
	int yPos;
	int getXPosition() const noexcept;
	int getYPosition() const noexcept;
	int changeXPosition(int) noexcept;
	int changeYPosition(int) noexcept;
	Position(int, int);
	Position() = default;
};