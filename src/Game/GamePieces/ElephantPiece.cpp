
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
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics)
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("Tiles/ElephantAI.png", imgBank);
        else setDisplayImage("Tiles/ElephantPlayer.png", imgBank);
    }
    type = PieceType::ELEPHANT;
}

bool ElephantPiece::canMove(int newX, int newY)
{
    //Elephants move digagonally
    if ((newX == x-1 || newX ==x+1) && (newY == y-1 || newY ==y+1)
        && newX >= 0 && newX < 3
        && newY >= 0 && newY < 4)
        return true;
    return false;
}

shared_ptr<GamePiece> ElephantPiece::clone()
{
    //This just copies the piece and returns it as a GamePiece (not ElephantPiece). Needed for the AI because we need
    //to be able to get GamePiece Ptrs during lookahead.
    return make_shared<ElephantPiece>(*this);
}