#ifndef DATA_H
#define DATA_H

#include "color.h"
#include "math.h"
#include <QWidget>


class Data {

    public:
        Data();
        Data(unsigned int x, unsigned int y);
        Data(const Data &other);
        virtual ~Data();

        virtual unsigned int toNumber() = 0;
        virtual Color toColor() = 0;
        virtual bool isNumber() = 0;
        virtual bool isColor() = 0;

        unsigned int getX();
        unsigned int getY();
        void setX(unsigned int x);
        void setY(unsigned int y);
        unsigned int distance(Data const& other);


        //virtual bool operator ==(Data const& other) = 0;

    protected:
        unsigned int x;
        unsigned int y;
};

#endif // DATA_H
