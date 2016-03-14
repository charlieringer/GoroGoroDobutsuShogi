
//
//  LionPiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#include "LionPiece.hpp"

LionPiece::LionPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank ): GamePiece(x,y,_owner)
{
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics)
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("LionAI.png", imgBank);
        else setDisplayImage("LionPlayer.png", imgBank);
    }
    type = PieceType::LION;
    
}

bool LionPiece::canMove(int newX, int newY)
{
    if ((((newY == y+1 && newX == x)|| (newY == y-1 && newX == x)|| (newX == x+1 && newY == y)|| (newX == x-1 && newY == y))
         ||
         ((newX == x-1 || newX ==x+1) && (newY == y-1 || newY ==y+1)))
        && newX >=  0 && newX < 3
        && newY >= 0 && newY < 4)
    {
        return true;
    }
  return false;
}

shared_ptr<GamePiece> LionPiece::clone()
{
    //This just copies the piece and returns it as a GamePiece (not Lion). Needed for the AI because we need
    //to be able to get GamePiece Ptrs during lookahead.
    return make_shared<LionPiece>(*this);
}