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
    thread* aiThread;
    bool threadDone = false;
    bool aiStarted;
    Lookahead nextMove;
    void playOutGameWith(Lookahead& current);
    Lookahead mcts(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    void getNextMoveFromMCTS(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    
public:
    AIBrain();
    ~AIBrain();
    void startAI(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    Lookahead getMoveandReset(){
        aiStarted = false;
        return nextMove;
    };
    bool hasNextMove(){ return threadDone;};
    bool started(){ return aiStarted;};
};



#endif /* AIBrain_hpp */
