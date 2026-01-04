#pragma once

#include "Cell.h"
#include "ofMain.h"
#include "ofxGui.h" // Sertakan library GUI

class ofApp : public ofBaseApp {

public:
  ofParameter<int> cellSize; // Diubah jadi ofParameter untuk GUI
  std::vector<std::unique_ptr<Cell>> grid;
  ofShader shader; // Pengelola Shader

  enum BackgroundMode { TRAILS, CANVAS, NORMAL };
  BackgroundMode currentMode = TRAILS;

  // Anggota GUI
  ofxPanel gui;
  ofxToggle modeTrails;
  ofxToggle modeCanvas;
  ofxToggle modeNormal;

  ofxButton cellSizeUp;
  ofxButton cellSizeDown;
  ofxLabel cellSizeDisplay;

  bool showGui = false;
  bool crusorVisible = true;

  //Listener untuk perubahan pada background
  void modeTrailsChanged(bool& val);
  void modeCanvasChanged(bool& val);
  void modeNormalChanged(bool& val);

  // Listener untuk perubahan cellSize
  void cellSizeChanged(int &val);
  void cellSizeUpPressed();
  void cellSizeDownPressed();
  void updateCellSizeDisplay();

  // Helper untuk membuat ulang grid
  void setupGrid();

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
