#pragma once
#include "ofMain.h"
#include <memory>
#include <vector>

class Cell {
public:
  float x, y;
  float startX, startY;
  float targetX, targetY;
  ofVec2f gridPos;
  ofVec2f phyloPos;
  float size;
  int col, row;

  bool animating = false;
  float animProgress = 0.0;
  float easeProgress = 0.0; // Eased value
  float animSpeed = 0.1;
  bool isValid = true;
  int fibValue;
  ofColor cellColor; // Fibonacci-based color


  Cell(float startX, float startY, float targetX, float targetY, float size,
       int fibIndex, int col, int row, bool validTarget);

  void startAnimation();
  void toPhyllotaxis();
  void toGrid();
  void update();
  void drawRect(ofShader &shader); // Updated signature
  int fibonanci(int n);
};
