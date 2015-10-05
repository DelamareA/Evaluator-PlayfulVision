#include "colordata.h"

std::vector<Template*> ColorData::s_templates;

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
<<<<<<< HEAD
        ColorData::s_templates[color] = new Template(*i, colorToTeam(color));
=======
        //s_templates[color] = new Template(i, color);
>>>>>>> 4b8b4ed5e72c494ad1cde9fbc80b7977c769a0cb
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

<<<<<<< HEAD
team_t ColorData::colorToTeam(Color c){
    switch (c){
        case TEAM_1 : return TEAM_A; break;
        case TEAM_2 : return TEAM_B; break;
        case REFEREE : return TEAM_REFEREE; break;
    }
}

std::vector<Template*> ColorData::getTemplates(){
=======
/*std::vector<Template*> ColorData::getTemplates(){
>>>>>>> 4b8b4ed5e72c494ad1cde9fbc80b7977c769a0cb
    return s_templates;
}*/
