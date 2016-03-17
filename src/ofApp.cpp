#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shared_ptr<ImageBank> imgBank = make_shared<ImageBank>();
    GameState::addGameState(new Frontend(imgBank));
    GameState::addGameState(new AISettings(imgBank));
    GameState::addGameState(new Game(imgBank));
    GameState::addGameState(new GameOverWin(imgBank));
    GameState::addGameState(new GameOverLose(imgBank));
    GameState::setState(FRONTEND);
}

//--------------------------------------------------------------
void ofApp::update(){
    GameState::getCurrentState()->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    GameState::getCurrentState()->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
    GameState::getCurrentState()->handleClick(x,y);
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
