//
//  BlankPiece.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#include "BlankPiece.hpp"

BlankPiece::BlankPiece(int x, int y, shared_ptr<ImageBank> imgBank, Player* _owner ): GamePiece(x,y,_owner)
{
    if (imgBank)
        setDisplayImage("Blank.png", imgBank);
    
    type = PieceType::BLANK;
}


bool BlankPiece::canMove(int newX, int newY)
{
    assert(true);
    return false;
}

shared_ptr<GamePiece> BlankPiece::clone()
{
   return make_shared<BlankPiece>(*this);
}
