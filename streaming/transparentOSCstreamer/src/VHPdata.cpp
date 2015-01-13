#include "VHPdata.h"

//constructor

//----------------------------------------------------------------	
VHPdata::VHPdata() {
}
VHPdata::VHPdata(string _name, string _type) {
    name = _name;
    type = _type;
}

// methods

//----------------------------------------------------------------

void VHPdata::setData(bool _v) {
    bool_value = _v;
}

void VHPdata::setData(int _v) {
    int_value = _v;
}

void VHPdata::setData(float _v) {
    float_value = _v;
}

void VHPdata::setData(ofColor _v) {
    color_value = _v;
}

//----------------------------------------------------------------

bool VHPdata::getBoolData() {
    return bool_value;
}

int VHPdata::getIntData() {
    return int_value;
}

float VHPdata::getFloatData() {
    return float_value;
}

ofColor VHPdata::getColorData() {
    return color_value;
}

//----------------------------------------------------------------

void VHPdata::setTime(string _t){
    time = _t;
}

//----------------------------------------------------------------

void VHPdata::info() {
    cout << "name: " << name << ", type: " << type << endl;
}

string VHPdata::getInfo() {
    return "name: "+ name + ", type: "+ type;
}