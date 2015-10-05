#include "numberdata.h"

NumberData::NumberData(){
    this->val = 1;
}

NumberData(QImage* img, int val){
    m_img = img;
    this->val = val;
}

NumberData::NumberData(int val){
    this->val = val;
}

NumberData::~NumberData(){

}

QImage* set_image(QImage* img){
    m_img = img;
}

QImage* get_image(){
    return m_img;
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
