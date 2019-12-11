#pragma once

#include <iostream>

#include "ofMain.h"
#include <ofxButton.h>
#include "game.h"

class ofApp : public ofBaseApp{

	public:
		Game game;
		int nWidth;
		int nHeight;
		int nBoardSize;
		ofRectangle rectBoard;

		void setup();
		void update();
		void draw();
		void drawTitle();
		void drawScore();
		void drawBoard();
		void drawDescription();

		void drawFailure();
		void drawSuccess();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
