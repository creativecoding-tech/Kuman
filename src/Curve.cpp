#include "Curve.h"
#include <ofMath.h>
#include <ofMathConstants.h>
#include <ofGraphics.h>
#include <ofAppRunner.h>

Curve::Curve(float x,float  y,float size) {
	cellX = x;
	cellY = y;
	cellSize = size;
	angle = 0;

	//posisi awal random dalam cell
	cpx1 = x + ofRandom(size * 0.2, size * 0.8);
	cpy1 = y + ofRandom(size * 0.2, size * 0.8);

	
	speedX = ofRandom(-8, 8);
	speedY = ofRandom(-8, -8);

	//warna random
	r = ofRandom((255));
	g = ofRandom((255));
	g = ofRandom((255));

	strokeWeightValue = ofRandom(1, 3);
	strokeAlphaValue = ofRandom(50, 150);
	mode = floor(ofRandom(1, 7));

	zoomAngle = ofRandom(TWO_PI);
	zoomSpeed = ofRandom(0.05, 0.1);
	minScale = 0.3;
	maxScale = 1.0;
	currentScale = 1.0;
}

void Curve::update() {
	cpx1 += speedX;
	cpy1 += speedY;

	angle -= 0.03;

	zoomAngle += zoomSpeed;
	currentScale = ofMap(cos(zoomAngle), -1, 1, minScale, maxScale);

	if (cpx1 > cellX + cellSize * 0.9 || cpx1 < cellX + cellSize * 0.1) {
		speedX *= -1;
	}
	if (cpy1 > cellY + cellSize * 0.9 || cpy1 < cellY + cellSize * 0.1) {
		speedY *= -1;
	}
}

void Curve::display() {
	ofPushMatrix();
	ofTranslate(cellX + cellSize / 2, cellY + cellSize / 2);
	ofRotateRad(angle);
	ofScale(currentScale);
	ofTranslate(-cellSize / 2, -cellSize / 2);

	ofNoFill();
	ofSetLineWidth(strokeWeightValue);
	ofSetColor(r, g, b, strokeAlphaValue);

	float centerX = cellSize / 2;
	float centerY = cellSize / 2;

	switch (mode) {
	case 1:
		ofDrawCurve(cpx1-cellX,cpy1 -cellY,centerX,centerY,
			cellSize*0.25,cellSize*0.25,cellSize,cellSize);
		break;
	case 2:
		ofDrawCurve(cpx1 - cellX, cpy1 - cellY, centerX, centerY,
			cellSize * 0.75, cellSize * 0.2,
			cellSize, cellSize);
		break;
	case 4:
		ofDrawCurve(cpx1 - cellX, cpy1 - cellY, centerX, centerY,
			cellSize * 0.75, cellSize * 0.8,
			cellSize, cellSize);
		break;
	case 5:
		ofDrawCurve(cpx1 - cellX, cpy1 - cellY, centerX, centerY,
			cellSize * 0.5, cellSize * 0.2,
			cellSize, cellSize);
		break;
	case 6:
		// Kurva ke bawah
		ofDrawCurve(cpx1 - cellX, cpy1 - cellY, centerX, centerY,
			cellSize * 0.5, cellSize * 0.8,
			cellSize, cellSize);
		break;
	}
	ofPopMatrix();
}

void Curve::run() {
	update();
	display();
}

void Curve::updateCellPosition(float newX, float newY) {
	float dx = newX - cellX;
	float dy = newY - cellY;

	cellX = newX;
	cellY = newY;

	cpx1 += dx;
	cpy1 += dy;
}