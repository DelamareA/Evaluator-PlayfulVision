#include "interface_number.h"

int InterfaceNumber::send_test_case(NumTestCase* tc){
    if (tc == NULL){
        qDebug() << "Error at interface number, null pointer";
        return -1;
    }
    else{
        return tc->get_expected_result(); // TODO give the test case to the algorithm
    }
}
