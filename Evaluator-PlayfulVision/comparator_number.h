#ifndef COMAPARATOR_NUMBER_H_INCLUDED
#define COMAPARATOR_NUMBER_H_INCLUDED

#include "test_case.h"
#include "interface_number.h"
#include "mainwindow.h"
#include <fstream>
#include <QDebug>

typedef struct{
    int success;
    int fails;
    int undermined;
    int num_test;
}number_comparison_results_t;

class ComparatorNumber{
public:
    ComparatorNumber(std::string test_case_file);
    ~ComparatorNumber();

    void run_test_cases();

    number_comparison_results_t retreive_test_results();

private:
    std::vector<NumTestCase*> m_test_cases;
    number_comparison_results_t m_results;
};

#endif;
