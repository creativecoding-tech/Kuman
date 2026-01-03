#pragma once
class Curve
{
public:
	float cpx1, cpy1;
	float speedX, speedY;
	float r, g, b;
	float strokeWeightValue;
	int mode;
	float strokeAlphaValue;
	float angle;

	float zoomAngle;
	float zoomSpeed;
	float minScale;
	float maxScale;
	float currentScale;

	float cellX, cellY;
	float cellSize;
	Curve(float x, float y, float size);
	Curve();
	void update();
	void display();
	void run();
	void updateCellPosition(float newX, float newY);

};

