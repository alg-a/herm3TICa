#ifndef VHP_DATA
#define VHP_DATA

#include "ofMain.h"

//--------------------------------------------------------
class VHPdata {
    public:
    
        //constructor
        VHPdata();
        VHPdata(string _name, string _type);
    
        // variables
        string type;
        string name;
        string time;
        bool bool_value;
        int int_value;
        float float_value;
        ofColor color_value;
    
        // methods
        void info();
        string getInfo();
        void setData(bool _v);
        void setData(int _v);
        void setData(float _v);
        void setData(ofColor _v);
        bool getBoolData();
        int getIntData();
        float getFloatData();
        ofColor getColorData();
        void setTime(string _t);
    
    private:
	
};
//--------------------------------------------------------

#endif 