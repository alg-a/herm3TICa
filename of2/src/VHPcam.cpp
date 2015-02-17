#include "VHPcam.h"

//constructor

//----------------------------------------------------------------	
VHPcam::VHPcam() {
    
}

// methods

//----------------------------------------------------------------
void VHPcam::setup(int _w, int _h, int _d, int _f, string _ffmpeg, int _n, int _nb) {
    
    // video setup
    camWidth 		= _w;	// try to grab at this size.
	camHeight 		= _h;
	totalPixels     = camWidth * camHeight * 3;
    
    // contrast
	contrast.setup();
    
    //we can now get back a list of devices.
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName;
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl;
        }
	}
    
    cout << "DeviceID: " << _d << " FrameRate: " << _f << " camWidth: " << camWidth << " camHeight: " << camHeight  << endl;
    vidGrabber.setVerbose(true);
    vidGrabber.setDeviceID(_d);
	//vidGrabber.setDesiredFrameRate(_f);
    
    // Video devices
    for(int i = 0; i < videoDevices.size(); i++){
        cout << videoDevices[i] << endl;
    }
    
    // init grabber
    vidGrabber.initGrabber(camWidth*2,camHeight*2);
    
    
    
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    //mClient.set("","Simple Server");
    vidClient.setup();
    vidClient.set("ipCam","");
    
    
    // allocate the frame buffer object
    // Cam
    invertFbo.allocate(camWidth*2, camHeight*2, GL_RGB, 0);
    greyFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    sustractFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    fboBlurOnePass.allocate(camWidth, camHeight, GL_RGB, 0);
    fboBlurTwoPass.allocate(camWidth, camHeight, GL_RGB, 0);
    adjFbo.allocate(camWidth, camHeight, GL_RGB, 0);
    extraFbo.allocate(camWidth*2, camHeight*2, GL_RGB, 0);
    // Video
    maskFbo.allocate(camWidth*2, camHeight*2, GL_RGB, 0);
    stelaFbo.allocate(camWidth*2, camHeight*2, GL_RGB, 0);
    contrastFbo.allocate(camWidth*2, camHeight*2, GL_RGB, 0);
    recorderFbo.allocate(camWidth*2, camHeight*2, GL_RGB, 0);
    
    // allocate textures
    // Cam
    videoTexture.allocate(camWidth*2, camHeight*2, GL_RGB);
    greyTexture.allocate(camWidth, camHeight, GL_RGB);
    background.allocate(camWidth, camHeight, GL_RGB);
    adjTexture.allocate(camWidth, camHeight, GL_RGB);
    // Video
    contrastTexture.allocate(camWidth*2, camHeight*2, GL_RGB);
    playerTexture.allocate(camWidth*2, camHeight*2, GL_RGB);
    recorderTexture.allocate(camWidth*2, camHeight*2, GL_RGB);
    stelaTexture.allocate(camWidth*2, camHeight*2, GL_RGB);
    
    // allocate ofxCv Images
    greyImage.allocate(camWidth,camHeight);
    colorImage.allocate(camWidth,camHeight);
    
    // width + height for sierpinski
    w[0] = 1460; // 1458 + 2 (*1)
    h[0] = 729;
    th[0] = 1458.0*camHeight/camWidth;
	w[1] = 488; // 486 + 2 (*3)
    h[1] = 243;
    th[1] = 486.0*camHeight/camWidth;
	w[2] = 164; // 162 + 2 (*9)
    h[2] = 81;
    th[2] = 162.0*camHeight/camWidth;
    w[3] = 56; // 54 + 2 (*27)
    h[3] = 27;
    th[3] = 54.0*camHeight/camWidth;
	w[4] = 20; // 18 + 2 (*81)
    h[4] = 9;
    th[4] = 18.0*camHeight/camWidth;
	w[5] = 8; // 6 + 2 (*243)
    h[5] = 3;
    th[5] = 6.0*camHeight/camWidth;
    
    // allocate the frame buffer object
    for (int i=0; i<6; i++) {
        Fbo[i].allocate(w[i], h[i], GL_RGB, 0);
        Texture[i].allocate(w[i], h[i], GL_RGB);
        Texture[i].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }
    
    // allocate the frame buffer object => SierpinskiData
    for (int i=0; i<6; i++) {
        sierpinskiFbo[i].allocate(w[i], h[i], GL_RGB, 0);
        sierpinskiTexture[i].allocate(w[i], h[i], GL_RGB);
        sierpinskiTexture[i].setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }
    doAlpha = 0;
    sierpinskiMixture = 0.3;
    
    // Grid
    gridFbo.allocate(w[4], h[4], GL_RGB, 0);
    gridTexture.allocate(w[4], h[4], GL_RGB);
    gridTexture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    //shaders
    #ifdef TARGET_OPENGLES
	greyShader.load("shaders_gles/greyscale");
    sustractShader.load("shaders_gles/sustraction");
    invertShader.load("shaders_gles/invert");
    maskShader.load("shaders_gles/mask");
	stelaShader.load("shaders_gles/stela");
    shaderBlurX.load("shaders_gles/shaderBlurX");
    shaderBlurY.load("shaders_gles/shaderBlurY");
    adjShader.load("shaders_gles/adjustment");
	contrastShader.load("shaders_gles/contrast");
	sierpinskiShader.load("shaders_gles/sierpinski");
    alphaShader.load("shaders_gles/alpha");
    holeShader.load("shaders_gles/hole");
    cout << "shadersES2" << endl;
    #else
	if(ofGetGLProgrammableRenderer()){
		greyShader.load("shaders_gl3/greyscale");
        sustractShader.load("shaders_gl3/sustraction");
        invertShader.load("shaders_gl3/invert");
        maskShader.load("shaders_gl3/mask");
		stelaShader.load("shaders_gl3/stela");
        shaderBlurX.load("shaders_gl3/shaderBlurX");
        shaderBlurY.load("shaders_gl3/shaderBlurY");
        adjShader.load("shaders_gl3/adjustment");
		contrastShader.load("shaders_gl3/contrast");
        sierpinskiShader.load("shaders_gl3/sierpinski");
        alphaShader.load("shaders_gl3/alpha");
        holeShader.load("shaders_gl3/hole");
        cout << "shadersGL3" << endl;
	}else{
		greyShader.load("shaders/greyscale");
        sustractShader.load("shaders/sustraction");
        invertShader.load("shaders/invert");
        maskShader.load("shaders/mask.vert");
		stelaShader.load("shaders/stela");
		shaderBlurX.load("shaders/shaderBlurX");
        shaderBlurY.load("shaders/shaderBlurY");
        adjShader.load("shaders/adjustment");
		contrastShader.load("shaders/contrast");
        sierpinskiShader.load("shaders/sierpinski");
        alphaShader.load("shaders/alpha");
        holeShader.load("shaders/hole");
        cout << "shadersGL2" << endl;
	}
    #endif
    
    // recorder
    recorder.setFfmpegLocation(_ffmpeg);
    
    // recording variables
    recordingNum = _n;
    playingNum = 0;
    newRecording = "";
    fileBeingRecorded = "";
    recording = false;
    playing = false;
    syphon = false;
    sustract = true;
    negative = false;
    BkgNum = _nb;
    playingBkgNum = 0;
    playingBkg = false;
    invert = false;
    streaming = false;
    
    x = 0;
    blur = 0.0;
    min = 0.0;
    max = 1.0;
    grid.init(18, 9, 81, 81);
    sierpinski.init();
    
    mode = 0;
    vidBackground = 0;
    maskColor.set(0, 0, 0);
    
    e[4] = 162;
    f[4] = 179;
    e[5] = 136;
    f[5] = 255;
}

