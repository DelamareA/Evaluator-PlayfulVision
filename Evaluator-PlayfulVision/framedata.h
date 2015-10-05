#ifndef FRAMEDATA_H
#define FRAMEDATA_H

#include <QSet>
#include "data.h"

// This class is just a set, which includes all the data in the current frame
class FrameData{

    public:
        FrameData();
        FrameData(FrameData* other);

        QSetIterator<Data *> iterator();
        void addData(Data * p);
        void deleteData(Data * p);

     private:
        QSet<Data *> dataSet;
};

#endif // FRAMEDATA_H
