//
//  LionPiece.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#ifndef LionPiece_hpp
#define LionPiece_hpp

#include <stdio.h>
#include "GamePiece.hpp"

class LionPiece: public GamePiece
{
public:
    LionPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank = NULL);
    virtual bool canMove(int newX, int newY);
    virtual shared_ptr<GamePiece> clone();
};

#endif /* LionPiece_hpp */