void VHPcam::settings(int _stela, int _mixture, int _e0, int _f0, int _e1, int _f1, int _e2, int _f2, int _e3, int _f3, float _b, float _rb, float _rw){
    percent[0] = ofClamp(_stela, 0, 1000);
    percent[1] = ofClamp(_mixture, 0, 1000);
    setContrast(0, _e0, _f0);
    setContrast(1, _e1, _f1);
    setContrast(2, _e2, _f2);
    setContrast(3, _e3, _f3);
    blur = _b;
    min = _rb;
    max = _rw;
}

//----------------------------------------------------------------
void VHPcam::update(ofxOscSender & _local_sender, ofxOscSender & _remote_sender) {
    
    vidGrabber.update();
    player.update();
    bkgPlayer.update();

    if (player.isPlaying()) playerTexture.loadData(player.getPixels(), camWidth*2, camHeight*2, GL_RGB);
    if (bkgPlayer.isPlaying()) background.loadData(bkgPlayer.getPixels(), camWidth, camHeight, GL_RGB);
    
    if (vidGrabber.isFrameNew()){
        
        videoTexture.loadData(vidGrabber.getPixels(), camWidth*2, camHeight*2, GL_RGB);
        
        // Syphon
        getSyphonVideo();
        
        // Invert
        invertVideo();
        
        // 0 interface, 1 sierpinski mago, 2 mascara + grid, 3 sierpinski styled, 4 Black holes white wall
        switch (mode) {
            case 0:
                // Adjust
                adjustVideo();
                // contourFinder
                findBlobs();
                // Mask
                mask();
                break;
            case 1:
                // SierpinskiData
                sierpinskiData(_local_sender);
                break;
            case 2:
                // Adjust
                adjustVideo();
                // Mask
                mask();
                // Grid
                gridStyle(_local_sender);
                break;
            case 3:
                // Adjust
                adjustVideo();
                // Mask
                mask();
                // Sierpinski styled
                sierpinskiStyle();
                // Grid
                gridStyle(_remote_sender);
                break;
            case 4:
                // Adjust
                adjustVideo();
                // contourFinder
                findBlobs();
                // Black holes white wall
                holes();
                break;
            default:
                break;
        }
     }
}

