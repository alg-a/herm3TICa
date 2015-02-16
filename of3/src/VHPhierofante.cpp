#include "VHPhierofante.h"

//constructor

//----------------------------------------------------------------	
VHPhierofante::VHPhierofante() {
}

// methods

//----------------------------------------------------------------

void VHPhierofante::setup(ofxXmlSettings _settings){
    n = _settings.getNumTags("IMAGE_HIEROFANTE");
    for(int i = 0; i < n; i++){
        string image = _settings.getValue("IMAGE_HIEROFANTE", "", i);
        int w = _settings.getValue("MARGIN_W", 0, i);
        int h = _settings.getValue("MARGIN_H", 0, i);
        img_hierofante.push_back(ofImage());
        img_margin.push_back(ofVec2f(w, h));
        img_hierofante[i].loadImage(image);
        cout << image << " width: " << img_hierofante[i].getWidth() << " height: " << img_hierofante[i].getHeight() << endl;
    }
    center.set(0, 1400);
    for(int i = 0; i < n; i++){
        int w = img_margin[i].x - img_hierofante[0].getWidth()/2 + img_hierofante[i].getWidth()/2;
        int h = img_margin[i].y - img_hierofante[0].getHeight()/2 + img_hierofante[i].getHeight()/2;
        if (i==2) {
            h -= img_hierofante[i].getHeight()/2;
        } else if (i==5) {
            w += img_hierofante[i].getWidth()/2;
            h += img_hierofante[i].getHeight()/2;
        } else if (i==6) {
            w -= img_hierofante[i].getWidth()/2;
            h += img_hierofante[i].getHeight()/2;
        } else if (i==8) {
            h -= img_hierofante[i].getHeight()/2;
        }
        img_position.push_back(ofVec2f(w, h));
        img_size.push_back(ofVec2f(img_hierofante[i].getWidth(), img_hierofante[i].getHeight()));
    }
    mouth.set(1,1);
    eyebrow.set(1,1);
    eyes.set(0.5, 0.5);
    jaw = 1;
    receiver.setup(8338);
}

//----------------------------------------------------------------

