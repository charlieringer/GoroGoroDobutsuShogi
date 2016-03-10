//
//  AIBrain.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 01/03/2016.
//
//

#ifndef AIBrain_hpp
#define AIBrain_hpp

#include <stdio.h>
#include <vector>
#include "Player.hpp"
#include "Lookahead.hpp"

class AIBrain
{
private:
    //Lookahead currentState;
    
public:
    AIBrain();
    void getNextMove(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
};

#endif /* AIBrain_hpp */