void VHPcam::getSyphonVideo() {
    if (syphon) {
        invertFbo.begin();
        vidClient.draw(0, 0, camWidth*2, camHeight*2);
        invertFbo.end();
        invertFbo.readToPixels(invertPix);
        videoTexture.loadData(invertPix.getPixels(), camWidth*2, camHeight*2, GL_RGB);
    }
}

void VHPcam::invertVideo() {
    if (invert) {
        invertFbo.begin();
        videoTexture.draw(camWidth*2, 0, -camWidth*2, camHeight*2);
        invertFbo.end();
        invertFbo.readToPixels(invertPix);
        videoTexture.loadData(invertPix.getPixels(), camWidth*2, camHeight*2, GL_RGB);
    }
}

void VHPcam::sustractBackground() {
    if (sustract) {
        // Sustract
        sustractFbo.begin();
        sustractShader.begin();
        sustractShader.setUniformTexture("texBKG", background, 1);
        greyFbo.draw(0, 0, camWidth, camHeight);
        sustractShader.end();
        sustractFbo.end();
        sustractFbo.readToPixels(sustractPix);
    }
}

void VHPcam::negativeVideo() {
    if (negative) {
        // Invert to negative
        sustractFbo.begin();
        invertShader.begin();
        if (sustract) {
            sustractFbo.draw(0, 0, camWidth, camHeight);
        } else {
            greyFbo.draw(0, 0, camWidth, camHeight);
        }
        invertShader.end();
        sustractFbo.end();
        sustractFbo.readToPixels(sustractPix);
    }
}

