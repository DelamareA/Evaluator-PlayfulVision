#ifndef COLORDATA_H
#define COLORDATA_H

#include "data.h"

class ColorData : public Data {

    public:
        ColorData();
        ColorData(Color c);
        ColorData(Color c, bool isTemplate);
        ~ColorData();

        unsigned int toNumber();
        Color toColor();
        bool isNumber();
        bool isColor();

        void setTemplated(bool);
        void setImage(QImage*);
        bool getTemplate();
        QImage* getImage();

        static Color intToColor(int);
        static int colorToInt(Color c);

    private:
      Color color;
      bool isTemplate;
      QImage* image;
};

#endif // COLORDATA_H
