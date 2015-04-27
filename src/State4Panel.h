//
//  State4Panel.h
//  truthMirror
//
// Collaberated with jayson on 21/04/2015.
//
//

#ifndef __truthMirror__State4Panel__
#define __truthMirror__State4Panel__

#include <stdio.h>
#include "ofMain.h"

#define MARGIN_OFFSET 30
#define NUM_IMAGES 4
#define imageWidth 290
#define imageHeight 163
#define offset (1280 - (MARGIN_OFFSET * 2)) / 4
#define paddingBetweenTextAndImage -10
#define padding (offset - imageWidth)/2
#define Y_OFFSET -50

class State4Panel
{
public:
    State4Panel();
    void draw();
    void init(vector<string> imagePaths, vector <ofImage> inImgs, vector<string> labels, string ethnicity);
    
    void mouseOver(int mouseX, int mouseY);
    bool mousePressed(int mouseX, int mouseY);
private:
    bool mouseOverImg[NUM_IMAGES];
    ofTrueTypeFont	font;
    ofImage imgs[NUM_IMAGES];
    ofRectangle  imgBounds[NUM_IMAGES];
    
    string ethnicityFolder;
    bool isLoaded;
    vector<string> imgLabels;
};
#endif /* defined(__truthMirror__State4Panel__) */
