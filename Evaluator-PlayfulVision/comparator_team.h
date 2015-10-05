/*
	This class is the key of the evaluator.
	It is this class that compute the number of fails and success on the test cases.
	Basically there is 4 steps :
		1 ) Get the test cases, given in a text file format generated by the evaluator.
		2 ) For each test case, send it to the interface, in order to make the algorithm
				compute the result for this test.
		3 ) Wait for the result and compare it with the expected value of the test case,
				and set the number of fails/success accordingly.
		4 ) While there are test cases left, go to step 1.
*/

#include "test_case.h"
#include "interface_team.h"
#include <fstream>

typedef struct{
	int success;
	int fails;
	int undermined;
	int num_test;
}comparison_results_t;

class ComparatorTeam{
public:
	ComparatorTeam(std::string test_case_file);
	~ComparatorTeam();

	void run_test_cases();

	comparison_results_t retreive_test_results();

private:
    std::vector<TeamTestCase*> m_test_cases;
	comparison_results_t m_results;
};