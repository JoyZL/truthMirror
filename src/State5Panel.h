//
//  Stage5Panel.h
//  truthMirror
//
//  Collaberated with jayson on 22/04/2015.
//
//

#ifndef __truthMirror__Stage5Panel__
#define __truthMirror__Stage5Panel__

#include <stdio.h>
#include "ofMain.h"

#define CHINESE_FOLDER      "final_faces/chinese/"
#define KOREAN_FOLDER       "final_faces/korean/"
#define JAPANESE_FOLDER     "final_faces/japanese/"
#define TAIWANESE_FOLDER    "final_faces/taiwanese/"
enum Ethnicity {
    //state0
    NOSELECTION=-1,
    //state1
    CHINESE=0,
    TAIWANESE=1,
    KOREAN=2,
    JAPANESE=3,
    NUM_GUI = 4
};

#define IMAGE_OFFSET_Y 100
#define IMAGE_WIDTH 300
#define IMAGE_HEIGHT 210
#define OFFSET_X 320
#define OFFSET_Y 200
#define XPADDING 10
#define SCROLL_SPEED 0.5

#define SCROLL_BAR_WIDTH 10
#define SCROLL_BAR_HEIGHT 40

class State5Panel
{
public:
    
    void init(Ethnicity _ethnicity);
    void draw();
    
    void scrollDown(int speed, int yPosition);
    
    bool mouseDown(int mouseX, int mouseY);
    void mouseReleased(int mouseX, int mouseY);
private:
    
    void drawScrollBar();
    void loadImages(string path);
    
    float maxScrollAmount;
    ofTrueTypeFont	font;
    
    vector <ofImage> originalFaces;
    vector <ofImage> averageFaces;
    vector <ofImage> goldenRatioFaces;
    vector <ofImage> averageAttractionFaces;
    
    float scrollAmount;
    Ethnicity ethnicity;
    
    float scrollBarPosition;
    
    bool selectedScrollBar;
    
    ofRectangle restartButton;
};

#endif /* defined(__truthMirror__Stage5Panel__) */
