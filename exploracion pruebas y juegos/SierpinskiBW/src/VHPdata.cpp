#include "VHPdata.h"

//constructor

//----------------------------------------------------------------
VHPdata::VHPdata() {
    active = false;
    addition = 0;
    average = 0.0;
    value = 0;
    last = 0.0;
}

// methods

//----------------------------------------------------------------

void VHPdata::setActive(bool _a) {
    active = _a;
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

void VHPdata::setAverage(int _t) {
    average = addition/_t;
    addition = 0;
}

int VHPdata::getAverage() {
    return (int)average;
}

//----------------------------------------------------------------

void VHPdata::setLast(bool _l){
    last = _l;
}

void VHPdata::updateLast() {
    setLast(value);
}

bool VHPdata::getLast() {
    return last;
}

bool VHPdata::isNew(){
    if (last != value) {
        return true;
    } else {
        return false;
    }
}

//----------------------------------------------------------------

