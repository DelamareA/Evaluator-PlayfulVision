#include "numberdata.h"

NumberData::NumberData(){

}

NumberData::~NumberData(){

}

unsigned int NumberData::toNumber() {
    return val;
}

Color NumberData::toColor() {
    return Color();
}

bool NumberData::isNumber() {
    return true;
}

bool NumberData::isColor() {
    return false;
}
