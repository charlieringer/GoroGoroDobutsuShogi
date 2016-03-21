//
//  ChickPiece.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#ifndef ChickPiece_hpp
#define ChickPiece_hpp

#include <stdio.h>
#include "GamePiece.hpp"


class ChickPiece: public GamePiece
{
public:
    ChickPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank = NULL);
    ChickPiece(const ChickPiece& other);
    virtual ~ChickPiece();
    
    virtual bool canMove(int newX, int newY);
    virtual shared_ptr<GamePiece> clone();
};

#endif /* ChickPiece_hpp */
