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
    
public:
    AIBrain();
    Lookahead getNextMove(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    void playOutGameWith(Lookahead& current);
};

#endif /* AIBrain_hpp */
