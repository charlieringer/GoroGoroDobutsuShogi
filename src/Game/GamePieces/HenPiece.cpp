
//
//  HenPiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#include "HenPiece.hpp"

HenPiece::HenPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank ): GamePiece(x,y,_owner)
{
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("hen2.png", imgBank);
        else setDisplayImage("hen2.png", imgBank);
    }
    type = PieceType::HEN;
}

bool HenPiece::canMove(int newX, int newY)
{
    if (((newY == y+1 && newX == x)
         || (newY == y-1 && newX == x)
         || (newX == x+1 && newY == y)
         || (newX == x-1 && newY == y))
        && newX >= 0 && newX < 3
        && newY >= 0 && newY < 4)
    {
        return true;
    }
    
    if(owner->isAI())
    {
        if ((newX == x-1 || newX ==x+1) && newY ==y+1
            && newX >= 0 && newX < 3
            && newY >= 0 && newY < 4)
        {
            return true;
        }
    } else {
        if (((newX == x-1 || newX ==x+1) && newY ==y-1
             && newX >= 0 && newX < 3
             && newY >= 0 && newY < 4))
        {
            return true;
        }
    }
    return false;
}

shared_ptr<GamePiece> HenPiece::clone()
{
    return make_shared<HenPiece>(*this);
}