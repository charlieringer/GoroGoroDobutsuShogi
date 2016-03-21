
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
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics)
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("Tiles/HenAI.png", imgBank);
        else setDisplayImage("Tiles/HenPlayer.png", imgBank);
    }
    type = PieceType::HEN;
}

HenPiece::HenPiece(const HenPiece& other): GamePiece(other)
{
    type = PieceType::HEN;
}

HenPiece::~HenPiece(){}


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
    //This just copies the piece and returns it as a GamePiece (not HenPiece). Needed for the AI because we need
    //to be able to get GamePiece Ptrs during lookahead.
    return make_shared<HenPiece>(*this);
}