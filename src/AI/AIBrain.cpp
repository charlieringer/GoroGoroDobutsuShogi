//
//  AIBrain.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 01/03/2016.
//
//

#include "AIBrain.hpp"
#include <math.h>
#include "AIValues.hpp"

AIBrain::AIBrain():threadDone(false), aiStarted(false){}

AIBrain::~AIBrain()
{
    delete aiThread;
}

void AIBrain::startAI(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2)
{
    //We set the thread to a new thread starting a MCTS search
    aiThread = new std::thread(&AIBrain::startMCTS, this, std::ref(gameBoard), p1, p2);
    //And detach this thread so it can work on it's own
   // aiThread->detach();
}

void AIBrain::startMCTS(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2)
{
    //threadDone is just a flag that is set when we are done with the AI
    //(as it is on a different thread so we need to be told when it is don).
    threadDone = false;
    //We set the nextMove (which is what the main game gets hold of) to the result of a Monte Carlo Tree Search
    nextMove = mcts(gameBoard, p1, p2);
    threadDone = true;

}

Lookahead AIBrain::mcts(vector<GamePiecePtr>& gameBoard, Player* p1, Player* p2)
{
    Lookahead currentState = Lookahead(gameBoard, p1, p2);
    //This is just safety code if the AI tried to make a move before the state has changed but the game is over.
    if (currentState.terminal()) return currentState;
    
    cout << "----- MAKING MOVE -----" << endl;
    
    //These are our availaible moves
    vector<Lookahead> potentialMoves = currentState.getChildren();

    //These are set elsewhere as they are our AI parameters
    int totalItters = AIValues::getNumIterations();
    float exploreConst = AIValues::getExploreConstant();
    
    //Whilst we have not played enough games...
    int loopCounter = 1;
    while(currentState.getNumbCompletedGames() < totalItters){
        cout << "Loop: " << loopCounter << endl;
        loopCounter++;
        
        //Find the best child node
        float bestScore = -1;
        int bestIndex = -1;
        cout << "Level 0" << " ";
        //First we find the most promising of our potential moves
        for(int i = 0; i < potentialMoves.size(); i++){
            //This is a early escape if any of the potential moves are terminal.
            //If they are terminal then we have a win for the AI
            if (potentialMoves[i].terminal())
                return potentialMoves[i];
            
            //These are some scores we use for working out how good a move is
            float losses = potentialMoves[i].getLosses();
            float wins = potentialMoves[i].getWins();
            int games = potentialMoves[i].getNumbCompletedGames();
            
            //UBT (Upper Confidence Bound 1 applied to trees) function for determining
            //How much we want to explore vs exploit.
            //Because we want to change things the constant is configurable.
            float exploreRating = exploreConst*sqrt(2*(log(currentState.getNumbCompletedGames()+1)/(games+0.1)));
            //Win score starts at 100% for unexplored nodes
            float winScore = 1.0;
            //But we set it correctly if the node has been played
            if (games > 0) winScore = wins/games;
            
            float totalScore = winScore+exploreRating;

            //if we have a better score
            if (totalScore > bestScore){
                //We update the score and where it came from
                bestScore = totalScore;
                bestIndex = i;
            }
        }
        //Then it is time to find the best node further along the tree
        //This needs to be a pointer because it will jump around the place into different places as we go deep into the lookahead
        Lookahead* bestChild;
        bestChild = &potentialMoves[bestIndex];
        
        cout << "Chosen node " << bestIndex << endl;
        int level = 1;
        //Then find the best child of that node (and subseqent nodes)
        while(bestChild->getNumbChildren() > 0)
        {
            cout << "Level " << level << " ";
            level++;
            //We reset these values
            bestScore = -1;
            bestIndex = -1;
            //We loop through the children trying to find the best one.
            for(int i = 0; i < bestChild->getNumbChildren(); i++){
                //Scores as per the previous part
                float losses = bestChild->getChildren()[i].getLosses();
                float wins = bestChild->getChildren()[i].getWins();
                int games = bestChild->getChildren()[i].getNumbCompletedGames();
                
                //UBT (Upper Confidence Bound 1 applied to trees) function for deterimining
                //How much we want to explore vs exploit.
                //Because we want to change things the constant is configurable.
                float exploreRating = exploreConst*sqrt(2*(log(currentState.getNumbCompletedGames()+1)/(games+0.1)));
                float winScore = 1.0;
                if (games > 0)
                    winScore = wins/games;
                float totalScore = winScore+exploreRating;

                if (totalScore > bestScore){
                    //Updates values
                    bestScore = totalScore;
                    bestIndex = i;
                }
            }
            bestChild = &bestChild->getChildren()[bestIndex];
            cout << "Chosen node " << bestIndex << endl;
        }
        cout << endl;
        assert(bestScore!=-1);
        assert(bestIndex!=-1);
        assert(!(bestChild->getParent()->terminal()));
        //If out best move is one that ends the game e just add a win here
        if (bestChild->terminal()) bestChild->addWin(1);
        //Otherwise we play out with it.
        else randomPlayOut(bestChild);
    }

    //Here we actually work select the move once we have done all of the play outs
    int mostGames = -1;
    int bestIndex = -1;
    for(int i = 0; i < potentialMoves.size(); i++)
    {
        float losses = potentialMoves[i].getLosses();
        float wins = potentialMoves[i].getWins();
        int games = potentialMoves[i].getNumbCompletedGames();
        float score = (wins/games);
        cout << i << " th move played: " << potentialMoves[i].getNumbCompletedGames() << " and scores: " << score << endl;
        //In MCTS moves are selected not by their win% but by how often they were explored hence we selected the most played node
        if(games > mostGames)
        {
            mostGames = games;
            bestIndex = i;
        }
    }
    cout << "Chosen move: " << bestIndex << endl;
    return potentialMoves[bestIndex];
}

void AIBrain::randomPlayOut(Lookahead* playOutNode)
{
    assert(!(playOutNode->terminal()));
    //Otherwise randomly playout till we reach a terminal state
    bool terminalStateFound = false;
    
    //This are the potential moves
    vector<Lookahead> playOutChildren = playOutNode->generateChildren();
    assert(playOutChildren.size() > 0);
    //Of which we are selecting a random one
    int randomIndex = rand()%playOutChildren.size();
    
    //These are the moves we have looked at (so we are going to build a list which will represent the entire played out game)
    vector<Lookahead> evaluatedMoves;
    //We add the first random child to it
    evaluatedMoves.push_back(playOutChildren[randomIndex]);
    
    //While we have not found a terminal state
    while(!terminalStateFound)
    {
        //If the last move we did is terminal
        if(evaluatedMoves[evaluatedMoves.size()-1].terminal())
        {
            //We have found a terminal state
            terminalStateFound = true;
            
            //If there was a even number of moves that means that the player who made this move also made the winning move
            if(evaluatedMoves.size()%2 == 0) playOutNode->addWin(1);
            //Otherwise that player lost
            else playOutNode->addLoss(1);
            
        } else {
            //We only want to look so far, this is 16 plies (or 8 moves for each person). Chosen arbitrarily.
            //If we get this far we just record it as a game but otherwise do nothing.
            if (evaluatedMoves.size() > 16)
            {
                playOutNode->addGame();
                return;
            }
            //Lastly we get a new random move and add it to our moves.
            vector<Lookahead> playOutChildren = evaluatedMoves[evaluatedMoves.size()-1].generateChildren();
            randomIndex = rand()%playOutChildren.size();
            evaluatedMoves.push_back(playOutChildren[randomIndex]);
        }
    }
}