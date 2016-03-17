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
#include "ImageBank.hpp"

class Button
{
private:
    int x;
    int y;
    int h;
    int w;
    string id;
    ofImage* dispImage;
public:
    Button(){};
    ~Button(){};
    Button(int _x, int _y, int _w, int _h, string ident, string imgPath, shared_ptr<ImageBank>& imgBank);
    void draw();
    bool clicked(int mX, int mY);
};

#endif /* Button_hpp */
