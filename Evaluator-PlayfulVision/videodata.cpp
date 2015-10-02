#include "videodata.h"

VideoData::VideoData(){

}

VideoData::VideoData(QString fileName){

}

void VideoData::addFrameData(Time t, FrameData *data){
    dataMap.insert(t, data);
}

FrameData * VideoData::getFrameData(Time t){
    return dataMap[t];
}

QString VideoData::toString() {

}


ComparisonResult VideoData::compareTo(VideoData other, unsigned int marginOfError) {
    return ComparisonResult();
}