void VHPcam::adjustVideo() {
    // Grey
    greyFbo.begin();
    greyShader.begin();
    videoTexture.draw(0, 0, camWidth, camHeight);
    greyShader.end();
    greyFbo.end();
    greyFbo.readToPixels(greyPix);
    
    sustractBackground();
    negativeVideo();
    
    // Blur X
    fboBlurOnePass.begin();
    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur);
    if ((negative)||(sustract)) {
        sustractFbo.draw(0, 0, camWidth, camHeight);
    } else {
        greyFbo.draw(0, 0, camWidth, camHeight);
    }
    shaderBlurX.end();
    fboBlurOnePass.end();
    
    // Blur Y
    fboBlurTwoPass.begin();
    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur);
    fboBlurOnePass.draw(0, 0, camWidth, camHeight);
    shaderBlurY.end();
    fboBlurTwoPass.end();
    
    // Adjust
    adjFbo.begin();
    adjShader.begin();
    adjShader.setUniformTexture("texE", contrast.texture[e[0]], 1);
    adjShader.setUniform1f("f", f[0]);
    adjShader.setUniform1f("minColor", min);
    adjShader.setUniform1f("maxColor", max);
    fboBlurTwoPass.draw(0, 0, camWidth, camHeight);
    adjShader.end();
    adjFbo.end();
    adjFbo.readToPixels(adjPix);
    adjTexture.loadData(adjPix.getPixels(), camWidth, camHeight, GL_RGB);
}

void VHPcam::findBlobs() {
    colorImage.setFromPixels(adjPix);
    greyImage.setFromColorImage(colorImage);
    contourFinder.findContours(greyImage, 60, (camWidth*camHeight)/2, 12, true);
}

void VHPcam::mask() {
    
    // Mask
    maskFbo.begin();
    switch (vidBackground) {
        case 0:
            ofClear(maskColor);
            break;
        case 1:
            stelaTexture.draw(0, 0, camWidth*2, camHeight*2);
            break;
        case 2:
            playerTexture.draw(0, 0, camWidth*2, camHeight*2);
            break;
        default:
            break;
    }
    maskShader.begin();
    maskShader.setUniformTexture("mask", adjTexture, 1);
    videoTexture.draw(0, 0, camWidth*2, camHeight*2);
    maskShader.end();
    maskFbo.end();
    maskFbo.readToPixels(maskPix);
    
    // Stela
    stelaFbo.begin();
    stelaShader.begin();
    stelaShader.setUniformTexture("tex1", stelaTexture, 1);
    stelaShader.setUniform1f("mixture", percent[0]/1000.0);
    maskFbo.draw(0, 0, camWidth*2, camHeight*2);
    stelaShader.end();
    stelaFbo.end();
    // copy the frame buffer pixels
    stelaFbo.readToPixels(stelaPix);
    stelaTexture.loadData(stelaPix.getPixels(), camWidth*2, camHeight*2, GL_RGB);
    
    // Contraste Final
    contrastFbo.begin();
    contrastShader.begin();
    contrastShader.setUniformTexture("texE1", contrast.texture[e[1]], 1);
    contrastShader.setUniformTexture("texE2", contrast.texture[e[2]], 2);
    contrastShader.setUniformTexture("texE3", contrast.texture[e[3]], 3);
    contrastShader.setUniform1f("f1", f[1]);
    contrastShader.setUniform1f("f2", f[2]);
    contrastShader.setUniform1f("f3", f[3]);
    stelaFbo.draw(0, 0, camWidth*2, camHeight*2);
    contrastShader.end();
    contrastFbo.end();
}


//----------------------------------------------------------------

void VHPcam::sierpinskiData(ofxOscSender & _sender) {
    for (int i=0; i<6; i++) {
        sierpinskiFbo[i].begin();
        ofClear(0, 0, 0, 255);
        //contrastFbo.draw(0, 0, dw[i]-2, dh[i]);
        videoTexture.draw(0, 0, w[i]-2, th[i]);
        sierpinskiFbo[i].end();
        sierpinskiFbo[i].readToPixels(sierpinskiPix[i]);
        sierpinskiTexture[i].loadData(sierpinskiPix[i].getPixels(), w[i], h[i], GL_RGB);
    }
    sierpinski.update(sierpinskiPix[5].getPixels(), sierpinskiPix[4].getPixels(), sierpinskiPix[3].getPixels(), _sender);
}

//----------------------------------------------------------------

