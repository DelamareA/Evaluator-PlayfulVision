#include "colordata.h"

ColorData::ColorData() {

}

ColorData::~ColorData() {

}

unsigned int ColorData::toNumber() {
    return 0;
}

Color ColorData::toColor() {
    return this->color;
}

bool ColorData::isNumber() {
    return false;
}

bool ColorData::isColor() {
    return true;
}
