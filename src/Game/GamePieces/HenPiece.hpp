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
    HenPiece(const HenPiece& other);
    virtual ~HenPiece();
    //No copy constructor because we want default behaviour as cannot redefine the implict copy constuctor.
    virtual bool canMove(int newX, int newY);
    virtual shared_ptr<GamePiece> clone();
};

#endif /* HenPiece_hpp */