void VHPcam::gridStyle(ofxOscSender & _sender) {
    // Grid
    gridFbo.begin();
    ofClear(0, 0, 0, 255);
    adjTexture.draw(0, 0, w[4]-2, th[4]);
    gridFbo.end();
    gridFbo.readToPixels(gridPix);
    grid.update(gridPix.getPixels(), 2, _sender);
    gridTexture.loadData(gridPix.getPixels(), w[4], h[4], GL_RGB);
}

//----------------------------------------------------------------

void VHPcam::sierpinskiStyle() {
    // Sierpinski
    for (int i=0; i<6; i++) {
        Fbo[i].begin();
        ofClear(0, 0, 0, 255);
        contrastFbo.draw(0, 0, w[i]-2, th[i]);
        Fbo[i].end();
        Fbo[i].readToPixels(Pix[i]);
        Texture[i].loadData(Pix[i].getPixels(), w[i], h[i], GL_RGB);
    }
}

//----------------------------------------------------------------

void VHPcam::holes() {
    extraFbo.begin();
    ofClear(255, 255, 255, 255);
    ofPushStyle();
    for (int i = 0; i < contourFinder.nBlobs; i++){
        if(contourFinder.blobs[i].hole) {
            for (int o = 0; o<20; o++) {
                ofSetColor(0, 0, 0, o*o/5 + 20);
                ofFill();
                ofSetLineWidth(1.5);
                ofBeginShape();
                int s = 20 - o;
                for (int u = 0; u < contourFinder.blobs[i].pts.size(); u++){
                    
                    ofVec3f v = contourFinder.blobs[i].centroid*2 - contourFinder.blobs[i].pts[u]*2;
                    ofVec3f p = contourFinder.blobs[i].pts[u]*2 + v*s*s/300;
                    ofVertex(p.x, p.y);
                    // ofCurveVertex
                }
                ofVec3f v = contourFinder.blobs[i].centroid*2 - contourFinder.blobs[i].pts[0]*2;
                ofVec3f p = contourFinder.blobs[i].pts[0]*2 + v*s*s/300;
                ofVertex(p.x, p.y);
                ofEndShape();
            }
        }
    }
    ofPopStyle();
    extraFbo.end();
    extraFbo.readToPixels(extraPix);
    // Stela
    stelaFbo.begin();
    stelaShader.begin();
    stelaShader.setUniformTexture("tex1", stelaTexture, 1);
    stelaShader.setUniform1f("mixture", percent[0]/1000.0);
    extraFbo.draw(0, 0, camWidth*2, camHeight*2);
    stelaShader.end();
    stelaFbo.end();
    // copy the frame buffer pixels
    stelaFbo.readToPixels(stelaPix);
    stelaTexture.loadData(stelaPix.getPixels(), camWidth*2, camHeight*2, GL_RGB);
    // Contraste Final
    contrastFbo.begin();
    contrastShader.begin();
    contrastShader.setUniformTexture("texE1", contrast.texture[e[1]], 1);
    contrastShader.setUniformTexture("texE2", contrast.texture[e[2]], 2);
    contrastShader.setUniformTexture("texE3", contrast.texture[e[3]], 3);
    contrastShader.setUniform1f("f1", f[1]);
    contrastShader.setUniform1f("f2", f[2]);
    contrastShader.setUniform1f("f3", f[3]);
    stelaFbo.draw(0, 0, camWidth*2, camHeight*2);
    contrastShader.end();
    contrastFbo.end();
    // copy the frame buffer pixels
    contrastFbo.readToPixels(contrastPix);
    contrastTexture.loadData(contrastPix.getPixels(), camWidth*2, camHeight*2, GL_RGB);
}

//----------------------------------------------------------------

