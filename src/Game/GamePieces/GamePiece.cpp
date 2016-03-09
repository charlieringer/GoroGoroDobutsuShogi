//
//  GamePiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#include "GamePiece.hpp"

GamePiece::GamePiece(int _x, int _y, Player* _owner = NULL): x(_x), y(_y), owner(_owner){}


void GamePiece::setDisplayImage(string path, shared_ptr<ImageBank> imgBank)
{
    dispImage = imgBank->loadImage(path);
}

bool GamePiece::canMove(int newX, int newY){}

void GamePiece::moveTo(int newX, int newY)
{
    x = newX;
    y= newY;
}

void GamePiece::drawPiece(int xOffset, int w, int yOffset, int h)
{
    ofDrawRectangle(ofRectangle(xOffset+(x*(w)), yOffset+(y*(h)), w, h));
    if (dispImage != NULL) dispImage->draw(xOffset+(w*x),yOffset+(h*y));
    ofSetColor(0, 0, 0);
    ofNoFill();
    ofDrawRectangle(ofRectangle(xOffset+x*(w), yOffset+y*(h), 80, 80));
    ofFill();
    ofSetColor(255, 255, 255);
}














