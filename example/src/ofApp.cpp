// Based on Maximillian integration example, see https://github.com/micknoise/Maximilian/tree/master/openFrameworks

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //housekeeping
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    
    //Maximillian setup
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    //ofxAVUI setup
    //Zone 0
    zones[0].setup("zone1", 50, 100, 200, "sound.wav", ofColor(100,100,100, 150), ofColor(0,255,255, 255), bufferSize);
    ofxAVUIXYPad *pad1 = new ofxAVUIXYPad("Pad", "triggerPlay",  "toggleLooping", "volume", "pitch");
    zones[0].addUI(pad1, 150);
    ofxAVUIToggle *toggle1 = new ofxAVUIToggle("Looping", "toggleLooping");
    zones[0].addUI(toggle1, 100);
    ofxAVUIButton *button1 = new ofxAVUIButton("Trigger", "togglePlay");
    zones[0].addUI(button1, 100);
    
    ofxAVUIVisualWave *visual1 = new ofxAVUIVisualWave();
    zones[0].addVisual(visual1, ofColor(0,0,255));

    //Zone 1
    zones[1].setup("zone2", 300, 100, 150, "Low.wav", ofColor(100,100,100, 150), ofColor(255,255,0, 255), bufferSize);
    ofxAVUIEmpty *empty1 = new ofxAVUIEmpty("Empty");
    zones[1].addUI(empty1, 50);
    ofxAVUIXYPad *pad2 = new ofxAVUIXYPad("Pad", "triggerPlay", "triggerPlay", "pitch", "volume");
    zones[1].addUI(pad2, 100);
    ofxAVUIEmpty *empty2 = new ofxAVUIEmpty("Empty");
    zones[1].addUI(empty2, 75);
    ofxAVUISlider *slider1 = new ofxAVUISlider("Slider", "pitch", "triggerPlay", "toggleLooping");
    zones[1].addUI(slider1, 100);
    ofxAVUIToggle *toggle2 = new ofxAVUIToggle("Looping", "toggleLooping");
    zones[1].addUI(toggle2, 50);
    
    ofxAVUIVisualBars *visual2 = new ofxAVUIVisualBars(5);
    zones[1].addVisual(visual2, ofColor(255,0,255));

    //Zone 2
    zones[2].setup("zone3", 550, 100, 200, "synth.wav", ofColor(100,100,100, 150), ofColor(255,0,255, 255), bufferSize);
    ofxAVUIXYPad *pad3 = new ofxAVUIXYPad("Pad", "triggerPlay", "triggerPlay", "pitch", "volume");
    zones[2].addUI(pad3, 100);
    
    ofxAVUISoundFxFilter *filter1 = new ofxAVUISoundFxFilter();
    filter1->setup("filterToggle", false, "frequency", 200, 20000, 200, "resonance", 0, 100, 10);
    zones[2].addSoundFx(filter1);
    
    ofxAVUIXYPad *pad4 = new ofxAVUIXYPad("Filter Pad", "filterTrigger", "filterToggle", "frequency", "resonance");
    zones[2].addUI(pad4, 100);

    ofxAVUISoundFxDelay *delay1 = new ofxAVUISoundFxDelay();
    delay1->setup("delayToggle", false, "size", 10000, 40000, 20000, "feedback", 0.5, 1.0, 0.75);
    zones[2].addSoundFx(delay1);
    
    ofxAVUIXYPad *pad5 = new ofxAVUIXYPad("Delay Pad", "delayTrigger", "delayToggle", "size", "feedback");
    zones[2].addUI(pad5, 100);

    ofxAVUIToggle *toggle3 = new ofxAVUIToggle("Delay Toggle", "delayToggle");
    zones[2].addUI(toggle3, 50);
    
    ofxAVUIVisualCircles *visual3 = new ofxAVUIVisualCircles(10);
    zones[2].addVisual(visual3, ofColor(0,255,0, 196));

    //OF sound start
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //get individual parameters and use them outside of the zone, together with their min/max limits
    ofParameter<float> x = zones[0].getParamValueFloat("volume");
    int coordX = ofMap(x, x.getMin(), x.getMax(), 0, ofGetWidth());
    ofParameter<float> y = zones[0].getParamValueFloat("pitch");
    int coordY = ofMap(y, y.getMin(), y.getMax(), 0, ofGetHeight());
    ofDrawLine(coordX, 0, coordX, ofGetHeight());
    ofDrawLine(0, coordY, ofGetWidth(), coordY);

    //draw all the zones
    for (int k=0; k<3; k++) {
        zones[k].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        output[i*nChannels    ] = 0;
        output[i*nChannels + 1] = 0;

        for (int k=0; k<3; k++) {
            zones[k].play(i);
            output[i*nChannels    ] += zones[k].getOutput(0);
            output[i*nChannels + 1] += zones[k].getOutput(1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
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
