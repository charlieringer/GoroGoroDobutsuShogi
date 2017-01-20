//
//  Game.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 15/02/2016.
//
//

#ifndef Game_hpp
#define Game_hpp
#include <stdio.h>
#include <vector>
using namespace std;

#include "GiraffePiece.hpp"
#include "LionPiece.hpp"
#include "ElephantPiece.hpp"
#include "BlankPiece.hpp"
#include "ChickPiece.hpp"
#include "HenPiece.hpp"
#include "AIBrain.hpp"
#include "GameState.hpp"


class Game: public GameState
{
private:
    
    ofImage* background;
    ofImage* gameBackground;
    vector<GamePiecePtr> gameboard;
    GamePiecePtr playerSelectedPiece;
    shared_ptr<ImageBank> imgBank;
    HumanPlayer* player;
    AIPlayer* ai;
    AIBrain* brain;
    int pieceWidth;
    int pieceHeight;
    int xOffset;
    int yOffset;
    ofTrueTypeFont dispFont;
    bool aiStarted = false;
    bool firstMove = true;
    
    void movePiece(GamePiecePtr selectedPiece, int x, int y);
    void promotePiece(GamePiecePtr piece);
    bool handleDroppedPiece(int x,int y);
    bool playersTurn;
    bool lost = false;
    bool simulation = false;
    void reset();
    void checkEnd();
    void takeAITurn();
    void resetLoss();
    
public:
    Game(shared_ptr<ImageBank> _imgBank);
    Game(const Game& other);
    virtual ~Game();
    
    virtual void update();
    virtual void draw();
    virtual void handleClick(int x, int y);
};

#endif /* Game_hpp */
