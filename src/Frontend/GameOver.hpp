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

class GameOver: public GameState
{
private:
    
protected:
    ofImage* background;
    ofTrueTypeFont dispFont;

public:
    GameOver(shared_ptr<ImageBank> _imgBank);
   // virtual void draw() = 0;
};

class GameOverWin: public GameOver
{
public:
    GameOverWin(shared_ptr<ImageBank> _imgBank);
    virtual void update(){};
    virtual void draw();
    virtual void handleClick(int x, int y){};
};

class GameOverLose: public GameOver
{
public:
    GameOverLose(shared_ptr<ImageBank> _imgBank);
    virtual void update(){};
    virtual void draw();
    virtual void handleClick(int x, int y){};
};

#endif /* GameOver_hpp */
