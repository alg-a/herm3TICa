#ifndef _VHP_DATA
#define _VHP_DATA

#include "ofMain.h"

//--------------------------------------------------------
class VHPdata {
    public:
    
        //constructor
        VHPdata();
        VHPdata(int _n, int _x, int _y, int _w, int _h, string _a, int _l);
        VHPdata(int _x, int _y, int _w, int _h);
    
        // variables
        ofVec2f         vector;
        int             pixelNum;
        int             width;
        int             height;
        bool            active;
        bool            on;
        bool            value;
        bool            lastValue;
        int             average;
        int             lastAverage;
        int             type;
        string          address;
        int             l;
        ofColor         color;
        ofColor         grey;
    
         
        // methods
        void draw();
        void drawColor(int _n);
    
        void setActive(bool _a);
        bool isActive();
    
        void setAverage(int _a);
        int getAverage();
    
        void setOn(bool _o);
        bool getOn();
    
        void setValue(bool _v);
        bool getValue();
    
        void setAddress(string _a);
        string getAddress();
    
        void setType(int _t);
        int getType();
    
        void setLastValue(bool _l);
        void setLastAverage(int _a);
        void updateLast();
        bool getLastValue();
        int getLastAverage();
        bool isNew();
    
        private:
	
};
//--------------------------------------------------------

#endif