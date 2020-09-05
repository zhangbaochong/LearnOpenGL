#include "Mouse.h"

float Mouse::lastX = 0;
float Mouse::lastY = 0;
bool Mouse::isFirst = true;

bool Mouse::isFisrtMove()
{
	return isFirst;
}

void Mouse::setFirstMove(bool bFirst)
{
	isFirst = bFirst;
}

float Mouse::getLastX()
{
	return lastX;
}

float Mouse::getLastY()
{
	return lastY;
}

void Mouse::setLastXY(float x, float y)
{
	lastX = x;
	lastY = y;
}