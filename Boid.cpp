//
//  Boid.cpp
//  myBoids1
//
//  Created by Cárthach Ó Nuanáin on 21/01/2014.
//
//

#include "Boid.h"

//Default Constructor - randomise the lot
Boid::Boid()
{
    position = ofVec2f(ofRandom(ofGetWindowWidth()),ofRandom(ofGetWindowHeight()));
    velocity = ofVec2f(ofRandom(SEEDVELOCITY),ofRandom(SEEDVELOCITY));
    color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255),180.0f);
    
    animateCounter = 0;
    animateCounterIncreasing = true;

}
Boid::Boid(ofVec2f position, ofVec2f velocity, ofColor color)
{
    this->position = position;
    this->velocity = velocity;
    this->color = color;
}

void Boid::update(vector<Boid>& boids)
{
    //Get the key changes
    ofVec2f change1 = flock(boids);
    ofVec2f change2 = separate(boids);
    ofVec2f change3 = align(boids);

    //Apply changes
    velocity = velocity + change1 + change2 + change3;
    position = position + velocity;

    //Clamp bounds and speed
    clampPosition();
    clampVelocity();
}

void Boid::clampPosition()
{
    if(position.x >= ofGetWindowWidth())
    {
        position.x = ofGetWindowWidth() - 5.0f;
        velocity.x *= -1.0f;
    }
    if(position.x <= 0.0f)
    {
        position.x = 5.0f;
        velocity.x *= -1.0f;
    }
    if(position.y >= ofGetWindowHeight())
    {
        position.y = ofGetWindowHeight() - 5.0f;
        velocity.y *= -1.0f;
    }
    if(position.y <= 0.0f)
    {
        position.y = 5.0f;
        velocity.y *= -1.0f;
    }
}

void Boid::clampVelocity()
{
    if(abs(velocity.x) >= MAXVELOCITY)
    {
        int signX = (velocity.x < 0) ? -1 : (velocity.x > 0);
        velocity.x = MAXVELOCITY * (float)signX;
    }
    if(abs(velocity.y) >= MAXVELOCITY)
    {
        int signY = (velocity.y < 0) ? -1 : (velocity.y > 0);
        velocity.y = MAXVELOCITY * (float)signY;
    }
}
void Boid::draw()
{
//    ofSetColor(color);
    ofSetColor(50,200);
    ofFill();
    
//DRAW CIRCLES
//    ofCircle(position.x, position.y, RADIUS);
    float theta = atan2(velocity.y, velocity.x);

    
    ofPushMatrix();
    ofTranslate(position.x, position.y);
    

    ofMesh quad;
    
    // first triangle
    quad.addVertex(ofVec3f(0, 0, 1));
    quad.addVertex(ofVec3f(0, 20, 1));
    quad.addVertex(ofVec3f(-20-animateCounter, 25 + animateCounter, 1));
    
    quad.addVertex(ofVec3f(0, 0, 1));
    quad.addVertex(ofVec3f(0, 20, 1));
    quad.addVertex(ofVec3f(20+animateCounter, 25+animateCounter, 1));

    ofRotate(ofRadToDeg(theta) + 90);
    quad.draw(); // now you'll see a square
    ofPopMatrix();
    

    if(animateCounter<=ANIMATECOUNTERMAX && animateCounterIncreasing){
        animateCounter++;
        
        if(animateCounter == ANIMATECOUNTERMAX)
            animateCounterIncreasing = false;
    }
    else{
        animateCounter--;
        
        if(animateCounter == 0)
            animateCounterIncreasing = true;
    }
}

/*
 Flock towards the average position of the others
 */

ofVec2f Boid::flock(vector<Boid>& boids)
{
    ofVec2f sumOfPosOfOthers;
    int n = 0;
    
    for(int i=0; i<boids.size(); i++)
    {
        if (&boids[i] != this)
        {
            sumOfPosOfOthers += boids[i].position;
            n++;
        }
    }
     avgPosOfOthers = (sumOfPosOfOthers) / (float)n;
    ofVec2f changes = (avgPosOfOthers - this->position) / 100.0f;
    return changes;
}

/*
 Avoid other boids
 */

ofVec2f Boid::separate(vector<Boid>& boids)
{
    ofVec2f changes;
    for(int i=0; i<boids.size(); i++)
    {
        if (&boids[i] != this)
        {
            float dist = this->position.distance(boids[i].position);
            if(abs(dist) < MIN_DISTANCE)
            {
                changes = (changes - (this->position - boids[i].position));
            }
        }
    }
    return changes;
}

ofVec2f Boid::align(vector<Boid>& boids)
{
    ofVec2f sumOfVelOfOthers;
    int n =0;
    
    for(int i=0; i<boids.size(); i++)
    {
        if (&boids[i] != this)
        {
            sumOfVelOfOthers += boids[i].velocity;
            n++;
        }
    }
    avgVelOfOthers = sumOfVelOfOthers / (float)n;
    ofVec2f changes = (avgVelOfOthers - this->velocity) / 20.0f;
    return changes;
}

ofVec2f Boid::absVec2f(ofVec2f theVector)
{
    return ofVec2f(abs(theVector.x), abs(theVector.y));
}