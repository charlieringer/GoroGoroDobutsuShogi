//
//  AIBrain.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 01/03/2016.
//
//

#include "AIBrain.hpp"

AIBrain::AIBrain(){};

void AIBrain::getNextMove(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2)
{
    Lookahead currentState = Lookahead(gameBoard, p1, p2);
    
    cout << "States Played = " << currentState.getNumbCompletedGames() << " Loses = " << currentState.getLoses() << " Wins = " << currentState.getWins() << endl;
    cout << "Stop";
}