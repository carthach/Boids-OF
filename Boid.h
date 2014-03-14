//
//  Boid.h
//  myBoids1
//
//  Created by Cárthach Ó Nuanáin on 21/01/2014.
//
//

#ifndef __myBoids1__Boid__
#define __myBoids1__Boid__

#include "ofMain.h"
#include <iostream>

#endif /* defined(__myBoids1__Boid__) */

class Boid
{
public:
    Boid();
    Boid(ofVec2f position, ofVec2f velocity, ofColor color);
    
    ofVec2f position;
    ofVec2f velocity;
    void update(vector<Boid>& boids);
    void draw();

private:
    //TWEAKS
    static const float SEEDVELOCITY = 5.0f;
    static const float RADIUS = 5.0f;
    static const float MAXVELOCITY = 8.0f;
    static const float MIN_DISTANCE = 8.0f; //8.0f
    static const int ANIMATECOUNTERMAX = 20;
    
    ofVec2f flock(vector<Boid>& boids);
    ofVec2f separate(vector<Boid>& boids);
    ofVec2f align(vector<Boid>& boids);
    
    ofVec2f avgPosOfOthers;
    ofVec2f avgVelOfOthers;
    
    bool animateCounterIncreasing;
    int animateCounter;
    
    void clampPosition();
    void clampVelocity();
    
    ofVec2f absVec2f(ofVec2f theVector);
    ofColor color;
};