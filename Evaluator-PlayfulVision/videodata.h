#ifndef VIDEODATA_H
#define VIDEODATA_H

#include <QMap>
#include "framedata.h"
#include "comparisonresult.h"

#include "constants.h"

class VideoData {

    public:
        VideoData();
        VideoData(QString fileName);

        void addFrameData(Time t, FrameData * data);
        FrameData* getFrameData(Time t);

        QString toString();
        ComparisonResult compareTo(VideoData other, unsigned int marginOfError);

    private:
        QMap<Time, FrameData*> dataMap;
};

#endif // VIDEODATA_H
