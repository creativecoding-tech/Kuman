#include "Cell.h"
#include <ofMath.h>
#include <ofGraphics.h>

Cell::Cell(float startX, float startY,
	float targetX, float targetY,
	float size, int fibIndex,
	int col, int row,
	bool validTarget) {

    this->startX = startX;
    this->startY = startY;
    this->targetX = targetX;
    this->targetY = targetY;
    x = startX;
    y = startY;
    this->size = size;
    this->col = col;
    this->row = row;
    fibValue = fibonanci(fibIndex);
    isValid = validTarget;

    
    int numberOffCurves = 15;
    for (int i = 0;i < numberOffCurves;i++) {
        curves.push_back(std::make_unique<Curve>(x, y, size));
    }
}

void Cell::startAnimation() {
    animating = true;
    animProgress = 0.0;
}

void Cell::update() {
    if (animating) {
        animProgress += animSpeed;
        if (animProgress >= 1.0) {
            animProgress = 1.0;
            animating = false;
        }

        float t = animProgress;
        float ease = t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;

        //Interpolasi posisi
        x = ofLerp(startX, targetX, ease);
        y = ofLerp(startY, targetY, ease);

        for (auto& curve : curves) {
            curve->updateCellPosition(x, y);
        }
    }
}

void Cell::display() {
    update();
    if (!isValid && animProgress > 0) { return; }
    if ((col + row) % 2 == 0){
        ofSetColor(0);
        ofFill();
    }
    else {
        ofSetColor(255, 195, 80, 70);
        ofFill();
    }

    ofSetLineWidth(1);
    ofDrawRectangle(x, y, size, size);

    for (auto& curve:curves) {
        curve->run();
    }
}

int Cell::fibonanci(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2;i <= n;i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}
