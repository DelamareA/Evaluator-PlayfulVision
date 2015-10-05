#include "test_case.h"
#include "interface_number.h"
#include "mainwindow.h"
#include <fstream>

typedef struct{
    int success;
    int fails;
    int undermined;
    int num_test;
}comparison_results_t;

class ComparatorNumber{
public:
    ComparatorNumber(std::string test_case_file);
    ~ComparatorNumber();

    void run_test_cases();

    comparison_results_t retreive_test_results();

private:
    std::vector<NumTestCase*> m_test_cases;
    comparison_results_t m_results;
};
