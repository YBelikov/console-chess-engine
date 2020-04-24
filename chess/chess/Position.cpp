#include "Position.h"

Position::Position(int y, int x) : xPos{ x }, yPos{y} {}

int Position::getXPosition() const { return xPos; }

int Position::getYPosition() const { return yPos; }

void Position::changeXPosition(int xOffset) { xPos += xOffset; }

void Position::changeYPosition(int yOffset) { yPos += yOffset; }