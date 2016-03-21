//
//  ImageBank.cpp
//  papTermTwoCourseWork
//
//  Created by Charles Ringer on 06/11/2015.
//
//

#include "ImageBank.hpp"

//This class handles all of my images so that they do not get loaded multiple times.
ImageBank::ImageBank(){}

//Copy constructor
ImageBank::ImageBank(const ImageBank& other): images(other.images){}


ImageBank::~ImageBank()
{
    //Deletes all of the images in the image bank
    for(auto image: images)
    {
        delete image.second;
    }
}

//The funcion loads and image and returns a pointer to that image
ofImage* ImageBank::loadImage(string imgPath)
{
    //This checks to make sure we have not loaded the image already
    if(images.find(imgPath) == images.end())
    {
        //We create a new image
        ofImage *newImage = new ofImage();
        //Load it
        bool loaded = newImage->loadImage(imgPath);
        //Things go wrong if the image failed to load so assert that it did.
        assert(loaded);
        //Map the new image
        images[imgPath] = newImage;
        //And return a pointer to it
        return (images[imgPath]);
    }
    else
    {
        //Already loaded so just return the pointer
        return (images[imgPath]);
    }
}