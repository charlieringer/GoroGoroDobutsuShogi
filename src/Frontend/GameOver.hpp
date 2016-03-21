//
//  GameOver.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 28/02/2016.
//
//

#ifndef GameOver_hpp
#define GameOver_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ImageBank.hpp"
#include "GameState.hpp"
#include "Button.hpp"

class GameOver: public GameState
{
private:
    Button playAgain;
    Button mainMenu;
    ofImage* background;
    
protected:
    ofTrueTypeFont dispFont;

public:
    GameOver(shared_ptr<ImageBank>& _imgBank);
    GameOver( const GameOver& other);
    virtual ~GameOver();
    virtual void draw();
    virtual void handleClick(int x, int y);
};

class GameOverWin: public GameOver
{
public:
    GameOverWin(shared_ptr<ImageBank>& _imgBank);
    GameOverWin( const GameOverWin& other);
    virtual ~GameOverWin();
    virtual void update(){};
    virtual void draw();
    
};

class GameOverLose: public GameOver
{
public:
    GameOverLose(shared_ptr<ImageBank>& _imgBank);
    GameOverLose( const GameOverLose& other);
    virtual ~GameOverLose();
    virtual void update(){};
    virtual void draw();
};

#endif /* GameOver_hpp */
