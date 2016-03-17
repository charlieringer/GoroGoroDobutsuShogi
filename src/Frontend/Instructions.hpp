//
//  Instructions.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 17/03/2016.
//
//

#ifndef Instructions_hpp
#define Instructions_hpp

#include <stdio.h>
#include "GameState.hpp"
#include "ImageBank.hpp"
#include "Button.hpp"

class Instructions: public GameState
{
private:
    ofImage* background;
    Button title;
    Button back;
    ofTrueTypeFont dispFont;
    
public:
    Instructions(shared_ptr<ImageBank> imgBank);
    virtual void update(){};
    virtual void draw();
    virtual void handleClick(int x, int y);
};

#endif /* Instructions_hpp */
