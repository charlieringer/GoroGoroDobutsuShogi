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
    if (imgBank != NULL)
    {
        if(_owner->isAI()) setDisplayImage("GiraffeAI.png", imgBank);
        else setDisplayImage("GiraffePlayer.png", imgBank);
    }
    type = PieceType::GIRAFFE;
}

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
    return make_shared<GiraffePiece>(*this);
}