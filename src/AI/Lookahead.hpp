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
    int wins;
    int loses;
    int depthLevel;
    bool isTerminal;
    
    void generateChildren();
    vector<GamePiecePtr> copyGameBoard(vector<GamePiecePtr> initalBoard);
    vector<GamePiecePtr> simulateMove(vector<GamePiecePtr> board, int index, int x, int y);
    void simulateDroppedPiece(vector<GamePiecePtr> board, int x,int y);
    void simulatePromotion(vector<GamePiecePtr> board, GamePiecePtr piece);
    
    bool checkTerminality();
    
public:
    Lookahead(vector<GamePiecePtr> gameboard, Player* player1, Player* player2, Lookahead* parent, int depthLevel);
    
    int getNumbCompletedGames(){ return wins+loses;};
    int getWins(){ return wins;};
    int getLoses( ){return loses;};
    int getNumbChildren(){ return children.size();};
    float getScore(){return wins/(wins+loses);};
    
    void addChildWin(){ wins++;};
    void addChildLose(){loses++;};
    
};

#endif /* Move_hpp */
