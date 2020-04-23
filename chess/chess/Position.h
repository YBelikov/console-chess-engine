#pragma once
struct Position {
	int xPos;
	int yPos;
	int getXPosition() const noexcept;
	int getYPosition() const noexcept;
	void changeXPosition(int);
	void changeYPosition(int);
	Position(int, int);
	Position() = default;
};