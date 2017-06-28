#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"
#include "ofxControl.h"

#define OSC_DESTINATION_DEFAULT "localhost"
#define OSC_ADDRESS_ROOT_DEFAULT "/kinect"
#define OSC_PORT_DEFAULT 6448

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxPanel panel;
    
    vector < shared_ptr<ofxKinectV2> > kinects;
    
    vector <ofTexture> texDepth;
    vector <ofTexture> texRGB;
    vector <ofFloatPixels> rawDepthPixels;
    vector <ofColor> testdata;
    
    ofxOscSender osc;
    string oscDestination;
    string oscAddressRoot;
    int oscPort;
    string oscMessageString;
    string realWorldAddress;
    string screenAddress;
    
    bool doneOnce;
    bool depthOnce;
    bool sending;
    ofxControlWidget gui;

};
