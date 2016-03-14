

//
//  ChickPiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#include "ChickPiece.hpp"

ChickPiece::ChickPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank ): GamePiece(x,y,_owner)
{
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics)
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("ChickAI.png", imgBank);
        else setDisplayImage("ChickPlayer.png", imgBank);
    }
    type = PieceType::CHICK;
}

bool ChickPiece::canMove(int newX, int newY)
{
    //Chicks can only move forward
    if(owner->isAI())
    {
        if (newY == y+1 && newY < 4 && newY!=y && newX == x )
        {
            return true;
        }
    } else {
        if (newY == y-1 && newY >= 0 && newY!=y && newX == x)
        {
            return true;
        }
    }
    return false;
}

 shared_ptr<GamePiece> ChickPiece::clone()
{
    //This just copies the piece and returns it as a GamePiece (not ChickPiece). Needed for the AI because we need
    //to be able to get GamePiece Ptrs during lookahead.
    return make_shared<ChickPiece>(*this);
}