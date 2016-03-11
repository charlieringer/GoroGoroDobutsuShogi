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
    
    vector<Lookahead> potentialMoves = currentState.getChildren();

    for (auto& child : potentialMoves)
    {
        for(int i = 0; i < 50; i++)
        {
            child.randomPlayOutFromHere();
        }
    }
    
    int nodesExplored = 0;
    while(nodesExplored < 100){
        //Increment the number of nodes explored
        nodesExplored++;
        
        //Find the best child node
        int bestScore = -1;
        int bestIndex = -1;
        for(int i = 0; i < potentialMoves.size(); i++){
            float losses = potentialMoves[i].getLosses();
            float wins = potentialMoves[i].getWins();
            float score = 100*(wins/(losses+wins));
            if (score > bestScore){
                bestScore = score;
                bestIndex = i;
            }
        }
        Lookahead* bestChild;
        bestChild = &potentialMoves[bestIndex];
        
        //Then find the best child of that node (and subseqent nodes)
        while(bestChild->getNumbChildren() > 0){
            bestScore = -1;
            bestIndex = -1;
            for(int i = 0; i < bestChild->getNumbChildren(); i++){
                float losses = bestChild->getChildren()[i].getLosses();
                float wins = bestChild->getChildren()[i].getWins();
                float score;
                if(wins == 0 && losses == 0)
                    score = 0.0;
                else
                    score = 100*(wins/(losses+wins));
                if (score > bestScore){
                    bestScore = score;
                    bestIndex = i;
                }
            }
            assert(bestScore!=-1);
            assert(bestIndex!=-1);
            bestChild = &bestChild->getChildren()[bestIndex];
        }
        assert(bestScore!=-1);
        assert(bestIndex!=-1);
        
        //Once we have found the best move we generate it's children
        assert(bestChild->getParent());
        vector<Lookahead> generatedMoves = bestChild->generateChildren();
        bestChild->setChildren(generatedMoves);
        //And experiement with them
        for (auto& child : generatedMoves){
            if (child.checkTerminality())continue;
            for(int i = 0; i < 50; i++){
                child.randomPlayOutFromHere();
            }
        }
    }

    for(int i = 0; i < potentialMoves.size(); i++)
    {
        float losses = potentialMoves[i].getLosses();
        float wins = potentialMoves[i].getWins();
        float score = 100*(wins/(losses+wins));
        cout << i << " th move played: " << losses+wins << endl;
        //cout << i << " th move win: " << wins << endl;
        cout << i << " th move scores: " << score << endl;
    }
    cout << "States Played = " << currentState.getNumbCompletedGames() << " Losses = " << currentState.getLosses() << " Wins = " << currentState.getWins() << endl;
    cout << "Stop";
}