//
//  ElephantPiece.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 08/03/2016.
//
//

#ifndef ElephantPiece_hpp
#define ElephantPiece_hpp

#include <stdio.h>
#include "GamePiece.hpp"

class ElephantPiece: public GamePiece
{
public:
    ElephantPiece(int x, int y, Player* _owner, shared_ptr<ImageBank> imgBank = NULL);
    //No copy constructor because we want default behaviour and cannot redefine the implict copy constuctor. 
    virtual ~ElephantPiece();
    virtual bool canMove(int newX, int newY);
    virtual shared_ptr<GamePiece> clone();
};

#endif /* ElephantPiece_hpp */
