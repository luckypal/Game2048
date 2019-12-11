#include "ofApp.h"

#define COLOR_BACK	ofColor(0xfa, 0xf8, 0xef)
#define COLOR_BOARD	ofColor(0xbb, 0xad, 0xa0)
#define COLOR_CELL_BLANK ofColor(238, 228, 218, 256 * 0.35)
#define COLOR_CELL_TEXT ofColor(0x77, 0x6e, 0x65)
#define COLOR_CELL_TEXT_WHITE 0xf9f6f2
#define COLOR_CELL_FILL {0xeee4da, 0xede0c8, 0xf2b179, 0xf59563, 0xf67c5f, 0xf65e3b, 0xedcf72, 0xedcc61, 0xedc850, 0xedc53f, 0xedc22e};

#define BOARD_IN_RATIO 0.7
#define BOARD_TOP_RATIO 0.2
#define BOARD_BOTTOM_RATIO 0.1
#define BOARD_CELL_RATIO 0.1
#define FONT_RATIO 3.2

#define STRING_TITLE "2048"
#define STRING_DESCRIPTION "How to play: Use your arrow keys to move the tiles. When \n\
two tiles with the same number touch, they merge into one!\n\
W, A, S, D: Arrow, R: Restart Game"

ofColor getColorFromCode(int);
ofColor getColorFromNumber(int);
//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(COLOR_BACK);

	drawTitle();
	drawScore();

	drawBoard();
	drawDescription();
}

void ofApp::drawTitle() {
	ofTrueTypeFont fontTitle;
	fontTitle.load("arialbd.ttf", nBoardSize * 0.1);

	ofSetColor(getColorFromCode(0x776e65));
	string title = STRING_TITLE;
	int fontWidth = fontTitle.stringWidth(title);
	int fontHeight = fontTitle.stringHeight(title);
	fontTitle.drawString(title, rectBoard.getLeft(), rectBoard.getTop() - nBoardSize * 0.05);
}

void ofApp::drawScore() {
	double cellSize = nBoardSize / (BOARD_CELL_RATIO * (Game::BSIZE + (int)0x1) + Game::BSIZE);

	ofTrueTypeFont fontTitle;
	fontTitle.load("arialbd.ttf", cellSize / 4);

	ofSetColor(getColorFromCode(0xbbada0));
	char score[128] = { 0 };
	sprintf(score, "SCORE: %d", game.get_score());

	int fontWidth = fontTitle.stringWidth(score);
	int fontHeight = fontTitle.stringHeight(score);
	fontTitle.drawString(score, rectBoard.getRight() - fontWidth, rectBoard.getTop() - cellSize * 0.25);
}

void ofApp::drawDescription() {
	double cellSize = nBoardSize / (BOARD_CELL_RATIO * (Game::BSIZE + (int)0x1) + Game::BSIZE);

	ofTrueTypeFont fontTitle;
	fontTitle.load("arial.ttf", nBoardSize * 0.029);

	ofSetColor(getColorFromCode(0x776e65));
	char description[256] = STRING_DESCRIPTION;

	int fontWidth = fontTitle.stringWidth(description);
	int fontHeight = fontTitle.stringHeight(description);
	fontTitle.drawString(description, rectBoard.getLeft(), rectBoard.getBottom() + fontHeight / 2);
}

void ofApp::drawBoard() {
	ofSetColor(COLOR_BOARD);
	ofDrawRectangle(rectBoard);

	double cellSize = nBoardSize / (BOARD_CELL_RATIO * (Game::BSIZE + (int)0x1) + Game::BSIZE);
	double cellThick = cellSize * BOARD_CELL_RATIO;

	ofRectangle rectInnerBoard(
		rectBoard.getLeft() + cellThick,
		rectBoard.getTop() + cellThick,
		cellSize - cellThick * 2,
		cellSize - cellThick * 2);

	double fontHeight = cellSize / FONT_RATIO;
	ofTrueTypeFont fontCell;
	fontCell.load("arialbd.ttf", fontHeight);

	for (int row = 0; row < Game::BSIZE; row++) {
		for (int col = 0; col < Game::BSIZE; col++) {
			ofRectangle cell(
				rectInnerBoard.getLeft() + (cellSize + cellThick) * col,
				rectInnerBoard.getTop() + (cellSize + cellThick) * row,
				cellSize, cellSize);
			ofSetColor(COLOR_CELL_BLANK);
			ofDrawRectangle(cell);

			int boardNumber = game.board[row][col];
			if (boardNumber) {
				ofSetColor(getColorFromNumber(boardNumber));
				ofDrawRectangle(cell);

				ofSetColor(COLOR_CELL_TEXT);
				if (boardNumber >= 8)
					ofSetColor(getColorFromCode(COLOR_CELL_TEXT_WHITE));

				char text[100];
				snprintf(text, sizeof(text), "%d", boardNumber);

				int fontWidth = fontCell.stringWidth(text);
				int fontHeight = fontCell.stringHeight(text);
				fontCell.drawString(text, cell.getLeft() + (cellSize - fontWidth) / 2, cell.getTop() + (cellSize - fontHeight) / 2 + fontHeight);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 57357: key = 119; break;
	case 57359: key = 115; break;
	case 57356: key = 97; break;
	case 57358: key = 100; break;
	case 'r': game.restart(); return;
	}

	char input = key;
	game.step(input);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	nWidth = w;
	nHeight = h;
	nBoardSize = MIN(nWidth, nHeight) * BOARD_IN_RATIO;
	int left = (nWidth - nBoardSize) / 2;
	int top = (nHeight - nBoardSize) / 2;
	rectBoard = ofRectangle(left, top, nBoardSize, nBoardSize);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofColor getColorFromCode(int value) {
	return ofColor((value & 0xFF0000) >> 16, (value & 0xFF00) >> 8, value & 0xFF);
}

ofColor getColorFromNumber(int value) {
	int index = log2(value);

	int colorCodes[] = COLOR_CELL_FILL;
	int colorCode = colorCodes[index];

	return getColorFromCode(colorCode);
}