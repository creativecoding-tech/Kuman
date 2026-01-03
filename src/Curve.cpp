#include "Curve.h"
#include "ofMain.h"
#include <ofGraphics.h>
#include <ofMath.h>
#include <ofMathConstants.h>

Curve::Curve(float x, float y, float size) {
  // Ignore x, y input. We use LOCAL coordinates relative to (0,0)
  cellX = 0;
  cellY = 0;
  cellSize = size;
  angle = 0;

  // posisi awal random dalam cell (centered at 0,0)
  cpx1 = ofRandom(-size * 0.4, size * 0.4);
  cpy1 = ofRandom(-size * 0.4, size * 0.4);

  speedX = ofRandom(-8, 8);
  speedY = ofRandom(-8, -8);

  // warna random
  r = ofRandom((255));
  g = ofRandom((255));
  b = ofRandom((255)); // Fix typo 'g' -> 'b'

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

  // Bounce logic relative to LOCAL center (0,0)
  float half = cellSize * 0.5;
  float margin = cellSize * 0.1;

  if (cpx1 > half - margin || cpx1 < -half + margin) {
    speedX *= -1;
  }
  if (cpy1 > half - margin || cpy1 < -half + margin) {
    speedY *= -1;
  }
}

void Curve::display(ofShader &shader) {
  // Pindahkan Transformasi ke Shader Uniforms!

  // Kirim nilai transformasi ke Shader
  // uCenterOffset = menggeser (0,0) lokal ke tengah cell (size/2, size/2)
  shader.setUniform2f("uCenterOffset", cellSize / 2, cellSize / 2);
  shader.setUniform1f("uRotate", angle);
  shader.setUniform1f("uScale", currentScale);

  // Kirim warna via Uniform (0.0 - 1.0)
  shader.setUniform4f("uCurveColor", r / 255.0f, g / 255.0f, b / 255.0f,
                      strokeAlphaValue / 255.0f);

  ofSetLineWidth(strokeWeightValue);

  float centerX = cellSize / 2;
  float centerY = cellSize / 2;

  switch (mode) {
  case 1:
    ofDrawCurve(cpx1, cpy1, 0, 0, cellSize * 0.25, cellSize * 0.25,
                cellSize * 0.4, cellSize * 0.4);
    break;
  case 2:
    ofDrawCurve(cpx1, cpy1, 0, 0, cellSize * 0.4, cellSize * 0.1,
                cellSize * 0.4, cellSize * 0.4);
    break;
  case 4:
    ofDrawCurve(cpx1, cpy1, 0, 0, cellSize * 0.4, cellSize * 0.4,
                cellSize * 0.4, cellSize * 0.4);
    break;
  case 5:
    ofDrawCurve(cpx1, cpy1, 0, 0, cellSize * 0.3, cellSize * 0.1,
                cellSize * 0.4, cellSize * 0.4);
    break;
  case 6:
    // Kurva ke bawah
    ofDrawCurve(cpx1, cpy1, 0, 0, cellSize * 0.3, cellSize * 0.4,
                cellSize * 0.4, cellSize * 0.4);
    break;
  }
}

void Curve::run() {
  update();
}

void Curve::updateCellPosition(float newX, float newY) {
  float dx = newX - cellX;
  float dy = newY - cellY;

  cellX = newX;
  cellY = newY;

  cpx1 += dx;
  cpy1 += dy;
}