#include "testApp.h"

void testApp::timeoutFunction1() {
    state += 1;
    state = state % 4;
}

void testApp::timeoutFunction2(Arg *arg) {
    arg->state += 1;
    arg->state = arg->state % 4;
}

//--------------------------------------------------------------
void testApp::setup(){
    ofSetColor(255, 255, 255);
    
    state = 0;
    ofxSetTimeout(this, &testApp::timeoutFunction1, 500);
    ofxSetTimeout(this, &testApp::timeoutFunction1, 1000);
    ofxSetTimeout(this, &testApp::timeoutFunction2, new Arg(state), 1500);
    ofBackground(0, 0, 0);
    
#if __has_extension(blocks)
    blocksBindValue = false;
    
    ofxSetTimeout(Block_copy(^{
        t = ofxSetInterval(Block_copy(^{
            timeoutFunction1();
        }), 100);
    }), 2000);
    
    ofxSetTimeout(Block_copy(^{ blocksBindValue = true; }), 2000);
#endif
    
#if __has_feature(cxx_lambdas)
    lambdaBindValue = false;
    ofxSetTimeout([&](){ lambdaBindValue = true; }, 5000);
#endif
}

//--------------------------------------------------------------
void testApp::update(){
    switch (state) {
        case 0:
            ofBackground(0, 0, 0);
            break;
        case 1:
            ofBackground(255, 0, 0);
            break;
        case 2:
            ofBackground(0, 255, 0);
            break;
        case 3:
            ofBackground(0, 0, 255);
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
#if __has_extension(blocks)
    if(blocksBindValue) {
        for(int i = 0; i < 200; i++) {
            ofLine(ofRandomWidth(), ofRandomHeight(), ofRandomWidth(), ofRandomHeight());
        }
    }
#endif
    
#if __has_feature(cxx_lambdas)
    if(lambdaBindValue) {
        for(int i = 0; i < 200; i++) {
            ofCircle(ofRandomWidth(), ofRandomHeight(), ofRandom(10, 20));
        }
    }
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == ' ') t.clearTimer();
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
