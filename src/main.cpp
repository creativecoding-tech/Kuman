#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	//HideCommandPromt
#ifdef _WIN32
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setGLVersion(4, 6);
	settings.setSize(1920, 1080);
	settings.windowMode = OF_FULLSCREEN; //can also be OF_FULLSCREEN

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();

}
