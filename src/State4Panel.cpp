//
//  State4Panel.cpp
//  truthMirror
//
//  Collaberated with jayson on 21/04/2015.
//
//

#include "State4Panel.h"

State4Panel::State4Panel()
{
    isLoaded = false;
}

void State4Panel::draw()
{
    if(isLoaded)
    {
        for(int i = 0; i < NUM_IMAGES;i++)
        {
            ofSetColor(255,255,255);
            imgs[i].draw(imgBounds[i].x,imgBounds[i].y, imgBounds[i].width, imgBounds[i].height);
            
            if(mouseOverImg[i])
            {
                ofSetColor(255,255,255,125);
                ofRect(imgBounds[i].x,imgBounds[i].y, imgBounds[i].width, imgBounds[i].height);
            }
            
            ofRectangle textSizeRect = font.getStringBoundingBox(imgLabels[i], 0,0);
            font.drawString(imgLabels[i], i*offset + 160 - textSizeRect.width/2, ofGetHeight()/2 + imageHeight/2 + paddingBetweenTextAndImage);
        }
    }
}

void State4Panel::init(vector<string> imagePaths, vector <ofImage> inImgs, vector<string> labels, string ethnicity)
{
    ethnicityFolder = ethnicity;
    font.loadFont("verdana.ttf", 13, true, true);
    
    for(int i =0; i < imagePaths.size() && i < NUM_IMAGES ; i++)
    {
        cout << "loading image: " <<  imagePaths[i] << endl;
        imgs[i].loadImage(ofToDataPath(imagePaths[i]));
        imgLabels.push_back(labels[i]);
        mouseOverImg[i]=false;
        //imgBounds[i] = ofRectangle(i*offset + padding, ofGetHeight()/2 - imageHeight/2 + Y_OFFSET, imageWidth, imageHeight);
        imgBounds[i] = ofRectangle(MARGIN_OFFSET + i * offset + padding,ofGetHeight()/2 - imageHeight/2 + Y_OFFSET, imageWidth, imageHeight);
    }
    
    isLoaded=true;
}


void State4Panel::mouseOver(int mouseX, int mouseY)
{
    for(int i = 0; i < NUM_IMAGES;i++)
    {
        mouseOverImg[i] = false;
        
        if(imgBounds[i].inside((float)mouseX, (float)mouseY))
        {
            mouseOverImg[i] = true;
            
        }
    }
}

bool State4Panel::mousePressed(int mouseX, int mouseY)
{
    bool finished = false;
    for(int i = 0; i < NUM_IMAGES;i++)
    {
        // Selected image i
        if(imgBounds[i].inside((float)mouseX, (float)mouseY))
        {
            
            // Save image to file with date
            string imageType="";
            switch(i)
            {
                case 0:
                    imageType = "OR";
                    break;
                case 1:
                    imageType = "AV";
                    break;
                case 2:
                    imageType = "GR";
                    break;
                case 3:
                    imageType = "AA";
                    break;
            }
            string filePath = "final_faces/" + ethnicityFolder + "/" + imageType + "_" + ofGetTimestampString() + ".jpg";
            
            imgs[i].saveImage(ofToDataPath(filePath));
            finished = true;
        }
    }
    
    return finished;
}