#include "Cell.h"
#include "ofMain.h"
#include <ofGraphics.h>
#include <ofMath.h>

Cell::Cell(float startX, float startY, float targetX, float targetY, float size,
           int fibIndex, int col, int row, bool validTarget) {

  this->startX = startX;
  this->startY = startY;
  this->targetX = targetX;
  this->targetY = targetY;
  x = startX;
  y = startY;
  this->size = size;
  this->col = col;
  this->row = row;
  gridPos.set(startX, startY);
  phyloPos.set(targetX, targetY);
  fibValue = fibonanci(fibIndex);
  isValid = validTarget;

  float hue = fmod(fibIndex * 137.5, 255.0);
  cellColor.setHsb(hue, 255, 220, 200);
}

void Cell::startAnimation() {
  animating = true;
  animProgress = 0.0;
  // Randomize speed for organic feel (0.02 to 0.08)
  animSpeed = ofRandom(0.01, 0.08);
}

void Cell::toPhyllotaxis() {
  startX = x;
  startY = y;
  targetX = phyloPos.x;
  targetY = phyloPos.y;
  startAnimation();
}

void Cell::toGrid() {
  startX = x;
  startY = y;
  targetX = gridPos.x;
  targetY = gridPos.y;
  startAnimation();
}

void Cell::update() {
  if (animating) {
    animProgress += animSpeed;
    if (animProgress >= 1.0) {
      animProgress = 1.0;
      animating = false;
    }

    float t = animProgress;
    easeProgress = t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;

    x = startX + (targetX - startX) * easeProgress;
    y = startY + (targetY - startY) * easeProgress;
  }
}

void Cell::drawRect(ofShader &shader) {

  if (!isValid && animProgress > 0) {
    return;
  }

  if (!shader.isLoaded()) {
    ofSetColor(cellColor);
    ofFill();
    // Draw at 0,0. Shader adds position offset.
    ofDrawRectangle(0, 0, size, size);
  } else {
    // Shader diasumsikan SUDAH begin() di ofApp!

    // Uniform warna
    shader.setUniform1i("isGold", 2); // Mode 2: Fibonacci
    shader.setUniform4f("uCurveColor", cellColor.r / 255.0f,
                        cellColor.g / 255.0f, cellColor.b / 255.0f,
                        cellColor.a / 255.0f);

    // Uniform animasi posisi - GPU yang hitung!
    shader.setUniform2f("startPos", startX, startY);
    shader.setUniform2f("targetPos", targetX, targetY);
    shader.setUniform1f("progress", easeProgress); // Use EASED value

    // Uniform Transformasi DEFAULT (untuk Rect tidak ada rotasi/scale)
    shader.setUniform1f("uScale", 1.0);
    shader.setUniform1f("uRotate", 0.0);
    shader.setUniform2f("uCenterOffset", 0.0,
                        0.0); // Rect sudah digambar di 0,0

    ofFill();
    // Kirim 0,0 sebagai base position, shader akan menggeser (translate) vertex
    // ini
    ofDrawRectangle(0, 0, size, size);
  }
}

int Cell::fibonanci(int n) {
  if (n <= 1)
    return n;
  int a = 0, b = 1;
  for (int i = 2; i <= n; i++) {
    int temp = a + b;
    a = b;
    b = temp;
  }
  return b;
}
