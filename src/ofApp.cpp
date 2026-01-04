#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetVerticalSync(false);
  ofSetBackgroundAuto(false);
  ofSetEscapeQuitsApp(false);
  ofBackground(255);
  ofEnableAntiAliasing();
  ofEnableSmoothing();
  ofSetLineWidth(1.0);

  shader.load("shadersGL3/shader");

  // Inisialisasi GUI   
  gui.setup("Pengaturan Kuman");

  // Inisialisasi nilai cellSize secara manual karena slider sudah dihapus
  cellSize.set("Ukuran Cell", 15, 5, 60);

  // Cell Size "Stepper" (Label + Buttons)
  gui.add(cellSizeDisplay.setup("Ukuran (5-60)", ofToString(cellSize.get())));
  gui.add(cellSizeUp.setup("[ + ] Tambah"));
  gui.add(cellSizeDown.setup("[ - ] Kurang"));

  gui.add(modeTrails.setup("Mode Trails", true));
  gui.add(modeCanvas.setup("Mode Canvas", false));
  gui.add(modeNormal.setup("Mode Normal", false));

  //Tambahkan listener untuk perubahan pada background
  modeTrails.addListener(this, &ofApp::modeTrailsChanged);
  modeCanvas.addListener(this, &ofApp::modeCanvasChanged);
  modeNormal.addListener(this, &ofApp::modeNormalChanged);

  // Tambahkan listener untuk perubahan ukuran cell
  cellSize.addListener(this, &ofApp::cellSizeChanged);
  cellSizeUp.addListener(this, &ofApp::cellSizeUpPressed);
  cellSizeDown.addListener(this, &ofApp::cellSizeDownPressed);

  

  // Inisialisasi Grid pertama kali
  setupGrid();
}

// Helper untuk membuat ulang grid secara dinamis
void ofApp::setupGrid() {
  grid.clear();

  int cols = ofGetWidth() / cellSize;
  int rows = ofGetHeight() / cellSize;
  int totalCells = cols * rows;
  float goldenAngle = DEG_TO_RAD * 137.5;

  // Titik tengah layar
  float centerX = ofGetWidth() / 2;
  float centerY = ofGetHeight() / 2;

  for (int n = 0; n < totalCells; n++) {
    int gridCol = n % cols;
    int gridRow = n / cols;
    float startX = gridCol * cellSize;
    float startY = gridRow * cellSize;

    // Hitung posisi phyllotaxis (target)
    float angle = n * goldenAngle;
    float radius = cellSize * 0.35 * sqrt(n);
    float targetX = centerX + radius * cos(angle);
    float targetY = centerY + radius * sin(angle);

    // Cek apakah target berada di dalam batas layar
    bool validTarget =
        (targetX >= cellSize && targetX < ofGetWidth() - cellSize * 2 &&
         targetY >= cellSize && targetY < ofGetHeight() - cellSize * 2);

    grid.push_back(std::make_unique<Cell>(startX, startY, targetX, targetY,
                                          cellSize, n, gridCol, gridRow,
                                          validTarget));
  }
}

// Inilah fungsi yang dipanggil saat slider digeser
void ofApp::cellSizeChanged(int &val) {
  setupGrid();
  updateCellSizeDisplay();
}

void ofApp::cellSizeUpPressed() {
  if (cellSize < 60) {
    cellSize++;
  }
}

void ofApp::cellSizeDownPressed() {
  if (cellSize > 5) {
    cellSize--;
  }
}

void ofApp::updateCellSizeDisplay() {
  cellSizeDisplay = ofToString((int)cellSize);
}

//--------------------------------------------------------------
void ofApp::update() {
  for (auto &cl : grid) {
    cl->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Logika Pemilihan Background (Switch Case Style)
  switch (currentMode) {
  case TRAILS:
    // Mode 1: Background transparan (Efek Trails)
    ofSetBackgroundAuto(false);
    ofSetColor(255, 30);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    break;
  case CANVAS:
    // Mode 2: Tanpa pembersihan
    ofSetBackgroundAuto(false);
    break;
  case NORMAL:
    // Mode 3: Background Normal (Putih)
    ofSetBackgroundAuto(true);
    ofBackground(255);
    break;
  }

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
void ofApp::mousePressed(int x, int y, int button) {
    if (button == 2)  //Klik kanan
    {
        crusorVisible = !crusorVisible;
    }
    if (crusorVisible) ofShowCursor();
    if (!crusorVisible) ofHideCursor();
}

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

void ofApp::modeTrailsChanged(bool& val) {
    if (val) {
        modeCanvas = false;
        modeNormal = false;
        currentMode = TRAILS;
    }
}

void ofApp::modeCanvasChanged(bool& val) {
    if (val) {
        modeTrails = false;
        modeNormal = false;
        currentMode = CANVAS;
    }
}

void ofApp::modeNormalChanged(bool& val) {
    if (val) {
        modeTrails = false;
        modeCanvas = false;
        currentMode = NORMAL;
    }
}