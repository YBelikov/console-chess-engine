#include "Position.h"

Position::Position(int x, int y) : xPos{ x }, yPos{y} {}

int Position::getXPosition() const noexcept { return xPos; }

int Position::getYPosition() const noexcept { return yPos; }

int Position::changeXPosition(int xOffset) { xPos += xOffset; }

int Position::changeYPosition(int yOffset) { yPos += yOffset; }