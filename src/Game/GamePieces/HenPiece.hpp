//
//  HenPiece.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#ifndef HenPiece_hpp
#define HenPiece_hpp

#include <stdio.h>
#include "GamePiece.hpp"

class HenPiece: public GamePiece
{
public:
    HenPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank = NULL);
    virtual bool canMove(int newX, int newY);
    virtual shared_ptr<GamePiece> clone();
};

#endif /* HenPiece_hpp */
