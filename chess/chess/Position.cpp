#include "Position.h"

Position::Position(int x, int y) : xPos{ x }, yPos{y} {}

int Position::getXPosition() const noexcept { return xPos; }

int Position::getYPosition() const noexcept { return yPos; }

void Position::changeXPosition(int xOffset) { xPos += xOffset; }

void Position::changeYPosition(int yOffset) { yPos += yOffset; }