#ifndef COLORDATA_H
#define COLORDATA_H

#include "data.h"

class ColorData : public Data {

    public:
        ColorData();
        ColorData(Color c);
        ~ColorData();

        unsigned int toNumber();
        Color toColor();
        bool isNumber();
        bool isColor();

    private:
      Color color;
};

#endif // COLORDATA_H
