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
    //Sometimes the imgBank is null (like in the AI lookahead where we do not bother with graphics
    if (imgBank){}
        //setDisplayImage("Blank.png", imgBank);
    type = PieceType::BLANK;
}

BlankPiece::BlankPiece(const BlankPiece& other): GamePiece(other)
{
    type = PieceType::BLANK;
}

BlankPiece::~BlankPiece(){}


bool BlankPiece::canMove(int newX, int newY)
{
    //Allways assert if we are trying to move a blank piece, this should never happen.
    assert(true);
    return false;
}

shared_ptr<GamePiece> BlankPiece::clone()
{
    //This just copies the piece and returns it as a GamePiece (not BlankPiece). Needed for the AI because we need
    //to be able to get GamePiece Ptrs during lookahead.
   return make_shared<BlankPiece>(*this);
}
