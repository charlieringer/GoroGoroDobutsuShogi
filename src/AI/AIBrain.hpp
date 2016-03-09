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
    vector<GamePiecePtr> gameboard;
    Player player1;
    Player player2;
    Lookahead currentState;
    
public:
    void getNextMove();
};

#endif /* AIBrain_hpp */
