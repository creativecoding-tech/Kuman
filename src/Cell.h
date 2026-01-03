#pragma once
#include <memory>
#include <vector>
#include "Curve.h"
class Cell
{
public:
	float x, y;
	float startX, startY;
	float targetX, targetY;
	float size;
	int fibValue;
	int col, row;
	std::vector<std::unique_ptr<Curve>> curves;

	bool animating = false;
	float animProgress = 0.01;
	float animSpeed = 0.05;
	bool isValid = true;

	Cell(float startX, float startY, 
		float targetX, float targetY,
		float size,int finIndex,
		int col,int row,
		bool validTarget);

	void startAnimation();
	void update();
	void display();
	int fibonanci(int n);
};

