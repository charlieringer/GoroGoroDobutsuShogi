#include "ofApp.h"
#include "AIValues.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    //Sets up the game states
    shared_ptr<ImageBank> imgBank = make_shared<ImageBank>();
    GameState::addGameState(new Frontend(imgBank));
    GameState::addGameState(new AISettings(imgBank));
    GameState::addGameState(new Instructions(imgBank));
    GameState::addGameState(new Game(imgBank));
    GameState::addGameState(new GameOverLose(imgBank));
    GameState::addGameState(new GameOverWin(imgBank));
    GameState::setState(FRONTEND);
    //And starting AI values
    AIValues::setExploreConstant(1);
    AIValues::setNumIterations(5000);
}

//--------------------------------------------------------------
void ofApp::update(){
    //Updates the current state
    GameState::getCurrentState()->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //Draws the current state
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
    //Handles any clicks
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
