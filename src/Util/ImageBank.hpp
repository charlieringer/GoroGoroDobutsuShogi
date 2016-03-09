//
//  ImageBank.hpp
//  papTermOneCourseWork
//
//  Created by Charles Ringer on 06/11/2015.
//
//

#ifndef ImageBank_hpp
#define ImageBank_hpp

#include <stdio.h>
#include <ofMain.h>
#include <map>

class ImageBank
{
private:
    //Map of load paths and images
    std::map <string, ofImage*> images;
    
public:
    ImageBank();
    ~ImageBank();
    //fucntion to load an image and return a pointer to it
    ofImage * loadImage(string imgPath);
};

#endif /* ImageBank_hpp */
