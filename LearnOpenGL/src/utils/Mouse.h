#pragma once
class Mouse
{
public:
	static bool isFisrtMove();

	static void setFirstMove(bool bFirst);

	static float getLastX();

	static float getLastY();

	static void setLastXY(float x, float y);

private:
	static bool isFirst;

	static float lastX, lastY;
};
