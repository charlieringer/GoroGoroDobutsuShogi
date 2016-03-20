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
    vector<GamePiecePtr> gameboard;
    shared_ptr<Player> player1;
    shared_ptr<Player> player2;
    vector<Lookahead> children;
    Lookahead* parent;
    float wins = 0;
    float losses = 0;
    int games = 0;
    int depthLevel;
    bool isTerminal;
    
    vector<GamePiecePtr> copyGameBoard(vector<GamePiecePtr> initalBoard, shared_ptr<Player> p1, shared_ptr<Player> p2);
    void simulateDroppedPiece(vector<GamePiecePtr> &board, GamePiecePtr piece, shared_ptr<Player> owner, int x,int y);
    void simulatePromotion(vector<GamePiecePtr> &board, GamePiecePtr piece, shared_ptr<Player> owner);
    bool checkTerminality();

public:
    Lookahead(){};
    Lookahead(vector<GamePiecePtr>& _gameboard, shared_ptr<Player> _player1, shared_ptr<Player> _player2, Lookahead* _parent, int _depthLevel);
    Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2);
    ~Lookahead();
    
    bool terminal(){ return isTerminal;};
    int getNumbCompletedGames(){ return games;};
    float getWins(){ return wins;};
    float getLosses( ){return losses;};
    int getNumbChildren(){ return children.size();};
    int getDepth(){ return depthLevel;};
    shared_ptr<Player> getPlayer1(){ return player1;};
    shared_ptr<Player> getPlayer2(){ return player2;};
    vector<GamePiecePtr> getBoard(){ return gameboard;};
    Lookahead* getParent(){ return parent;};
    
    void addWin(float winAmount)
    {
        wins+=winAmount;
        games++;
        if (parent)
            parent->addLoss(winAmount);
    }
    
    void addLoss(float lossAmount)
    {
        losses+=lossAmount;
        games++;
        if (parent)
            parent->addWin(lossAmount);
    }
    
    void addGame(){ games++;}
    
    vector<Lookahead> generateChildren();
    vector<Lookahead>& getChildren(){ return children;};
    void setChildren(vector<Lookahead> _children){children = _children;};
};
#endif /* Move_hpp */
