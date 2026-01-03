#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetVerticalSync(false);
  grid.clear();
  ofSetBackgroundAuto(false);
  ofSetEscapeQuitsApp(false);
  ofBackground(255);
  ofEnableAntiAliasing();
  ofEnableSmoothing();
  ofSetLineWidth(1.0);

  shader.load("shadersGL3/shader");

  // Inisialisasi GUI (Gaya Radio Button)
  gui.setup("Pengaturan Background");
  gui.add(modeTrails.setup("Mode Trails", true));
  gui.add(modeCanvas.setup("Mode Canvas", false));
  gui.add(modeNormal.setup("Mode Normal", false));

  // Tambahkan listener untuk logika Radio Button (hanya satu yang aktif)
  modeTrails.addListener(this, &ofApp::modeTrailsChanged);
  modeCanvas.addListener(this, &ofApp::modeCanvasChanged);
  modeNormal.addListener(this, &ofApp::modeNormalChanged);

  showGui = true;

  int cols = ofGetWidth() / cellSize;
  int rows = ofGetHeight() / cellSize;
  int totalCells = cols * rows;
  float goldenAngle = DEG_TO_RAD * 137.5;

  // center point
  float centerX = ofGetWidth() / 2;
  float centerY = ofGetHeight() / 2;

  for (int n = 0; n < totalCells; n++) {
    int gridCol = n % cols;
    int gridRow = n / cols;
    float startX = gridCol * cellSize;
    float startY = gridRow * cellSize;

    // hitung posisi phyllotaxis (target)
    float angle = n * goldenAngle;
    float radius = cellSize * 0.35 * sqrt(n);
    float targetX = centerX + radius * cos(angle);
    float targetY = centerY + radius * sin(angle);

    // cek apakah target dalam bound layar
    bool validTarget =
        (targetX >= cellSize && targetX < ofGetWidth() - cellSize * 2 &&
         targetY >= cellSize && targetY < ofGetHeight() - cellSize * 2);

    grid.push_back(std::make_unique<Cell>(startX, startY, targetX, targetY,
                                          cellSize, n, gridCol, gridRow,
                                          validTarget));
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  for (auto &cl : grid) {
    cl->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Logika Pemilihan Background (Radio Button Style)
  if (modeTrails) {
    // Mode 1: Background transparan (Efek Trails)
    ofSetBackgroundAuto(false);
    ofSetColor(255, 30);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  } else if (modeCanvas) {
    // Mode 2: Tanpa
  } else if (modeNormal) {
    // Mode 3: Background Normal (Putih)
    ofSetBackgroundAuto(true);
    ofBackground(255);
  }

  ofNoFill();

  shader.begin();
  for (auto &cl : grid) {
    cl->drawRect(shader);
  }
  shader.end();

  // Tampilkan GUI jika diaktifkan
  if (showGui) {
    gui.draw();
  }

  // Tampilkan FPS di layar
  // ofSetColor(255, 0, 0);
  // string fpsStr = "FPS: " + ofToString(ofGetFrameRate());
  // ofDrawBitmapString(fpsStr, 20, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 'q' || key == 'Q')
    ofExit(0);

  if (key == 'p' || key == 'P') {
    for (auto &cl : grid) {
      cl->toPhyllotaxis();
    }
  }

  if (key == 'n' || key == 'N') {
    for (auto &cl : grid) {
      cl->toGrid();
    }
  }

  // Toggle tampilan GUI dengan tombol 'g'
  if (key == 'g' || key == 'G') {
    showGui = !showGui;
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}

// Logika Radio Button: Matikan toggle lain jika yang satu dinyalakan
void ofApp::modeTrailsChanged(bool &val) {
  if (val) {
    modeCanvas = false;
    modeNormal = false;
  }
}

void ofApp::modeCanvasChanged(bool &val) {
  if (val) {
    modeTrails = false;
    modeNormal = false;
  }
}

void ofApp::modeNormalChanged(bool &val) {
  if (val) {
    modeTrails = false;
    modeCanvas = false;
  }
}
