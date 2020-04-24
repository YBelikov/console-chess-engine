#pragma once
struct Position {
	int xPos;
	int yPos;
	int getXPosition() const;
	int getYPosition() const;
	void changeXPosition(int);
	void changeYPosition(int);
	Position(int, int);
	Position() = default;
};