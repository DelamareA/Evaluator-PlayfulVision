#include "framedata.h"

FrameData::FrameData() {

}

FrameData::FrameData(FrameData* other) {
    // faire copie très profonde
}


QSetIterator<Data *> FrameData::iterator(){
    return QSetIterator<Data *>(dataSet);
}

void FrameData::addData(Data * d){
    dataSet.insert(d);
}

void FrameData::deleteData(Data * d){
    delete d;
    dataSet.remove(d);
}
