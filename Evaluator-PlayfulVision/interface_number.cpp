#include "interface_number.h"

int InterfaceNumber::send_test_case(NumTestCase* tc){
    if (tc == NULL){
        qDebug() << "Error at interface number, null pointer";
        return -1;
    }
    else{
        return -1; // TODO give the test case to the algorithm
    }
}
