//
//  Button.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 27/02/2016.
//
//

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include "ofMain.h"

class Button
{
private:
    int x;
    int y;
    ofImage* dispImage;
public:
    bool clicked();
    
};

#endif /* Button_hpp */
