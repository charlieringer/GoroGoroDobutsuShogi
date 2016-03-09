
//
//  ElephantPiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#include "ElephantPiece.hpp"

ElephantPiece::ElephantPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank ): GamePiece(x,y,_owner)
{
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("ElephantAI.png", imgBank);
        else setDisplayImage("ElephantPlayer.png", imgBank);
    }
    type = PieceType::ELEPHANT;
}

bool ElephantPiece::canMove(int newX, int newY)
{
    if ((newX == x-1 || newX ==x+1) && (newY == y-1 || newY ==y+1)
        && newX >= 0 && newX < 3
        && newY >= 0 && newY < 4)
        return true;
    return false;
}

shared_ptr<GamePiece> ElephantPiece::clone()
{
    return make_shared<ElephantPiece>(*this);
}