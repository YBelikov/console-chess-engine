#pragma once
struct Position {
private:
	int yPos;
	int xPos;
public:
	int getXPosition() const;
	int getYPosition() const;
	void changeXPosition(int);
	void changeYPosition(int);
	Position(int, int);
	Position() = default;
	bool operator==(const Position&);
	bool operator !=(const Position&);
};