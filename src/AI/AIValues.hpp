//
//  AIValues.hpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 17/03/2016.
//
//

#ifndef AIValues_hpp
#define AIValues_hpp

#include <stdio.h>

class AIValues
{
private:
    static int numbItters;
    static float exploreConst;
    
public:
    static int getNumIterations(){ return numbItters;};
    static float getExploreConstant(){ return exploreConst;};
    
    static void setNumIterations(int newItters){ numbItters = newItters;};
    static void setExploreConstant(float newConst){ exploreConst = newConst;};
    
    static void incrementNumIterations(){ if(numbItters< 1500) numbItters+=50;}
    static void incrementExploreConstant(){ if(exploreConst < 5) exploreConst+=0.5;}
    
    static void decrementNumIterations(){ if (numbItters >50) numbItters-=50;}
    static void decrementExploreConstant(){ if (exploreConst> 0.5) exploreConst-=0.5;}
    
};
#endif /* AIValues_hpp */
