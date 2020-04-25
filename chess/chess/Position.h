#pragma once
struct Position {
	int yPos;
	int xPos;
	int getXPosition() const;
	int getYPosition() const;
	void changeXPosition(int);
	void changeYPosition(int);
	Position(int, int);
	Position() = default;
};