void VHPcam::draw() {
    int n;
    switch (mode) {
        case 0: // Working Interface
            drawInterface();
            break;
        case 1: // SierpinskiData mago + grid
            drawSierpinskiData();
            break;
        case 2: // mascara + grid
            gridTexture.draw(0, 0, w[4]*h[0]/h[4], h[0]);
            drawGrid();
            break;
        case 3: // Advanced sierpinski
            drawSierpinskiStyle();
            break;
        case 4: // holes
            drawHoles();
            break;
        default:
            videoTexture.draw(0,0);
            // do nithing
            break;
    }
    if(recording){
        recorderTexture.loadScreenData(0, 0, camWidth*2, camHeight*2);
        recorderFbo.begin();
        recorderTexture.draw(0, 0, camWidth*2, camHeight*2);
        recorderFbo.end();
        recorderFbo.readToPixels(recorderPix);
        recorder.addFrame(recorderPix);
    }
}

void VHPcam::drawInterface() {
    greyFbo.draw(0, 0, camWidth, camHeight);
    background.draw(camWidth*3/4, camHeight*3/4, camWidth/4, camHeight/4);
    sustractFbo.draw(camWidth, 0, camWidth, camHeight);
    //fboBlurTwoPass.draw(0, camHeight, camWidth, camHeight);
    adjFbo.draw(0, camHeight, camWidth, camHeight);
    maskFbo.draw(camWidth, camHeight, camWidth, camHeight);
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(camWidth, camHeight);
        ofSetColor(255);
        if(contourFinder.blobs[i].hole){
            ofDrawBitmapString("hole",
                               contourFinder.blobs[i].boundingRect.getCenter().x + camWidth,
                               contourFinder.blobs[i].boundingRect.getCenter().y + camHeight);
        }
    }
    ofPushStyle();
    ofSetHexColor(0xffffff);
    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), camWidth*2 - 160, camHeight*2 - 10);
    ofDrawBitmapString("Num blobs found: " + ofToString(contourFinder.nBlobs), camWidth*2 - 160, camHeight*2 - 24);
    ofPopStyle();
}

void VHPcam::drawSierpinskiData() {
    int n;
    /* n = 243;
     for (int i=0; i<6; i++) {
     alphaShader.begin();
     alphaShader.setUniform1f("alpha", sierpinskiMixture);
     alphaShader.setUniform1i("doAlpha", doAlpha);
     sierpinskiTexture[5-i].draw(0, 0, w[5-i]*n, h[5-i]*n);
     alphaShader.end();
     n /= 3;
     }*/
    n = 1;
    for (int i=0; i<6; i++) {
        alphaShader.begin();
        alphaShader.setUniform1f("alpha", sierpinskiMixture);
        alphaShader.setUniform1i("doAlpha", doAlpha);
        sierpinskiTexture[i].draw(0, 0, w[i]*n, h[i]*n);
        alphaShader.end();
        n *= 3;
    }
    sierpinski.draw();
    ofPushStyle();
    ofSetHexColor(0xffffff);
    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), camWidth*2 - 160, camHeight*2 - 10);
    ofPopStyle();
}

void VHPcam::drawGrid() {
    
    alphaShader.begin();
    alphaShader.setUniform1f("alpha", sierpinskiMixture);
    alphaShader.setUniform1i("doAlpha", doAlpha);
    //contrastFbo.draw(0, 0, camWidth*2, camHeight*2);
    contrastFbo.draw(0, 0, w[0], h[0]);
    alphaShader.end();
    
    
    ofPushStyle();
    ofSetHexColor(0xffffff);
    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), camWidth*2 - 260, camHeight*2 - 10);
    ofDrawBitmapString("peso: " + ofToString(grid.total_weight), camWidth*2 - 260, camHeight*2 - 24);
    ofPopStyle();
    ofVec2f v = grid.getVector();
    ofDrawBitmapString("grid vector: " + ofToString(v.x) +" " + ofToString(v.y), camWidth*2 - 260, camHeight*2 - 38);
    grid.draw();
}

void VHPcam::drawSierpinskiStyle() {
    int n;
    /* n = 1;
     for (int i=0; i<6; i++) {
     sierpinskiShader.begin();
     Texture[i].draw(camWidth*2, 0, w[i]*n, h[i]*n);
     sierpinskiShader.end();
     n *= 3;
     }*/
    ofPushStyle();
    ofSetColor(maskColor);
    ofFill();
    ofRect(0, 0, w[0], h[0]);
    ofPopStyle();
    n = 243;
    for (int i=0; i<6; i++) {
        sierpinskiShader.begin();
        Texture[5-i].draw(0, 0, w[5-i]*n, h[5-i]*n);
        sierpinskiShader.end();
        n /= 3;
    }
}

