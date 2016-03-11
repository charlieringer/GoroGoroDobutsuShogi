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
    Lookahead* parent = nullptr;
    int wins = 0;
    int losses = 0;
    int depthLevel;
    bool isTerminal;
    
    void generateChildren();
    vector<GamePiecePtr> copyGameBoard(vector<GamePiecePtr> initalBoard, Player* p1, Player* p2);
    void simulateDroppedPiece(vector<GamePiecePtr> &board, GamePiecePtr piece, Player* owner, int x,int y);
    void simulatePromotion(vector<GamePiecePtr> &board, GamePiecePtr piece, Player* owner);
    bool checkTerminality();
    
public:
    Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2, Lookahead* _parent, int _depthLevel);
    Lookahead(vector<GamePiecePtr>& _gameboard, Player* _player1, Player* _player2);
    ~Lookahead();
    
    int getNumbCompletedGames(){ return wins+losses;};
    int getWins(){ return wins;};
    int getLosses( ){return losses;};
    int getNumbChildren(){ return children.size();};
    //float getScore(){ return 100*(wins/(wins+losses));};
    //float getScore(){ return 1;};
    
    void addChildWin(){
        wins++;
        if(parent)
        {
            parent->addChildLose();
        }
    };
    void addChildLose(){
        losses++;
        if(parent)
        {
            parent->addChildWin();
        }
    };
    vector<Lookahead> getChildren(){ return children;};
    
};

#endif /* Move_hpp */