void VHPhierofante::update(){
    while(receiver.hasWaitingMessages()) {
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        if (m.getAddress() == "/gesture/eye/left") {
            scaleEyeL(m.getArgAsFloat(0));
            cout << "/gesture/eye/left " << m.getArgAsFloat(0) << endl;
        } else if (m.getAddress() == "/gesture/eye/right") {
            scaleEyeR(m.getArgAsFloat(0));
            cout << "/gesture/eye/right " << m.getArgAsFloat(0) << endl;
        } else if (m.getAddress() == "/gesture/mouth/width") {
            scaleMouthW(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/gesture/mouth/height") {
            scaleMouthH(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/gesture/jaw") {
            scaleJaw(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/pose/position") {
            setCenter(m.getArgAsFloat(0), m.getArgAsFloat(1));
        } else if (m.getAddress() == "/pose/scale") {
            setScale(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/gesture/eyebrow/left") {
            //scaleEyebrowW(m.getArgAsFloat(0));
            scaleEyebrowHL(m.getArgAsFloat(0));
        } else if (m.getAddress() == "/gesture/eyebrow/right") {
            scaleEyebrowHR(m.getArgAsFloat(0));
        }
    }
}

//--------------------------------------------------------------

void VHPhierofante::scaleEyeL(float _l){
    eyes.x = ofMap(_l, 1.9, 3.4, 0.0, 1.0, true);
    // eyes.x = _l;
    float scale = 0.7 + 0.4 * eyes.x;
    img_size[3].set(img_hierofante[3].getWidth() * scale, img_hierofante[3].getHeight() * scale);
}

//--------------------------------------------------------------

void VHPhierofante::scaleEyeR(float _r){
    eyes.y = ofMap(_r, 1.7, 3.5, 0.0, 1.0, true);
    //eyes.y = _r;
    float scale = 0.7 + 0.4 * eyes.y;
    img_size[4].set(img_hierofante[4].getWidth() * scale, img_hierofante[4].getHeight() * scale);
}

//--------------------------------------------------------------

void VHPhierofante::scaleMouthW(float _w){
    mouth.x = ofMap(_w, 5.9, 20.1, 0.0, 1.0, true);
    // mouth.x = _w;
    float scale = 0.5 + 0.8 * mouth.x;
    img_size[9].x = img_hierofante[9].getWidth() * scale;
}

//--------------------------------------------------------------

void VHPhierofante::scaleMouthH(float _h){
    mouth.y = ofMap(_h, 0.6, 7.9, 0.0, 1.0, true);
    //mouth.y = _h;
    float scale = 0.6 + 1.4 * mouth.y;
    img_size[9].y = img_hierofante[9].getHeight() * scale;
    
    scale = 0.8 + 0.2 * (1 - mouth.y);
    img_size[8].y = img_hierofante[8].getHeight() * scale;
}

//--------------------------------------------------------------

void VHPhierofante::scaleEyebrowW(float _w){
    eyebrow.x = ofMap(_w, 6.3, 11.7, 0.0, 1.0, true);
    //eyebrow.x = _w;
    float scale = 0.7 + 0.6 * eyebrow.x;
    img_size[5].x = img_hierofante[5].getWidth() * scale;
    img_size[6].x = img_hierofante[6].getWidth() * scale;
}

//--------------------------------------------------------------

void VHPhierofante::scaleEyebrowHL(float _h){
    eyebrow.y = ofMap(_h, 6.5, 11.6, 0.0, 1.0, true);
    // eyebrow.y = _h;
    float scale = 0.8 + 0.3 * eyebrow.y;
    img_size[5].y = img_hierofante[5].getWidth() * scale;
}

//--------------------------------------------------------------

void VHPhierofante::scaleEyebrowHR(float _h){
    eyebrow.y = ofMap(_h, 6.5, 11.6, 0.0, 1.0, true);
    // eyebrow.y = _h;
    float scale = 0.8 + 0.3 * eyebrow.y;
    img_size[6].y = img_hierofante[6].getWidth() * scale;
}

//--------------------------------------------------------------

void VHPhierofante::scaleJaw(float _j){
    jaw = ofMap(_j, 16.1, 29.3, 0.0, 1.0, true);
    // jaw = _j;
    float scale = 1 + 0.1 * jaw;
    img_size[2].y = img_hierofante[2].getHeight() * scale;
}

//--------------------------------------------------------------

void VHPhierofante::setCenter(float _x, float _y){
    center.x = ofMap(_x, 0.0, 560, -300.0, 300, true);
    center.y = 1400 + ofMap(_y, 0.0, 370, -300.0, 300, true);
}

void VHPhierofante::setScale(float _z){
    center.z = ofMap(_z, 1.6, 10.3, -1000.0, 0, true);
    // z -1200 200
}

//--------------------------------------------------------------

void VHPhierofante::draw(){
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2+center.x, ofGetHeight()/2+center.y, center.z);
    
    // fondo
    img_hierofante[0].setAnchorPercent(0.5, 0.5);
    img_hierofante[0].draw(img_position[0].x, img_position[0].y, img_size[0].x, img_size[0].y);
    
    // cuello
    img_hierofante[1].setAnchorPercent(0.5, 0.5);
    img_hierofante[1].draw(img_position[1].x, img_position[1].y, img_size[1].x, img_size[1].y);
    
    // cara
    img_hierofante[2].setAnchorPercent(0.5, 0);
    img_hierofante[2].draw(img_position[2].x, img_position[2].y, img_size[2].x, img_size[2].y);
    
    // ojo l
    img_hierofante[3].setAnchorPercent(0.5, 0.5);
    img_hierofante[3].draw(img_position[3].x, img_position[3].y, img_size[3].x, img_size[3].y);
    
    // ojo d
    img_hierofante[4].setAnchorPercent(0.5, 0.5);
    img_hierofante[4].draw(img_position[4].x, img_position[4].y, img_size[4].x, img_size[4].y);
    
    // ceja l
    img_hierofante[5].setAnchorPercent(1, 1);
    img_hierofante[5].draw(img_position[5].x, img_position[5].y, img_size[5].x, img_size[5].y);
    
    // ceja r
    img_hierofante[6].setAnchorPercent(0, 1);
    img_hierofante[6].draw(img_position[6].x, img_position[6].y, img_size[6].x, img_size[6].y);
    
    // corona
    img_hierofante[7].setAnchorPercent(0.5, 0.5);
    img_hierofante[7].draw(img_position[7].x, img_position[7].y, img_size[7].x, img_size[7].y);
    
    float dif = img_size[2].y - img_hierofante[2].getHeight();
    
    // nariz
    img_hierofante[8].setAnchorPercent(0.5, 0);
    img_hierofante[8].draw(img_position[8].x, img_position[8].y, img_size[8].x, img_size[8].y + dif/2);
    
    // boca
    img_hierofante[9].setAnchorPercent(0.5, 0.5);
    img_hierofante[9].draw(img_position[9].x, img_position[9].y + dif/2, img_size[9].x, img_size[9].y);
    
    // barbilla
    img_hierofante[10].setAnchorPercent(0.5, 0.5);
    img_hierofante[10].draw(img_position[10].x, img_position[10].y + dif/2, img_size[10].x, img_size[10].y);
    
    ofPopMatrix();
    
}
//--------------------------------------------------------------

