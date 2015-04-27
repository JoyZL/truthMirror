//
//  Stage5Panel.cpp
//  truthMirror
//
//  Collaberated with jayson on 22/04/2015.
//
//

#include "State5Panel.h"


void State5Panel::init(Ethnicity _ethnicity)
{
    
    originalFaces.clear();
    averageFaces.clear();
    goldenRatioFaces.clear();
    averageAttractionFaces.clear();
    
    selectedScrollBar=false;
    scrollBarPosition = 0.0f;
    font.loadFont("verdana.ttf", 15, true, true);
    
    scrollAmount = 0;
    
    ethnicity = _ethnicity;
    
    switch(ethnicity)
    {
        case CHINESE:
            loadImages(ofToDataPath(CHINESE_FOLDER));
            break;
        case KOREAN:
            loadImages(ofToDataPath(KOREAN_FOLDER));
            break;
        case JAPANESE:
            loadImages(ofToDataPath(JAPANESE_FOLDER));
            break;
        case TAIWANESE:
            loadImages(ofToDataPath(TAIWANESE_FOLDER));
            break;
    }
    
    restartButton = ofRectangle(ofGetWidth() - 200, 10, 150,30);
}




void State5Panel::loadImages(string path)
{
    ofDirectory dir(path);
    
    dir.allowExt("jpg");
    dir.listDir();
    
    for(int i = 0; i < dir.numFiles() ;i++)
    {
        cout << "Loading image: " << dir.getPath(i) << endl;
        
        string filename = dir.getName(i);//dir.getPath(i);
        string filePath = dir.getPath(i);
        std::string originalPrefix("OR");
        std::string averageAttractivePrefix("AA");
        std::string averagePrefix("AV");
        std::string goldenRatioPrefix("GR");
        
        
            
        if(filename.substr(0, originalPrefix.size()) == originalPrefix)
        {
            ofImage img;
            img.loadImage(filePath);
            originalFaces.push_back(img);
        }else if (filename.substr(0, averageAttractivePrefix.size()) == averageAttractivePrefix)
        {
            ofImage img;
            img.loadImage(filePath);
            averageAttractionFaces.push_back(img);
        }else if(filename.substr(0, averagePrefix.size()) == averagePrefix)
        {
            ofImage img;
            img.loadImage(filePath);
            averageFaces.push_back(img);

        }else if(filename.substr(0, goldenRatioPrefix.size()) == goldenRatioPrefix)
        {
            ofImage img;
            img.loadImage(filePath);
            goldenRatioFaces.push_back(img);
        }
    }
    
    cout << "NUM ORIGINAL IMAGES: " << originalFaces.size() << endl;
    cout << "NUM AVERAGEATTRACT IMAGES: " << averageAttractionFaces.size() << endl;
    cout << "NUM AVERAGE IMAGES: " << averageFaces.size() << endl;
    cout << "NUM GOLDENRATIO IMAGES: " << goldenRatioFaces.size() << endl;
}

