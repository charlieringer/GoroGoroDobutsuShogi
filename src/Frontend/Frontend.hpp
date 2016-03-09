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


class Frontend
{
private:
    ofImage* background;
    ofImage* title;
    ofImage* playbutton;
    shared_ptr<ImageBank> imgBank;
    State* state;
    
public:
    Frontend(State& _state, shared_ptr<ImageBank> _imgBank);
    Frontend( const Frontend& other);
    void drawFrontend();
    void handleClick();
};

#endif /* Frontend_hpp */
