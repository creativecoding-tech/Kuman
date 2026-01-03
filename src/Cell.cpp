#include "Cell.h"
#include "ofMain.h" // Needed for ofShader definition
#include <ofGraphics.h>
#include <ofMath.h>

// Static member definitions removed
// setupShader removed

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
  fibValue = fibonanci(fibIndex);
  isValid = validTarget;

  int numberOffCurves = 15;
  for (int i = 0; i < numberOffCurves; i++) {
    curves.push_back(std::make_unique<Curve>(0, 0, size));
  }
}

void Cell::startAnimation() {
  animating = true;
  animProgress = 0.0;
  // Randomize speed for organic feel (0.02 to 0.08)
  animSpeed = ofRandom(0.02, 0.08);
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
  }

  for (auto &curve : curves) {
    curve->update();
  }
}

void Cell::drawRect(ofShader &shader) {

  if (!isValid && animProgress > 0) {
    return;
  }

  if (!shader.isLoaded()) {
    // ofLogWarning("Shader tidak loaded! Pakai CPU fallback"); // Spamming log
    // if in loop? remove warning or keep 'once' CPU fallback
    if ((col + row) % 2 == 0) {
      ofSetColor(0);
    } else {
      ofSetColor(255, 195, 80, 70);
    }
    ofFill();
    // Draw at 0,0. Shader adds position offset.
    ofDrawRectangle(0, 0, size, size);
  } else {
    // Shader diasumsikan SUDAH begin() di ofApp!

    // Uniform warna
    int isGold = ((col + row) % 2 != 0) ? 1 : 0;
    shader.setUniform1i("isGold", isGold);

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

void Cell::drawCurves(ofShader &shader) {
  // Set uniforms for curves (same position logic as rects)
  shader.setUniform2f("startPos", startX, startY);
  shader.setUniform2f("targetPos", targetX, targetY);
  shader.setUniform1f("progress", easeProgress); // Use EASED value

  // Mode -1: Use vertex color (not gold/black)
  shader.setUniform1i("isGold", -1);

  // Curves
  for (auto &curve : curves) {
    curve->display(shader); // Pass shader to curve
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
