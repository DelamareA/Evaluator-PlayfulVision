#include "data.h"

Data::Data() {
    this->x = 0;
    this->y = 0;
}

Data::Data(unsigned int x, unsigned int y) {
    this->x = x;
    this->y = y;
}

Data::Data(const Data &other) {
    this->x = other.x;
    this->y = other.y;
}

Data::~Data() {

}

unsigned int Data::getX(){
    return x;
}

unsigned int Data::getY(){
    return y;
}

void Data::setX(unsigned int x){
    this->x = x;
}

void Data::setY(unsigned int y){
    this->y = y;
}

unsigned int Data::distance(Data const& other){
    int diffX = x - other.x;
    int diffy = y - other.y;
    return sqrt(diffX * diffX + diffy * diffy);
}


