//
//  GamePiece.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#ifndef GamePiece_hpp
#define GamePiece_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ImageBank.hpp"
#include "Player.hpp"

class Player;
enum class PieceType { CHICK, ELEPHANT, GIRAFFE, LION, HEN, BLANK };

class GamePiece
{
private:
    ofImage* dispImage;
    
protected:
    int x;
    int y;
    PieceType type;
    Player* owner;
    
    GamePiece(int x, int y, Player* _owner);
    
    void setDisplayImage(string path, shared_ptr<ImageBank> imgBank);
    
    
public:

    virtual bool canMove(int newX, int newY) = 0;
    virtual shared_ptr<GamePiece> clone() = 0;
    void moveTo(int x, int y);
    int getX(){ return x;};
    int getY(){ return y;};
    PieceType getType(){ return type;};
    Player* getOwner(){ return owner;};

    void drawPiece(int xOffset, int w, int yOffset, int h);
};

typedef shared_ptr<GamePiece> GamePiecePtr;

#endif /* GamePiece_hpp */
