//
//  BlankPiece.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#ifndef BlankPiece_hpp
#define BlankPiece_hpp

#include <stdio.h>
#include "GamePiece.hpp"

class BlankPiece: public GamePiece
{
public:
    BlankPiece(int x, int y, shared_ptr<ImageBank> imgBank = NULL, Player* _owner = NULL);
    //No copy constructor because we want default behaviour as cannot redefine the implict copy constuctor.
    virtual ~BlankPiece();
    virtual bool canMove(int newX, int newY);
    virtual shared_ptr<GamePiece> clone();
};

#endif /* BlankPiece_hpp */
