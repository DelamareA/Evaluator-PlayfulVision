#ifndef INTERFACE_NUMBER_H_INCLUDED
#define INTERFACE_NUMBER_H_INCLUDED

#include "test_case.h"
#include <QDebug>

class InterfaceNumber{
    public:
        static int send_test_case(NumTestCase* tc);
};
#endif