void State5Panel::draw()
{
    ofPushMatrix();
    
    
    ofTranslate(0, -scrollAmount);
    ofSetColor(255,255,255);
    switch(ethnicity)
    {
        case CHINESE:
            font.drawString("CHINESE", 60,35);
            break;
        case JAPANESE:
            font.drawString("JAPANESE", 60,35);
            break;
        case TAIWANESE:
            font.drawString("TAIWANESE", 60,35);
            break;
        case KOREAN:
            font.drawString("KOREAN", 60,35);
            break;
    }
    ofNoFill();
    ofRect(30,10,180,30);
    ofFill();
    
    ofSetColor(125,125,125);
    ofRect(restartButton.x, restartButton.y, restartButton.width, restartButton.height);
    
    ofNoFill();
    ofSetColor(255,255,255);
    ofRect(restartButton.x, restartButton.y, restartButton.width, restartButton.height);
    
    font.drawString("RESTART", restartButton.x + 10, 35);
    ofFill();
    
    ofTranslate(0,30);
    ofSetColor(255,255,255);
    int totalFaces = originalFaces.size() + averageFaces.size() + averageAttractionFaces.size() + goldenRatioFaces.size();
    
    char label[64];
    sprintf(label, "People Who Selected Their Original Face : %i of %i",originalFaces.size(), totalFaces);
    
    ofLine(0,IMAGE_OFFSET_Y - 24, ofGetWidth(), IMAGE_OFFSET_Y - 24 );
    ofLine(0,IMAGE_OFFSET_Y - 53, ofGetWidth(), IMAGE_OFFSET_Y - 53 );
    font.drawString(label, 30,IMAGE_OFFSET_Y -30);
    
    int numOriginalRows         = (originalFaces.size() / 4) +1;
    int numAverageRows          = (averageFaces.size()   / 4)+1;
    int numAverageAttractRows   = (averageAttractionFaces.size()  / 4)+1;
    int numGoldenRatioRows      = (goldenRatioFaces.size()  / 4)+1;
    
    if(originalFaces.size() % 4 == 0)
        numOriginalRows--;
    
    if(averageFaces.size() % 4 == 0)
        numAverageRows--;
    
    if(averageAttractionFaces.size() % 4 == 0)
        numAverageAttractRows--;
    
    if(goldenRatioFaces.size() % 4 == 0)
        numGoldenRatioRows--;
    
    ofSetColor(255,255,255);
    for(int i = 0; i < originalFaces.size();i++)
    {
        int column = i % 4;
        int row    = i / 4;
        
        float x = column * OFFSET_X;
        float y = IMAGE_OFFSET_Y + row * OFFSET_Y;
        originalFaces[i].draw(x + XPADDING, y, IMAGE_WIDTH, IMAGE_HEIGHT);
    }
    
    float off = IMAGE_OFFSET_Y + (numOriginalRows) * OFFSET_Y;
    
    sprintf(label, "People Who Selected The Average Face : %i of %i",averageFaces.size(), totalFaces);
    ofSetColor(255,255,255);
    font.drawString(label, 30,off -30 + IMAGE_OFFSET_Y);
    ofLine(0,off - 24 + IMAGE_OFFSET_Y, ofGetWidth(), off - 24  + IMAGE_OFFSET_Y);
    ofLine(0,off - 53 + IMAGE_OFFSET_Y, ofGetWidth(), off - 53  + IMAGE_OFFSET_Y);
    
    ofSetColor(255,255,255);
    for(int i = 0; i < averageFaces.size();i++)
    {
        int column = i % 4;
        int row    = i / 4;
        
        float x = column * OFFSET_X;
        float y = off + IMAGE_OFFSET_Y + row * OFFSET_Y;
        averageFaces[i].draw(x + XPADDING, y, IMAGE_WIDTH, IMAGE_HEIGHT);
    }
    
    
    off = off + IMAGE_OFFSET_Y + (numAverageRows) * OFFSET_Y;
    
    sprintf(label, "People Who Selected The Golden Ratio : %i of %i",goldenRatioFaces.size(), totalFaces);
    ofSetColor(255,255,255);
    font.drawString(label, 30,off -30 + IMAGE_OFFSET_Y);
    ofLine(0,off - 24 + IMAGE_OFFSET_Y, ofGetWidth(), off - 24  + IMAGE_OFFSET_Y);
    ofLine(0,off - 53 + IMAGE_OFFSET_Y, ofGetWidth(), off - 53  + IMAGE_OFFSET_Y);
    
    ofSetColor(255,255,255);
    for(int i = 0; i < goldenRatioFaces.size();i++)
    {
        int column = i % 4;
        int row    = i / 4;
        
        float x = column * OFFSET_X;
        float y = off + IMAGE_OFFSET_Y + row * OFFSET_Y;
        goldenRatioFaces[i].draw(x + XPADDING, y, IMAGE_WIDTH, IMAGE_HEIGHT);
    }
    
    
    off = off + IMAGE_OFFSET_Y + (numGoldenRatioRows) * OFFSET_Y;
    ofSetColor(255,255,255);
    sprintf(label, "People Who Selected The Average Attractive Face : %i of %i",averageAttractionFaces.size(), totalFaces);
  
    font.drawString(label, 30,off -30 + IMAGE_OFFSET_Y);
    ofLine(0,off - 24 + IMAGE_OFFSET_Y, ofGetWidth(), off - 24 + IMAGE_OFFSET_Y );
    ofLine(0,off - 53 + IMAGE_OFFSET_Y, ofGetWidth(), off - 53 + IMAGE_OFFSET_Y );
    
    
    ofSetColor(255,255,255);
    for(int i = 0; i < averageAttractionFaces.size();i++)
    {
        int column = i % 4;
        int row    = i / 4;
        
        float x = column * OFFSET_X;
        float y = off + IMAGE_OFFSET_Y + row * OFFSET_Y;
        averageAttractionFaces[i].draw(x + XPADDING, y, IMAGE_WIDTH, IMAGE_HEIGHT);
    }
    
    maxScrollAmount = off + (numAverageAttractRows) * OFFSET_Y;
    ofPopMatrix();
    drawScrollBar();
}


void State5Panel::drawScrollBar()
{
    scrollBarPosition = scrollAmount / maxScrollAmount;
    ofSetColor(200);
    ofRect(ofGetWidth() - SCROLL_BAR_WIDTH, 0, SCROLL_BAR_WIDTH, ofGetHeight());
    
    ofSetColor(255);
    ofRect(ofGetWidth() - SCROLL_BAR_WIDTH, scrollBarPosition * ((float)ofGetHeight()-SCROLL_BAR_HEIGHT),SCROLL_BAR_WIDTH,SCROLL_BAR_HEIGHT);
    
}
void State5Panel::mouseReleased(int mouseX, int mouseY)
{
    selectedScrollBar=false;
}

bool State5Panel::mouseDown(int mouseX, int mouseY)
{
    scrollBarPosition = scrollAmount / maxScrollAmount;
    
    ofRectangle scrollBarRect = ofRectangle(ofGetWidth() - SCROLL_BAR_WIDTH, scrollBarPosition * ((float)ofGetHeight()-SCROLL_BAR_HEIGHT),SCROLL_BAR_WIDTH,SCROLL_BAR_HEIGHT);
    
    if(scrollBarRect.inside(mouseX,mouseY))
    {
        selectedScrollBar = true;
    }else{
        selectedScrollBar = false;
    }
    
    if(restartButton.inside(mouseX, mouseY - scrollAmount))
    {
        return true;
    }else
        return false;
}

void State5Panel::scrollDown(int speed, int yPosition)
{
    if(selectedScrollBar)
    {
        float amount = (float)yPosition / (float)ofGetHeight();
        scrollAmount = amount * (float)maxScrollAmount;
    }else
        scrollAmount -= (float)speed * SCROLL_SPEED;
    
    if(scrollAmount < 0) scrollAmount = 0;
    if(scrollAmount > maxScrollAmount) scrollAmount = maxScrollAmount;
}