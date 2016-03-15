//
//  Frontend.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 23/02/2016.
//
//

#ifndef Frontend_hpp
#define Frontend_hpp

#include <stdio.h>
#include "ImageBank.hpp"
#include "State.hpp"
#include "Button.hpp"
#include "GameState.hpp"

class Frontend: public GameState
{
private:
    ofImage* background;
    Button title;
    Button play;
    shared_ptr<ImageBank> imgBank;
    
public:
    Frontend(shared_ptr<ImageBank> _imgBank);
    Frontend( const Frontend& other);
    virtual void update(){};
    virtual void draw();
    virtual void handleClick(int x, int y);
};

#endif /* Frontend_hpp */
