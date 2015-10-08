#ifndef NUMBERDATA_H
#define NUMBERDATA_H

#include "data.h"

// This class is a subclass of data which represents a number
class NumberData : public Data {

    public:
        NumberData();
        NumberData(QImage* img, int val);
        NumberData(int val);
        ~NumberData();

        void setImage(QImage*);
        QImage* getImage();

        unsigned int toNumber();
        Color toColor();
        bool isNumber();
        bool isColor();

    private:
        unsigned int val;
};

#endif // NUMBERDATA_H
