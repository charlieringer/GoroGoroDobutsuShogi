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
    
    cout << "States Played = " << currentState.getNumbCompletedGames() << " Losses = " << currentState.getLosses() << " Wins = " << currentState.getWins() << endl;
    int indexOfBest = -1;
    
    vector<Lookahead> potentialMoves = currentState.getChildren();
    for(int i = 0; i < potentialMoves.size(); i++)
    {
        float losses = potentialMoves[i].getLosses();
        float wins = potentialMoves[i].getWins();
        float score = 100*(wins/(losses+wins));
        cout << i << " th move losses: " << losses << endl;
        cout << i << " th move win: " << wins << endl;
        cout << i << " th move scores: " << score << endl;
    }
    cout << "Stop";
}