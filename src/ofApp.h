#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxFaceTracker.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxDelaunay.h"
#include "ofxUI.h"

#include "State4Panel.h"
#include "State5Panel.h"

//#include "ofxFBOTexture.h"

#define BUTTON_IMAGE "state4_button.png"

#define CHINESE_TEXT_LABEL "CHINESE"
#define JAPANESE_TEXT_LABEL "JAPANESE"
#define KOREAN_TEXT_LABEL "KOREAN"
#define TAIWANESE_TEXT_LABEL "TAIWANESE"
class testApp : public ofBaseApp {
public:
    
    enum State { STATE0 = 0, STATE1 = 1, STATE2 = 2, STATE3 = 3, STATE4 = 4, STATE5 = 5 };
   
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void trackFace();
    void drawGrid();
    void drawCam();
    void reference();
    void drawChoices();
    void UpdateLabelAverage(string name);
    void UpdateLabelGR(string name);
    void UpdateLabelAA(string name);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void setVisibility(string labelName, bool isVisible);
    void setLbVisibility(string lbName, bool isLbVisible);

    void updateLabel(string name, string labelName);
    void updateLb(string name, string labelName);
    void hideState0 ();
    void showState0 ();
    void state4Buttons();
    void mousePressed(int x, int y, int button);
    void resetApp();
    //void mouseReleased(int x, int y, int button);
    
    bool capture;
    
    ofImage img;
    ofImage capturedImg;
        
    ofVideoGrabber cam;
    
    //ofxFaceTracker camTracker;
    ofxFaceTrackerThreaded camTracker;
    
    ofxFaceTracker imgTracker;
    
    ofxUICanvas *gui0;
    ofxUICanvas *gui1;
    
    ofxUICanvas *gui3;
    ofxUICanvas *gui2;
    
    //ofxUICanvas *gui5;
    
    void guiEvent(ofxUIEventArgs &e);

    bool drawPadding;
    bool drawCapture= false;
    
    int imgCounter;
    
    State appState = STATE0;
    State prevState = appState;
    string ethnicity;
    Ethnicity currentEthnicity = NOSELECTION;
    
    vector<ofImage> captureImgs;
    vector<string> imagePaths;
    
    vector<ofImage> referenceImages;
    vector<ofImage> smallReferenceImages;
    vector<ofImage> savedImages;
    vector<ofImage> finalSelectionOR;
    vector<ofImage> finalSelectionAV;
    vector<ofImage> finalSelectionGR;
    vector<ofImage> finalSelectionAA;
    
    vector<string> capturedImgPath;
    
    State4Panel state4Panel;
    State5Panel state5Panel;
    
    void hideState1();
    void showState2();
    void nextState();
    void showState5();
    void showState1();
    void hideState5();
    
    void hideState2();
    void showState3();
    void hideState3();
    
    bool scrolling;
    int lastScrollY;
    
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y , int button);
    
    
    ofTrueTypeFont	font;
};
