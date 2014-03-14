#include "testApp.h"
#define NUMOFBOIDS 10

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAntiAliasing();
    ofSetFrameRate(15);
    for (int i=0; i<NUMOFBOIDS; i++) {
        boids.push_back(Boid());
    }
    sender.setup("127.0.0.1", 6666);
    
    //old OF default is 96 - but this results in fonts looking larger than in other programs.
	ofTrueTypeFont::setGlobalDpi(72);
    
    verdana14.loadFont("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);
}

//--------------------------------------------------------------
void testApp::update(){

    for(int i=0; i<boids.size(); i++)
    {
        ofxOscMessage m;
        m.setAddress("/boid");
        m.addIntArg(i);
        boids[i].update(boids);
        m.addFloatArg(boids[i].position.x);
        m.addFloatArg(boids[i].position.y);
        m.addFloatArg(boids[i].velocity.x);
        m.addFloatArg(boids[i].velocity.y);
        sender.sendMessage(m);
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    //Display Text
    ofSetColor(245, 58, 135);
    ofPoint start = ofPoint(ofGetWindowWidth()-200,ofGetWindowHeight()-50);
	verdana14.drawString("Framerate: " + ofToString(ofGetFrameRate()), start.x, start.y );
	verdana14.drawString("No of Boids: " + ofToString(boids.size()), start.x, start.y+20);

    //Draw boids
    for(int i=0; i<boids.size(); i++)
        boids[i].draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //Add/delete boids 
    if (key == '=') {
        boids.push_back(Boid());
    } else if(key == '-')
    {
        boids.pop_back();
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
