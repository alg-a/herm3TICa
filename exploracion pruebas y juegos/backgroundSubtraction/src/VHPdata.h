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
        string address;
        int addition;
        float average;
        bool value;
        bool last;
    
        // methods
        void setActive(bool _a);
        bool isActive();
    
        void setAddition(int _a);
        void add(int _a);
        int getAddition();
    
        void setValue(bool _v);
        bool getValue();
    
        void setAddress(string _a);
        string getAddress();
    
        void setAverage(int _t);
        int getAverage();
    
        void setLast(bool _l);
        void updateLast();
        bool getLast();
        bool isNew();

    
    private:
	
};
//--------------------------------------------------------

#endif