#ifndef VHP_DATA
#define VHP_DATA

#include "ofMain.h"

//--------------------------------------------------------
class VHPdata {
    public:
    
        //constructor
        VHPdata();
    
        // variables
        bool        active;
        string      address;
        string      type;
        int         addition;
        float       average;
        int         lastAverage;
        bool        on;
        bool        value;
        bool        last;
    
        // methods
        void setActive(bool _a);
        bool isActive();
    
        void setAddition(int _a);
        void add(int _a);
        int getAddition();
    
        void setOn(bool _o);
        bool getOn();
    
        void setValue(bool _v);
        bool getValue();
    
        void setAddress(string _a);
        string getAddress();
    
        void setType(int _t);
        string getType();
    
        void setAverage(int _t);
        float getAverage();
    
        void setLast(bool _l);
        void updateLast();
        bool getLast();
        bool isNew();
        void setLastAverage(float _a);
        int getLastAverage();
    
    private:
	
};
//--------------------------------------------------------

#endif