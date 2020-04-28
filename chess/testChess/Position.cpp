#include "Position.h"

Position::Position(int y, int x) : yPos{y}, xPos{ x } {}

int Position::getXPosition() const { return xPos; }

int Position::getYPosition() const { return yPos; }

void Position::changeXPosition(int xOffset) { xPos += xOffset; }

void Position::changeYPosition(int yOffset) { yPos += yOffset; }

bool Position::operator==(const Position& other) {
	return xPos == other.getXPosition() && yPos == other.getYPosition();
}

bool Position::operator!=(const Position& other) {
	return !(*this == other);
}