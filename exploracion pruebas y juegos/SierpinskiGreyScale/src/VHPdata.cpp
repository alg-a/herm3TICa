#include "VHPdata.h"

//constructor

//----------------------------------------------------------------
VHPdata::VHPdata() {
    type = "toggle"; // trigger average
    active = false;
    on = false;
    addition = 0;
    average = 0.0;
    value = 0;
    last = 0.0;
}

// methods

//----------------------------------------------------------------

void VHPdata::setActive(bool _a) {
    active = _a;
    cout << "setActive(" << active << ")" << endl;
}

bool VHPdata::isActive() {
    return active;
}

//----------------------------------------------------------------

void VHPdata::setAddition(int _a) {
    addition = _a;
}

void VHPdata::add(int _a) {
    addition += _a;
}

int VHPdata::getAddition() {
    return addition;
}

//----------------------------------------------------------------

void VHPdata::setOn(bool _o) {
    on = _o;
}

bool VHPdata::getOn() {
    return on;
}

//----------------------------------------------------------------

void VHPdata::setValue(bool _v) {
    value = _v;
}

bool VHPdata::getValue() {
    return value;
}

//----------------------------------------------------------------

void VHPdata::setAddress(string _a) {
    address = _a;
}

string VHPdata::getAddress() {
    return address;
}

//----------------------------------------------------------------

void VHPdata::setType(int _t) {
    if (_t == 0) {
        type = "trigger";
    } else if (_t == 1) {
        type = "toggle";
    }  else if (_t == 2) {
        type = "average";
    }
}

string VHPdata::getType() {
    return type;
}

//----------------------------------------------------------------


void VHPdata::setAverage(int _t) {
    average = addition/_t;
    addition = 0;
}

float VHPdata::getAverage() {
    return average;
}

//----------------------------------------------------------------

void VHPdata::setLast(bool _l){
    last = _l;
}

void VHPdata::setLastAverage(float _a){
    lastAverage = (int) _a;
}

void VHPdata::updateLast() {
    setLast(value);
    setLastAverage(average);
}

bool VHPdata::getLast() {
    return last;
}

int VHPdata::getLastAverage() {
    return lastAverage;
}

bool VHPdata::isNew(){
    // cout << " last: " << last << " value: " << value << " on: " << on << endl;
    if ((type == "trigger")&&(last != value)) {
        return true;
    } else if ((type == "toggle")&&(last != value)) {
        if ((!value)&&(on)) {
            on = false;
            return true;
        } if ((!value)&&(!on)) {
            on = true;
            return true;
        } else {
            updateLast();
            return false;
        }
    } else if ((type == "average")&&(lastAverage != (int)average)) {
        return true;
    } else {
        return false;
    }
}