//userflow of this app at this point
//defult starting state: state 0
//press "c" to capture your original portrait
//mouse click one ethnicity and it goes to state 1 automatically
//press "c" again to capture the average face
//press "n" to go to the next state: state 2
//press "c" again to capture the golden ratio face
//press "n" to go to the next state: state 3
//press "c" to capture the average attractive face
//press "n" to go to the next state: state 4
//mouse select one of the image buttons
//press "n" to go to state 5, here shows all users' selections from state 4

//press "n" to go back to state 0


#include "ofApp.h"
#include <sstream>


using namespace ofxCv;

void testApp::setup() {
        vector<ofVideoDevice> devices = cam.listDevices();
    for (int i =0; i<devices.size(); i++) {
        cout<<devices[i].id<<endl;
        cout<<devices[i].hardwareName<<endl;
    }
    cam.setDeviceID(1);
    
//    devices[0].id
    font.loadFont("verdana.ttf", 20, true, true);
    
    lastScrollY = -1;
    
    //set up image and camera tracker
    ofSetVerticalSync(true);
    cam.initGrabber(1280, 720);
    
    imgTracker.setup();
    camTracker.setup();    
    
    resetApp();
    
    ofEnableSmoothing();
    
    ofSetFrameRate(25);
}

void testApp::resetApp()
{
    currentEthnicity = NOSELECTION;
    
    appState = STATE0;
    prevState = appState;
    capture = false;
     drawCapture= false;
    imgCounter = 0;
    referenceImages.clear();
    referenceImages.resize(NUM_GUI);
    smallReferenceImages.clear();
    smallReferenceImages.resize(NUM_GUI);
    
    //screen captured image names
    capturedImgPath.clear();
    capturedImgPath.resize(4);
    imagePaths.clear();
    imagePaths.resize(4);
    
    //menu on state 0, actual reference images to update to the imgTracker
    referenceImages[ CHINESE ].loadImage("AVERAGECHINESE.jpg");
    referenceImages[ TAIWANESE ].loadImage("AVERAGETAIWANESE.jpg");
    referenceImages[ KOREAN ].loadImage("AVERAGEKOREAN.jpg");
    referenceImages[ JAPANESE ].loadImage("AVERAGEJAPANESE.jpg");
    
    //a smaller version of reference images for display
    smallReferenceImages[ CHINESE ].loadImage("AC.jpg");
    smallReferenceImages[ TAIWANESE ].loadImage("AT.jpg");
    smallReferenceImages[ KOREAN ].loadImage("AK.jpg");
    smallReferenceImages[ JAPANESE ].loadImage("AJ.jpg");
    showState0();

}

void testApp::showState0(){
    
    cout << "Setting up state 0" << endl;
    imgTracker.setup();
    camTracker.setup();
    
    currentEthnicity= NOSELECTION;
    imgCounter = 0;
    
    //ofxUI
    drawPadding = false;
    //create UI canvases for gui at bottom left of screen
    gui0 = new ofxUICanvas(0, 10, 350, 300);
    gui0->setVisible(true);
    
    gui0->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui0->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN, OFX_UI_ALIGN_CENTER);
    gui0->addLabel("TAKE A PHOTO AND", OFX_UI_FONT_LARGE);
    gui0->addLabel("SELECT WHO YOU ARE", OFX_UI_FONT_LARGE);
    gui0->addLabel("", OFX_UI_FONT_LARGE);
    
    gui0->addSpacer();
    gui0->addLabelButton("TAKE A PHOTO", false);
    gui0->addSpacer();
    gui0->addLabelButton("CHINESE", false);
    gui0->addLabelButton("TAIWANESE", false);
    gui0->addLabelButton("KOREAN", false);
    gui0->addLabelButton("JAPANESE", false);
    //gui0->addSpacer();
    
    
    gui0->autoSizeToFitWidgets();
    ofAddListener(gui0->newGUIEvent,this,&testApp::guiEvent);

    captureImgs.resize(4);
}

void testApp::hideState5()
{
    
}
void testApp::hideState1()
{
    
    ofRemoveListener(gui1->newGUIEvent,this,&testApp::guiEvent);
    gui1->setVisible(false);
    delete gui1;
}
void testApp::hideState2()
{
    
    ofRemoveListener(gui2->newGUIEvent,this,&testApp::guiEvent);
    gui2->setVisible(false);
    delete gui2;
}
void testApp::hideState3()
{
    
    ofRemoveListener(gui3->newGUIEvent,this,&testApp::guiEvent);
    gui3->setVisible(false);
    delete gui3;
}

