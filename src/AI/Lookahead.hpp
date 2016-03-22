//
//  Move.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 01/03/2016.
//
//

#ifndef Lookahead_hpp
#define Lookahead_hpp

#include <stdio.h>
#include "GamePiece.hpp"

class Lookahead
{
private:
    //The game board and 2 players represent the game
    vector<GamePiecePtr> gameboard;
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    //Any lookaheads that follow moves from this node
    vector<Lookahead> children;
    //Parent node
    Lookahead* parent;
    //Number of wins, losses and games played
    float wins = 0;
    float losses = 0;
    int games = 0;
    int draws = 0;
    //How deep in the look ahead this is
    int depthLevel;
    //And wheather this end state represents an end game
    bool isTerminal;
    //
    vector<GamePiecePtr> copyGameBoard(vector<GamePiecePtr> initalBoard, shared_ptr<Player> p1, shared_ptr<Player> p2);
    void simulateDroppedPiece(vector<GamePiecePtr> &board, GamePiecePtr piece, shared_ptr<Player> owner, int x,int y);
    void simulatePromotion(vector<GamePiecePtr> &board, GamePiecePtr piece, shared_ptr<Player> owner);
    bool checkTerminality();

public:
    Lookahead(){};
    Lookahead(vector<GamePiecePtr>& _gameboard, shared_ptr<Player> _player1, shared_ptr<Player> _player2, Lookahead* _parent, int _depthLevel);
    Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2);
    Lookahead(const Lookahead& other);
    ~Lookahead();
    
    //Generic getters
    bool terminal(){ return isTerminal;};
    int getNumbCompletedGames(){ return games;};
    float getWins(){ return wins;};
    float getLosses( ){return losses;};
    int getNumbChildren(){ return children.size();};
    int getDepth(){ return depthLevel;};
    Lookahead* getParent(){ return parent;};
    int getDraws(){return draws;};
    
    //Used when copying the game state back to the real game
    shared_ptr<Player> getPlayer1(){ return player1;};
    shared_ptr<Player> getPlayer2(){ return player2;};
    vector<GamePiecePtr> getBoard(){ return gameboard;};
    
   
    
    void addWin(float winAmount)
    {
        //A win for this node is a loss for the parent
        wins+=winAmount;
        games++;
        if (parent)
            parent->addLoss(winAmount);
    }
    
    void addLoss(float lossAmount)
    {
        //A loss for this node is a win for the parent
        losses+=lossAmount;
        games++;
        if (parent)
            parent->addWin(lossAmount);
    }
    
    void addDraw(float drawScore)
    {
        games++;
        draws++;
        wins+=drawScore;
        if (parent)
            parent->addDraw(drawScore);
        
    }
    
    void addGame(){ games++;}
    
    //This is for making, getting and setting the possible moves from this node
    vector<Lookahead> generateChildren();
    vector<Lookahead>& getChildren(){ return children;};
    void setChildren(vector<Lookahead> _children){children = _children;};
};
#endif /* Move_hpp */
