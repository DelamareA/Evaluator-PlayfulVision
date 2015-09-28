#ifndef NUMBERDATA_H
#define NUMBERDATA_H

#include "data.h"

class NumberData : public Data {

    public:
        NumberData();
        ~NumberData();

        unsigned int toNumber();
        Color toColor();
        bool isNumber();
        bool isColor();

    private:
        unsigned int val;
};

#endif // NUMBERDATA_H
