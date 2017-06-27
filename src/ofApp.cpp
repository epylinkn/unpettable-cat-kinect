#include "ofApp.h"
#include "sstream"

//NOTE: if you are unable to connect to your device on OS X, try unplugging and replugging in the power, while leaving the USB connected.
//ofxKinectV2 will only work if the NUI Sensor shows up in the Superspeed category of the System Profiler in the USB section.

//On OS X if you are not using the example project. Make sure to add OpenCL.framework to the Link Binary With Library Build Phase
//and change the line in Project.xcconfig to OTHER_LDFLAGS = $(OF_CORE_LIBS) $(OF_CORE_FRAMEWORKS) -framework OpenCL

//--------------------------------------------------------------
void ofApp::setup(){
    
    doneOnce = false;
    depthOnce = false;
    
    //Uncomment for verbose info from libfreenect2
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofBackground(30, 30, 30);
    
    //see how many devices we have.
    ofxKinectV2 tmp;
    vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();
    
    //allocate for this many devices
    kinects.resize(deviceList.size());
    texDepth.resize(kinects.size());
    texRGB.resize(kinects.size());
    
    panel.setup("", "settings.xml", 10, 100);
    
    //Note you don't have to use ofxKinectV2 as a shared pointer, but if you want to have it in a vector ( ie: for multuple ) it needs to be.
    for(int d = 0; d < kinects.size(); d++){
        kinects[d] = shared_ptr <ofxKinectV2> (new ofxKinectV2());
        kinects[d]->open(deviceList[d].serial);
        panel.add(kinects[d]->params);
    }
    
    panel.loadFromFile("settings.xml");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int d = 0; d < kinects.size(); d++){
        kinects[d]->update();
        if( kinects[d]->isFrameNew() ){
            texDepth[d].loadData( kinects[d]->getDepthPixels() );
            texRGB[d].loadData( kinects[d]->getRgbPixels() );
        }
    }
}



//--------------------------------------------------------------
void ofApp::draw(){
    //    ofDrawBitmapString("ofxKinectV2: Work in progress addon.\nBased on the excellent work by the OpenKinect libfreenect2 team\n\n-Requires USB 3.0 port ( superspeed )\n-Requires patched libusb. If you have the libusb from ofxKinect ( v1 ) linked to your project it will prevent superspeed on Kinect V2", 10, 14);
    
    for(int d = 0; d < kinects.size(); d++){
        float dwHD = 1920/4;
        float dhHD = 1080/4;
        
        float shiftY = 100 + ((10 + texDepth[d].getHeight()) * d);
        
        texDepth[d].draw(200, shiftY);
        texRGB[d].draw(200, shiftY + texDepth[d].getHeight(), dwHD, dhHD);
    }
    
    
    panel.draw();
    
    
    
    
    ofPixels pix;
    texRGB[0].readToPixels(pix);
    string debugString = "Num pixels: " + ofToString(pix.size());
    ofDrawBitmapString(debugString, 20, 30);
    



    
    int i = 0;
    if (!doneOnce) {
        while( i < pix.size()) {
            ofColor color = pix.getColor(i);
        
            string foo = "RGB pixel: " + ofToString(color);
            std::cout << foo << std::endl;
            
            if (i> 1000) {
                doneOnce = true;
                break;
            }
            
            i += pix.getNumChannels();
        }
    }
    
    
    //    ofFloatPixels depthPixels;
    //    texDepth[0].readToPixels(depthPixels);
    //    string debugDepth = "Num depth pixels: " + ofToString(depthPixels.size());
    //    ofDrawBitmapString(debugDepth, 20, 40);
    ofPixels depthPixels;
    texDepth[0].readToPixels(depthPixels);
    
    unsigned char * pixels  = depthPixels.getData();
    char prevDepth;
    int changeCounter = 0;
    
    if (!depthOnce) {
        for(int i = 0; i < depthPixels.size(); i++){
            int depth = pixels[i];
            
            if (changeCounter > 1000) {
                depthOnce = true;
                break;
                
            }
            
            if (depth != prevDepth) {
                changeCounter++;
                string foo = "Depth pixel: " + ofToString(depth);
                std::cout << foo << std::endl;
            }
        }
    }

    ofDrawBitmapString("Points: ", 10, 14);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