void testApp::showState3()
{
    
    gui3 = new ofxUICanvas(0, 383, 250, 200);
    gui3->setVisible(true);
    gui3->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui3->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN, OFX_UI_ALIGN_CENTER);
    
    switch(currentEthnicity)
    {
        case CHINESE:
            gui3->addLabel(CHINESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case TAIWANESE:
            gui3->addLabel(TAIWANESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case KOREAN:
            gui3->addLabel(KOREAN_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case JAPANESE:
            gui3->addLabel(JAPANESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
    }
    
    gui3->addLabel("AVERAGE ATTRACTIVE", OFX_UI_FONT_LARGE);
    gui3->addLabelButton("TAKE A PHOTO", false);
    gui3->addLabelButton("NEXT", false);
    gui3->autoSizeToFitWidgets();
    ofAddListener(gui3->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::showState2()
{
    
    gui2 = new ofxUICanvas(0, 383, 250, 200);
    gui2->setVisible(true);
    gui2->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui2->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN, OFX_UI_ALIGN_CENTER);
    
    switch(currentEthnicity)
    {
        case CHINESE:
            gui2->addLabel(CHINESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case TAIWANESE:
            gui2->addLabel(TAIWANESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case KOREAN:
            gui2->addLabel(KOREAN_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case JAPANESE:
            gui2->addLabel(JAPANESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
    }
    
    gui2->addLabel("GOLDEN RATIO", OFX_UI_FONT_LARGE);
    gui2->addLabelButton("TAKE A PHOTO", false);
    gui2->addLabelButton("NEXT", false);
    gui2->autoSizeToFitWidgets();
    ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::hideState0(){
    
    cout << "Hiding state0" << endl;
    
    ofRemoveListener(gui0->newGUIEvent,this,&testApp::guiEvent);
    gui0->setVisible(false);
    gui0->clearWidgets();
    //delete gui0;
    
    //hide the first set of menu
    //setVisibility("CHINESE",false);
    //setVisibility("TAIWANESE",false);
    //setVisibility("KOREAN",false);
    //setVisibility("JAPANESE",false);
    //gui->removeWidget("SELECT WHO YOU ARE");
    //show the second set of menu
    //setLbVisibility("AVERAGE",true);
    //setLbVisibility("GOLDENRATIO",true);
    //setLbVisibility("AVERAGEATTRACTIVE",true);
    
    //    setVisibility("START OVER", false);
    
}

//image buttons that contain the 4 screen captured images
void testApp::state4Buttons(){
    drawPadding = false;
    vector<string> imageLabel;
    /*imageLabel.push_back("OR YOU");
    imageLabel.push_back("AV YOU");
    imageLabel.push_back("GR YOU");
    imageLabel.push_back("AA YOU");*/
    imageLabel.push_back("ORIGINAL");
    imageLabel.push_back("AVERAGE");
    imageLabel.push_back("GOLDEN RATIO");
    imageLabel.push_back("AVERAGE\nATTRACTIVE");
    
    if(imagePaths.size() > 0)
    {
        switch(currentEthnicity)
        {
            case CHINESE:
                state4Panel.init(imagePaths, captureImgs,imageLabel, "chinese" );
                break;
                
            case TAIWANESE:
                state4Panel.init(imagePaths, captureImgs,imageLabel, "taiwanese" );
                break;
                
            case KOREAN:
                state4Panel.init(imagePaths, captureImgs,imageLabel, "korean" );
                break;
                
            case JAPANESE:
                state4Panel.init(imagePaths, captureImgs,imageLabel, "japanese" );
                break;
        };
    }else{
        cout<<"IMG COUNTER IS 0"<<endl;
    }

}


//set button visibility
void testApp::setVisibility(string labelName, bool isVis)
{
    //ofxUILabelButton* l = (ofxUILabelButton*) gui->getWidget(labelName);
    //l->setVisible(isVis);
   }

//set lable visibility
void testApp::setLbVisibility(string lbName, bool isLbVisible)
{
   
    //ofxUILabel* lb = (ofxUILabel*) gui->getWidget(lbName);
   
    //lb->setVisible(isLbVisible);
   }


//update label text
void testApp::updateLb(string name, string labelName){
    
    //ofxUILabel * l = (ofxUILabel*) gui->getWidget(labelName);
    
    //l->setLabel(name);
}

void testApp::showState1()
{
    gui1 = new ofxUICanvas(0, 383, 250, 200);
    gui1->setVisible(true);
    gui1->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui1->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN, OFX_UI_ALIGN_CENTER);
    
    switch(currentEthnicity)
    {
        case CHINESE:
            gui1->addLabel(CHINESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case TAIWANESE:
            gui1->addLabel(TAIWANESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case KOREAN:
            gui1->addLabel(KOREAN_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
            
        case JAPANESE:
            gui1->addLabel(JAPANESE_TEXT_LABEL, OFX_UI_FONT_LARGE);
            break;
    }
    
    gui1->addLabel("AVERAGE", OFX_UI_FONT_LARGE);
    gui1->addLabelButton("TAKE A PHOTO", false);
    gui1->addLabelButton("NEXT", false);
    gui1->autoSizeToFitWidgets();
    ofAddListener(gui1->newGUIEvent,this,&testApp::guiEvent);
    
    
    gui0->setVisible(false);
    gui0->clearWidgets();
    
}
void testApp::update() {
   
    
    char windowTitle[64];
    sprintf(windowTitle, "Framerate: %f\n",ofGetFrameRate());
    ofSetWindowTitle(windowTitle);
    cam.update();
    
    ofImage img;
    img.setFromPixels(cam.getPixels(), 1280, 720, OF_IMAGE_COLOR);
    //img.mirror(false,true);
    
    if(camTracker.isLookingForFace())
    {
        img.resize(320,240);
    }
    
    if(cam.isFrameNew() && appState < 4) {
        
        //camTracker.update(toCv(cam));
        camTracker.update(toCv(img));
        
    }
    
    //if user chooses one of the ethnicity
    
    printf("APPSTATE: %i PREVSTATE: %i\n", appState, prevState);
    if( prevState != appState ){
        //change from state 0 to state 1, and update the gui menu
        prevState = appState;
                cout<<"STATE CHANGED TO " << appState <<endl;
        switch (appState) {

            case STATE0:
                
                hideState5();
                showState0();
                break;
            case STATE1:
                
                hideState0();
               
                showState1();
                
                
                break;
            
            //state2: update reference image to be the golden ratio face of selected ethnicity
            case STATE2:
                
                hideState1();
                showState2();
                break;

            
            //state3: update reference image to be the average attractive face of selected ethnicity
            case STATE3:
                
                hideState2();
                showState3();
                break;
            //no more face tracking or morphing
            case STATE4:
                
                
                hideState3();
                
                break;
            //show the second gui menu that contains 4 image buttons (screen captured images from state 0 to state 3), and remove the first gui
            case STATE5:
                

                //gui->removeWidgets();
                
                break;
                
            default:
                break;
        }
        
    }
    
}

//key presses for controlling the gui menus
void testApp::keyPressed(int key){
    //press "c" to screen capture
    if(key == 'c'){
        capture = true;
    }
    
    //press "n" to switch to the next state
    if(key == 'n')
    {
        nextState();
        
        
    }
}

void testApp::nextState()
{
    printf("NEXT STATE: %i %i\n", prevState, appState);
    if(prevState == appState)
    {
        if(appState  == STATE0)
        {
            appState = STATE1;
        }else if(appState == STATE1){
            
            appState = STATE2;
            
            //update the reference image
            switch (currentEthnicity) {
                case CHINESE:
                {
                    //reference image to update to imgTracker
                    referenceImages[ CHINESE ].loadImage("GOLDENRATIOCHINESE.jpg");
                    //smaller version of the image to be displayed
                    smallReferenceImages[ CHINESE ].loadImage("GRC.jpg");
                }
                    break;
                    
                case TAIWANESE:
                {
                    referenceImages[ TAIWANESE ].loadImage("GOLDENRATIOTAIWANESE.jpg");
                    smallReferenceImages[ TAIWANESE ].loadImage("GRT.jpg");
                }
                    break;
                    
                case KOREAN:
                {
                    referenceImages[ KOREAN ].loadImage("GOLDENRATIOKOREAN.jpg");
                    smallReferenceImages[ KOREAN ].loadImage("GRK.jpg");
                }
                    break;
                    
                case JAPANESE:
                {
                    referenceImages[ JAPANESE ].loadImage("GOLDENRATIOJAPANESE.jpg");
                    smallReferenceImages[ JAPANESE ].loadImage("GRJ.jpg");
                }
                    break;
                    
                default:
                    break;
            }
            
        }else if(appState == STATE2){
            appState = STATE3;
            
            switch (currentEthnicity) {
                case CHINESE:
                {
                    referenceImages[ CHINESE ].loadImage("AVERAGEATTRACTIVECHINESE.jpg");
                    smallReferenceImages[ CHINESE ].loadImage("AAC.jpg");
                }
                    break;
                    
                case TAIWANESE:
                {
                    referenceImages[ TAIWANESE ].loadImage("AVERAGEATTRACTIVECHINESE.jpg");
                    smallReferenceImages[ TAIWANESE ].loadImage("AAT.jpg");
                }
                    break;
                    
                case KOREAN:
                {
                    referenceImages[ KOREAN ].loadImage("AVERAGEATTRACTIVEKOREAN.jpg");
                    smallReferenceImages[ KOREAN ].loadImage("AAK.jpg");
                }
                    break;
                    
                case JAPANESE:
                {
                    referenceImages[ JAPANESE ].loadImage("AVERAGEATTRACTIVEJAPANESE.jpg");
                    smallReferenceImages[ JAPANESE ].loadImage("AAJ.jpg");
                }
                    break;
                    
                default:
                    break;
            }
            
        }else if(appState == STATE3){
            printf("Changing to state 4\n");
            
            appState = STATE4;
            //draw 4 image buttons
            state4Buttons();
            
        }else if(appState == STATE4){
            printf("Changing to state 5\n");
            showState5();
            appState = STATE5;
        }else if(appState == STATE5){
            //go back to state0, reset everything
            appState = STATE0;
            //showState0();
        }
    }
}

void testApp::showState5()
{
    //gui5 = new ofxUICanvas(1000, 20, 200, 20);
    //gui5->addLabelButton("RESTART", false);
    //ofAddListener(gui5->newGUIEvent,this,&testApp::guiEvent);
    
    state5Panel.init(currentEthnicity);
}

void testApp::keyReleased(int key){
    
}

void testApp::drawCam(){
    
    ofPushMatrix();
    ofScale(-1.0f,1.0f);
    cam.draw(-ofGetWidth(),0);
    ofPopMatrix();
   }

//update reference image to imgTracker
void testApp::reference(){

    if(currentEthnicity != NOSELECTION){
    //referenceImages[ currentEthnicity ].draw(0,0);
    smallReferenceImages[currentEthnicity].draw(0,0);
    
    imgTracker.update(toCv(referenceImages[ currentEthnicity ]));
    //ofLog()<<"imgTracker:" << ofToString(imgTracker.getFound());
    }
  
}

//face tracking functions
void testApp::trackFace(){
    
    ofSetColor(255);
    
//    if(imgTracker.getFound()){
//        imgTracker.draw();
//    }
    
    ofPushMatrix();
    ofTranslate(0, 0);
    ofScale(-1.0,1.0);
    ofTranslate(-ofGetWidth(),0);
    
    if(camTracker.getFound()) {
        ofMesh faceMesh = camTracker.getImageMesh();
        ofxDelaunay delaunay;
        
        // add main face points
        for(int i = 0; i < faceMesh.getNumVertices(); i++) {
            delaunay.addPoint(faceMesh.getVertex(i));
        }
        
        // add boundary face points
        float scaleFactor = 1.6;
        ofPolyline outline = camTracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
        ofVec2f position = camTracker.getPosition();
        for(int i = 0; i < outline.size(); i++) {
            ofVec2f point((outline[i] - position) * scaleFactor + position);
            delaunay.addPoint(point);
        }
        
        // add the image corners
        int w = cam.getWidth(), h = cam.getHeight();
        delaunay.addPoint(ofVec2f(0, 0));
        delaunay.addPoint(ofVec2f(w, 0));
        delaunay.addPoint(ofVec2f(w, h));
        delaunay.addPoint(ofVec2f(0, h));
        
        delaunay.triangulate();
        ofMesh triangulated = delaunay.triangleMesh;
        triangulated.drawWireframe();
        
        // find mapping between triangulated mesh and original
        vector<int> delaunayToFinal(triangulated.getNumVertices(), -1);
        vector<int> finalToDelaunay;
        int reindexed = 0;
        for(int i = 0; i < faceMesh.getNumVertices(); i++) {
            float minDistance = 0;
            int best = 0;
            for(int j = 0; j < triangulated.getNumVertices(); j++) {
                float distance = triangulated.getVertex(j).distance(faceMesh.getVertex(i));
                if(j == 0 || distance < minDistance) {
                    minDistance = distance;
                    best = j;
                }
            }
            delaunayToFinal[best] = reindexed++;
            finalToDelaunay.push_back(best);
        }
        for(int i = 0; i < delaunayToFinal.size(); i++) {
            if(delaunayToFinal[i] == -1) {
                delaunayToFinal[i] = reindexed++;
                finalToDelaunay.push_back(i);
            }
        }
        
        // construct new mesh that has tex coords, vertices, etc.
        ofMesh finalMesh;
        finalMesh.setMode(OF_PRIMITIVE_TRIANGLES);
        for(int i = 0; i < delaunayToFinal.size(); i++) {
            int index = finalToDelaunay[i];
            finalMesh.addVertex(triangulated.getVertex(index));
            finalMesh.addTexCoord(triangulated.getVertex(index));
        }
        for(int i = 0; i < triangulated.getNumIndices(); i++) {
            finalMesh.addIndex(delaunayToFinal[triangulated.getIndex(i)]);
        }
        
        // modify mesh
        if(imgTracker.getFound()) {
            ofVec2f imgPosition = imgTracker.getPosition();
            ofVec2f camPosition = camTracker.getPosition();
            float imgScale = imgTracker.getScale();
            float camScale = camTracker.getScale();
            
            ofMesh reference = imgTracker.getImageMesh();
            for(int i = 0; i < reference.getNumVertices(); i++) {
                ofVec2f point = reference.getVertices()[i];
                
                point -= imgPosition;
                point /= imgScale;
                point *= camScale;
                point += camPosition;
                finalMesh.getVertices()[i] = point;
            }
        }
        
        cam.getTextureReference().bind();
        finalMesh.drawFaces();
        cam.getTextureReference().unbind();
        
    }
    // draw a jawline in live video according to the reference image jawling for user to align for face morphing
    if(imgTracker.getFound()){
        ofPolyline jaw = imgTracker.getImageFeature(ofxFaceTracker::JAW);
        jaw.draw();
    }
    
    ofPopMatrix();

}


//state 5: put all user selections(final selection arrays) in order, 4 images per row, original faces first, average faces the second, golden ratio faces the third, and average attractive faces the fourth
void testApp::drawGrid(){
    
    if(finalSelectionOR.size() > 0){
        for(int i =0; i< finalSelectionOR.size(); i++){
            int rowOR = floor(i/4);
            
            if(i>3){
                finalSelectionOR[i].draw(i%4*320,rowOR*180, 304, 171);
            
            }else{
                
                finalSelectionOR[i].draw(i*320,0, 304,171);
            }
        }
    }else{
        cout<<"finalSelectionOR IS 0"<<endl;
    }
    
    if(finalSelectionAV.size()>0){
        for(int i =0; i< finalSelectionAV.size(); i++){
            
            int rowAV = floor(i/4) + round(finalSelectionOR.size()-1);
            if(i>3){
            
                finalSelectionAV[i].draw(i*320,rowAV*180, 304,171);
            }else{
                finalSelectionAV[i].draw(i*320,180, 304,171);
            }
        }
    }
    
    if(finalSelectionGR.size()>0){
        for(int i =0; i< finalSelectionGR.size(); i++){
            
            int rowGR = floor(i/4) + round((finalSelectionOR.size()-1)/4) + round((finalSelectionAV.size()-1)/4);
            
            if(i>3){
                finalSelectionGR[i].draw(i*320,rowGR*180, 304,171);
            }else{
            
                finalSelectionGR[i].draw(i*320,360, 304,171);
            }
        }
    }
    
    if(finalSelectionAA.size()>0){
        for(int i =0; i< finalSelectionAA.size(); i++){
            
            int rowAA = floor(i/4) + round((finalSelectionOR.size()-1)/4) + round((finalSelectionAV.size()-1)/4) + round((finalSelectionGR.size()-1)/4);
            
            if(i>3){
                finalSelectionAA[i].draw(i*320,rowAA*180, 304,171);
            }else{
                
                finalSelectionAA[i].draw(i*320,540, 304,171);
            }
        }
    }
    

}

//enable the functions for each state
void testApp::draw() {
    ofBackground(0,0,0);
    
    cout << "gui0: " << gui0 << endl;
    
    ofPushMatrix();
    ofPushStyle();
    switch ( appState ) {
        //state0: no reference img, draw camera, take a photo
        case STATE0:
            //showState0();
            drawCam();
            break;
        //state1: draw avearge reference img, draw camera, use facetracker, take a photo
        case STATE1:
            drawCam();
            trackFace();
            reference();
            break;
        //state2: draw golden ratio reference img, draw camera, use facetracker, take a photo
        case STATE2:
            drawCam();
            trackFace();
            reference();
            break;
        //state3: draw average attractive reference img, draw camera, use facetracker, take a photo
        case STATE3:
            drawCam();
            trackFace();
            reference();
            break;
        //state4:draw the four photos taken from state0 to state3, select a photo
        case STATE4:
            printf("Drawing state 4\n");
            state4Panel.mouseOver(ofGetMouseX(), ofGetMouseY());
            state4Panel.draw();
            break;
        //state5: draw all users' selections in the relevant category
        case STATE5:
            state5Panel.draw();
            //drawGrid();
            break;
            
        default:
            break;
    }

    ofPopStyle();
    ofPopMatrix();
    
    //save screen captured images, give each a unique name by adding a time stamp. Save the file names so they can be loaded into the 4 image buttons on state4
    if(capture){
        
        
          //imgCounter += 1;
        
            ofImage img;
            //img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            img.grabScreen(280, 0, 1000, 700);
        
        captureImgs[(int)appState] = img;
        
        //captureImgs.push_back(img);
        
            std::ostringstream oss;
            oss << ofGetTimestampString();
            //string path = "capturedImage_" +ofToString(imagePaths.size())+ ".jpg";
            string path = "capturedImage_" +ofToString((int)appState)+ ".jpg";
        cout << "Saving image[" << (int)appState << ": " << path<<endl;
            img.saveImage(path);
            imagePaths[(int)appState] = path;
    
            capture = false;
       
    }
    
}


//--------------------------------------------------------------
//menu gui events
void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    int kind = e.widget->getKind();
    
    ofxUILabel* label = (ofxUILabel*) e.widget;

    cout<< "Button pressed: " << e.getName() << " parent: " << e.getCanvasParent() <<endl;
    
    if(e.getName() == "CHINESE"){
   
        currentEthnicity= CHINESE;
        appState = STATE1;
        
    }else if(e.getName()=="TAIWANESE"){
        currentEthnicity= TAIWANESE;
        appState = STATE1;
        nextState();
        
    }else if(e.getName()=="KOREAN"){
        currentEthnicity= KOREAN;
        appState = STATE1;
        nextState();
        
    }else if(e.getName()=="JAPANESE"){
        currentEthnicity= JAPANESE;
        appState = STATE1;
        nextState();
        
    }else if(e.getName()=="TAKE A PHOTO"){
        
        
        capture = true;
    }else if(e.getName()=="NEXT"){
        
        nextState();
    }else if(e.getName()=="RESTART"){
        
        
        nextState();
    }

    //once the user clicks one of the image button, save that image into the right final selection array
    else if(e.getName()=="OR YOU"){
        //finalSelectionOR.push_back(savedImages[0]);
        finalSelectionOR.push_back(imagePaths[0]);
        cout<<"original you"<<endl;
        
    }else if(e.getName()=="AV YOU"){
        //finalSelectionAV.push_back(savedImages[1]);
        finalSelectionAV.push_back(imagePaths[1]);
        
    }else if(e.getName()=="GR YOU"){
        //finalSelectionGR.push_back(savedImages[2]);
        finalSelectionGR.push_back(imagePaths[2]);
        
    }else if(e.getName()=="AA YOU"){
        //finalSelectionAA.push_back(savedImages[3]);
        finalSelectionAA.push_back(imagePaths[3]);
    }
    

}

//--------------------------------------------------------------
void testApp::exit()
{
    delete gui0;
    
}

void testApp::mousePressed(int x, int y, int button)
{
    if(appState == STATE4)
    {
        
        if(state4Panel.mousePressed(ofGetMouseX(), ofGetMouseY()))
            nextState();
    }
    
    if(appState == STATE5)
    {
        if(state5Panel.mouseDown(x,y))
            nextState();
    }
    scrolling = false;
}

void testApp::mouseReleased(int x, int y, int button)
{
    if(appState == STATE5)
        state5Panel.mouseReleased(x,y);
    
}

void testApp::mouseDragged(int x, int y, int button)
{
    if(scrolling)
    {
        int diff = y - lastScrollY;
    
        state5Panel.scrollDown(diff,y);
    }
    scrolling = true;
    lastScrollY = y;
}
