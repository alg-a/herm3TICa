#ifndef VHP_STREAMER
#define VHP_STREAMER

#include "ofMain.h"
#include "ofxJSONElement.h"
#include "VHPdata.h"
#include "ofxOsc.h"

//--------------------------------------------------------
class VHPstreamer {
    public:
    
        //constructor
        VHPstreamer();
        VHPstreamer(int _user_id, string _user_name);
    
        // variables
        int user_id;
        string user_name;
        vector<VHPdata> data;
    
        // methods
        void info();
        ofxOscMessage setData(ofxJSONElement& _s);
        string getData();
    
        
    private:
	
};
//--------------------------------------------------------

#endif 