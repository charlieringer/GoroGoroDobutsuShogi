//
//  GiraffePiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#include "GiraffePiece.hpp"

GiraffePiece::GiraffePiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank ): GamePiece(x,y,_owner)
{
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics)
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("Tiles/GiraffeAI.png", imgBank);
        else setDisplayImage("Tiles/GiraffePlayer.png", imgBank);
    }
    type = PieceType::GIRAFFE;
}

GiraffePiece::GiraffePiece(const GiraffePiece& other): GamePiece(other)
{
    type = PieceType::GIRAFFE;
}

GiraffePiece::~GiraffePiece(){}

bool GiraffePiece::canMove(int newX, int newY)
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
    return false;
}

shared_ptr<GamePiece> GiraffePiece::clone()
{
    //This just copies the piece and returns it as a GamePiece (not GiraffePiece). Needed for the AI because we need
    //to be able to get GamePiece Ptrs during lookahead.
    return make_shared<GiraffePiece>(*this);
}