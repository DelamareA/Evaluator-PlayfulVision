#include "numberdata.h"

NumberData::NumberData(){
    this->val = 1;
}

NumberData::NumberData(QImage* img, int val){
    this->image = img;
    this->val = val;
}

NumberData::NumberData(int val){
    this->val = val;
}

NumberData::~NumberData(){

}

void NumberData::setImage(QImage* i){
    this->image = i;
}

QImage* NumberData::getImage(){
    return this->image;
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
