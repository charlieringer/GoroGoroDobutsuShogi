#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
    switch(state)
    {
        case(FRONTEND):
            break;
        case(INGAME):
            game.takeAITurn();
            game.checkEnd();
            break;
        case(GAMEOVERWIN):
            break;
        case(GAMEOVERLOSE):
            break;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    switch(state)
    {
        case(FRONTEND):
            frontend.drawFrontend();
            break;
        case(INGAME):
            game.drawGame();
            break;
        case(GAMEOVERWIN):
            gameOverWin.display();
            break;
        case(GAMEOVERLOSE):
            gameOverLose.display();
            break;
    }
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
    switch(state)
    {
        case(FRONTEND):
            frontend.handleClick();
            state = INGAME;
            break;
        case(INGAME):
            game.handlePlayerClick(x,y);
            break;
        case(GAMEOVERWIN):
            break;
        case(GAMEOVERLOSE):
            break;
    }
    

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
