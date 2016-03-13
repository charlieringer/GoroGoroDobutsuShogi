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
    Player* player1;
    Player* player2;
    vector<Lookahead> children;
    Lookahead* parent;
    int wins = 0;
    int losses = 0;
    int games = 0;
    int depthLevel;
    bool isTerminal;
    
    vector<GamePiecePtr> copyGameBoard(vector<GamePiecePtr> initalBoard, Player* p1, Player* p2);
    void simulateDroppedPiece(vector<GamePiecePtr> &board, GamePiecePtr piece, Player* owner, int x,int y);
    void simulatePromotion(vector<GamePiecePtr> &board, GamePiecePtr piece, Player* owner);
    
    void addWin()
    {
        wins++;
        games++;
        if (parent)
            parent->addLoss();
    }
    void addLoss()
    {
        losses++;
        games++;
        if (parent)
            parent->addWin();
    }
    
    
public:
    Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2, Lookahead* _parent, int _depthLevel);
    Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2);
    ~Lookahead();
    
    bool terminal(){ return isTerminal;};
    bool checkTerminality();
    int getNumbCompletedGames(){ return games;};
    int getWins(){ return wins;};
    int getLosses( ){return losses;};
    int getNumbChildren(){ return children.size();};
    int getDepth(){ return depthLevel;};
    Player* getPlayer1(){ return player1;};
    Player* getPlayer2(){ return player2;};
    vector<GamePiecePtr> getBoard(){ return gameboard;};
    Lookahead* getParent(){ return parent;};
    
    void randomPlayOut();
    vector<Lookahead> generateChildren();
    vector<Lookahead>& getChildren(){ return children;};
    void setChildren(vector<Lookahead> _children){children = _children;};
    void playOutNGames(int n);
};
#endif /* Move_hpp */
