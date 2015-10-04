#include "colordata.h"

ColorData::ColorData() {
    this->color = TEAM_1;
    this->isTemplate = false;
    this->image = 0;
}

ColorData::ColorData(Color c) {
    this->color = c;
    this->isTemplate = false;
    this->image = 0;
}

ColorData::ColorData(Color c, bool isTemplate) {
    this->color = c;
    this->isTemplate = isTemplate;
    this->image = 0;
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

void ColorData::setTemplated(bool b){
    this->isTemplate = b;
}

void ColorData::setImage(QImage* i){
    this->image = i;
    if (isTemplate){
        s_templates[color] = new Template(i, color);
    }
}

bool ColorData::getTemplate(){
    return this->isTemplate;
}

QImage* ColorData::getImage(){
    return this->image;
}

Color ColorData::intToColor(int i){
    Color c;
    switch (i){
        case 0:
        c = TEAM_1;
        break;
        case 1:
        c = TEAM_2;
        break;
        default:
        c = REFEREE;
        break;
    }
    return c;
}

int ColorData::colorToInt(Color c){
    int i;
    switch (c){
        case TEAM_1:
        i = 0;
        break;
        case TEAM_2:
        i = 1;
        break;
        default:
        i = 2;
        break;
    }
    return i;
}

std::vector<Template*> ColorData::getTemplates(){
    return s_templates;
}
