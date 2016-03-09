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

class GameOver
{
private:
    
protected:
    ofImage* background;
    ofTrueTypeFont dispFont;

public:
    GameOver(shared_ptr<ImageBank> _imgBank);
    virtual void display();
};

class GameOverWin: public GameOver
{
public:
    GameOverWin(shared_ptr<ImageBank> _imgBank);
    void display();
};

class GameOverLose: public GameOver
{
public:
    GameOverLose(shared_ptr<ImageBank> _imgBank);
    void display();
};

#endif /* GameOver_hpp */
