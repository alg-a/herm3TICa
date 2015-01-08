#include "VHPdata.h"

//constructor

//----------------------------------------------------------------
VHPdata::VHPdata() {
    active = false;
    value = 0;
}

// methods

//----------------------------------------------------------------

void VHPdata::setActive(bool _a) {
    active = _a;
}

bool VHPdata::isActive() {
    return active;
}

void VHPdata::setValue(int _v) {
    value = _v;
}

void VHPdata::addValue(int _v) {
    value += _v;
}

int VHPdata::getValue() {
    return value;
}

void VHPdata::setAddress(string _a) {
    address = _a;
}

string VHPdata::getAddress() {
    return address;
}

void VHPdata::setAverage(int _t) {
    average = value/_t;
    value = 0;
}

int VHPdata::getAverage() {
    return (int)average;
}

//----------------------------------------------------------------

