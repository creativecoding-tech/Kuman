#include "Curve.h"
#include <ofMath.h>

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
}