#pragma once
#include "Curve.h"
#include "ofMain.h"
#include <memory>
#include <vector>

class Cell {
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
  float easeProgress = 0.0; // Eased value
  float animSpeed = 0.1;
  bool isValid = true;

  // Removed static shader members

  Cell(float startX, float startY, float targetX, float targetY, float size,
       int finIndex, int col, int row, bool validTarget);

  void startAnimation();
  void update();
  void drawRect(ofShader &shader);   // Updated signature
  void drawCurves(ofShader &shader); // Updated signature
  int fibonanci(int n);
};
