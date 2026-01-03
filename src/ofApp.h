#pragma once

#include "Cell.h"
#include "Curve.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
  int cellSize = 15;
  std::vector<std::unique_ptr<Cell>> grid;
  ofShader shader; // Shader manager
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
};
