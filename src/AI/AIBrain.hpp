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
    bool threadDone;
    bool aiStarted;
    Lookahead nextMove;
    
    Lookahead mcts(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    void startMCTS(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    void randomPlayOut(Lookahead* playOutNode);
    
public:
    AIBrain();
    AIBrain(const AIBrain& other);
    ~AIBrain();
    
    void startAI(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2);
    Lookahead getMoveandReset(){
        //reset thread
        delete aiThread;
        aiThread = nullptr;
        //And return next move
        return nextMove;
    };
    bool hasNextMove(){ return threadDone;};
    bool started(){ return aiStarted;};
    void reset();
};

#endif /* AIBrain_hpp */
