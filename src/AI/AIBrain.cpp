//
//  AIBrain.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 01/03/2016.
//
//

#include "AIBrain.hpp"
#include <math.h>

AIBrain::AIBrain(){};

void AIBrain::playOutGameWith(Lookahead& current)
{
    current.randomPlayOut();
}

Lookahead AIBrain::getNextMove(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2)
{
    cout << "----- MAKING MOVE -----" << endl;

    Lookahead currentState = Lookahead(gameBoard, p1, p2);
    
    vector<Lookahead> potentialMoves = currentState.getChildren();

    int totalItters = 500;
    int nodesExplored = 0;
    
    while(nodesExplored < totalItters){
        nodesExplored++;
        cout << "Loop: " << nodesExplored << endl;
        //Increment the number of nodes explored
        
        
        //Find the best child node
        float bestScore = -1;
        int bestIndex = -1;
        cout << "Level 0" << endl;
        for(int i = 0; i < potentialMoves.size(); i++){
            cout << "Node " << i << endl;
            float constant = 1.0;
            float losses = potentialMoves[i].getLosses();
            float wins = potentialMoves[i].getWins();
            
            float exploreRating = constant + sqrt(log(nodesExplored)/(losses+wins+0.1));
            float score = 1.0;
            if (losses+wins > 0)
                score = wins/(losses+wins);
            float totalScore = score+exploreRating;
            cout << "Wins " << wins << " Losses " << losses << " Explore rating " << exploreRating << " Total " << totalScore << " Current Best Score " << bestScore << endl;
            if (totalScore > bestScore){
                bestScore = totalScore;
                bestIndex = i;
            }
            cout << endl;
        }
        cout << "Chosen node " << bestIndex << endl;
        Lookahead* bestChild;
        bestChild = &potentialMoves[bestIndex];
        
        //Then find the best child of that node (and subseqent nodes)
        while(bestChild->getNumbChildren() > 0)
        {
            bestScore = -1;
            bestIndex = -1;
            for(int i = 0; i < bestChild->getNumbChildren(); i++){
                float constant = 1.0;
                float losses = bestChild->getChildren()[i].getLosses();
                float wins = bestChild->getChildren()[i].getWins();
                
                float exploreRating = constant + sqrt(log(nodesExplored)/(losses+wins+0.1));
                float score = 1.0;
                if (losses+wins > 0)
                    score = wins/(losses+wins);
                float totalScore = score+exploreRating;
                if (totalScore > bestScore){
                    bestScore = totalScore;
                    bestIndex = i;
                }
            }
            bestChild = &bestChild->getChildren()[bestIndex];
            assert(bestScore!=-1);
            assert(bestIndex!=-1);
        }
        
        assert(bestScore!=-1);
        assert(bestIndex!=-1);
        
        //Once we have found the best move we generate it's children
        assert(bestChild->getParent());
        vector<Lookahead> generatedMoves = bestChild->generateChildren();
        //bestChild->generateChildren();
        bestChild->setChildren(generatedMoves);
        //And experiement with them
        vector<std::thread> playOutThreads;
        for (auto& child : generatedMoves){
            playOutThreads.push_back(std::thread( &AIBrain::playOutGameWith, this, std::ref(child)));
        }
        for (auto &thread : playOutThreads)
        {
            thread.join();
        }
    }

    int bestScore = -1;
    int bestIndex = -1;
    for(int i = 0; i < potentialMoves.size(); i++)
    {
        float losses = potentialMoves[i].getLosses();
        float wins = potentialMoves[i].getWins();
        float score = 100*(wins/(losses+wins));
        cout << i << " th move played: " << losses+wins << endl;
        //cout << i << " th move win: " << wins << endl;
        cout << i << " th move scores: " << score << endl;
        score = losses+wins;
        if(score > bestScore)
        {
            bestScore = score;
            bestIndex = i;
        }
    }
    cout << "Chosen move: " << bestIndex;
    cout << " States Played = " << currentState.getNumbCompletedGames() << " Losses = " << currentState.getLosses() << " Wins = " << currentState.getWins() << endl;
    return potentialMoves[bestIndex];
}