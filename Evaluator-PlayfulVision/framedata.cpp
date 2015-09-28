#include "framedata.h"

FrameData::FrameData() {

}


QSetIterator<Data *> FrameData::iterator(){
    return QSetIterator<Data *>(dataSet);
}

void FrameData::addData(Data * d){
    dataSet.insert(d);
}
