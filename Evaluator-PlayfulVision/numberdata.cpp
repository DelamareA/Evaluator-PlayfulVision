#include "numberdata.h"

NumberData::NumberData(){
    this->val = 1;
}

NumberData::NumberData(QImage* img, int val){
    m_img = img;
    this->val = val;
}

NumberData::NumberData(int val){
    this->val = val;
}

NumberData::~NumberData(){

}

QImage* NumberData::set_image(QImage* img){
    m_img = img;
}

QImage* NumberData::get_image(){
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
