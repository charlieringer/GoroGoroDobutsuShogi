//
//  GamePiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#include "GamePiece.hpp"

GamePiece::GamePiece(int _x, int _y, Player* _owner = NULL): x(_x), y(_y), owner(_owner){}
GamePiece::GamePiece(const GamePiece& other): x(other.x), y(other.y), owner(other.owner), dispImage(other.dispImage){}
GamePiece::~GamePiece(){}


void GamePiece::setDisplayImage(string path, shared_ptr<ImageBank> imgBank)
{
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics)
   if (imgBank)
        dispImage = imgBank->loadImage(path);
}

void GamePiece::moveTo(int newX, int newY)
{
    //Literally just moves the piece. Use in conjunction with CanMove which finds a legal move
    x = newX;
    y= newY;
}

//Draws rhe game piece (
void GamePiece::drawPiece(int xOffset, int w, int yOffset, int h)
{
    //ofDrawRectangle(ofRectangle(xOffset+(x*(w)), yOffset+(y*(h)), w, h));
    if (dispImage != nullptr) dispImage->draw(xOffset+(w*x),yOffset+(h*y));
    ofSetColor(0, 0, 0);
    ofNoFill();
    ofDrawRectangle(ofRectangle(xOffset+x*(w), yOffset+y*(h), w, h));
    ofFill();
    ofSetColor(255, 255, 255);
}