void VHPcam::drawHoles() {
    holeShader.begin();
    holeShader.setUniformTexture("texE1", contrast.texture[e[4]], 1);
    holeShader.setUniformTexture("texE2", contrast.texture[e[5]], 2);
    holeShader.setUniformTexture("mask", contrastTexture, 3);
    holeShader.setUniform1f("f1", f[4]);
    holeShader.setUniform1f("f2", f[5]);
    videoTexture.draw(0, 0, camWidth*2, camHeight*2);
    holeShader.end();
    contrastTexture.draw(camWidth*3/2, camHeight*3/2, camWidth/2, camHeight/2);
    ofPushStyle();
    ofSetHexColor(0x000000);
    ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()), camWidth*2 - 260, camHeight*2 - 10);
    ofPopStyle();
}

//----------------------------------------------------------------

void VHPcam::setContrast(int _n, float _e, float _f) {
    _n = ofClamp(_n, 0, 5);
    e[_n] = (int) ofClamp(_e, 0, 255);
    f[_n] = (int) ofClamp(_f, 0, 255);
    cout << "e["<< _n << "]: "<< e[_n] << ", f[" << _n << "]: "<< f[_n] << endl;
}

void VHPcam::setMode(int _m) {
    // 0 interface, 1 sierpinski mago, 2 mascara + grid, 3 sierpinski styled, 4 Black holes white wall
    if ((mode==1)&&(_m!=1)) {
        if (streaming) sierpinski.streamer.stop();
    } else if ((mode!=1)&&(_m==1)) {
        if (streaming) sierpinski.streamer.start();
    } else if ((mode==2)&&(_m!=2)) {
        if (streaming) grid.streamer.stop();
    } else if ((mode!=2)&&(_m==2)) {
        if (streaming) grid.streamer.start();
    }
    mode = _m;
}

//----------------------------------------------------------------

void VHPcam::save(int _s) {
    if (_s == 0) {
        if(recording) {
            recorder.close();
            newRecording = fileBeingRecorded;
            recording = false;
        }
    } else if (_s == 1){
        if(!recording) {
            recorder.setup("saved/clip_"+ ofToString(recordingNum) +".mov", camWidth*2, camHeight*2, 30);
            fileBeingRecorded = "saved/clip_"+ ofToString(recordingNum) +".mov";
            recording = true;
            recordingNum++;
        }
    }
}

//----------------------------------------------------------------

void VHPcam::play(int _p, int _n) {
    if (_p == 0) {
        if(playing) {
            player.stop();
            playing = false;
        }
    } else if (_p == 1){
        if(!playing) {
            playing = load(_n);
        }
    }
}

void VHPcam::playBkg(int _p, int _n) {
    if (_p == 0) {
        if(playingBkg) {
            bkgPlayer.stop();
            playingBkg = false;
        }
    } else if (_p == 1){
        if(!playingBkg) {
            playingBkg = loadBkg(_n);
        }
    }
}

//----------------------------------------------------------------

string VHPcam::getNewRecording() {
    return newRecording;
}

void VHPcam::emptyNewRecording() {
    newRecording = "";
}

//----------------------------------------------------------------

bool VHPcam::load(int _n){
	bool exists = player.loadMovie("recorded/clip_"+ofToString(_n)+".mov");
    if (exists) player.play();
    return exists;
}

bool VHPcam::loadBkg(int _n){
	bool exists = bkgPlayer.loadMovie("recorded/clip_grey_"+ofToString(_n)+".mov");
    if (exists) bkgPlayer.play();
    return exists;
}

//----------------------------------------------------------------

void VHPcam::updateBkg() {
    background.loadData(greyPix.getPixels(), camWidth, camHeight, GL_RGB);
}

//----------------------------------------------------------------
