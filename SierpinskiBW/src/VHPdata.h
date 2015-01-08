#ifndef VHP_DATA
#define VHP_DATA

#include "ofMain.h"

//--------------------------------------------------------
class VHPdata {
public:
    
    //constructor
    VHPdata();
    
    // variables
    bool active;
    int value;
    string address;
    float average;
    
    // methods
    void setActive(bool _a);
    bool isActive();
    void setValue(int _v);
    void addValue(int _v);
    int getValue();
    void setAddress(string _a);
    string getAddress();
    void setAverage(int _t);
    int getAverage();
    
private:
	
};
//--------------------------------------------------------

#endif