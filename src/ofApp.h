#pragma once

#include "Cell.h"
#include "ofMain.h"
#include "ofxGui.h" // Sertakan library GUI

class ofApp : public ofBaseApp {

public:
  int cellSize = 15;
  std::vector<std::unique_ptr<Cell>> grid;
  ofShader shader; // Pengelola Shader

  // Anggota GUI (Radio Button Style)
  ofxPanel gui;
  ofxToggle modeTrails; // Mode 1: Trails
  ofxToggle modeCanvas;  // Mode 2: Hitam
  ofxToggle modeNormal; // Mode 3: Normal
  bool showGui = false;

  // Fungsi listener untuk menangani logika "hanya satu yang aktif" (Radio
  // Button)
  void modeTrailsChanged(bool &val);
  void modeCanvasChanged(bool &val);
  void modeNormalChanged(bool &val);

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
