/* 
	This class is responsible of injecting the test cases in our algorithm
	And then returning the result.
	It is called by the Comparator and given a test case.
		The test case is then given to the algorithm.
		The algorithm compute the value (team) for this test case.
		And then the interface returns the value.
	Finally the Comparator can compare the value returned by the algo and
	the expected value.
*/

#include "test_case.h"

class InterfaceTeam{
	public:
		InterfaceTeam();
		~InterfaceTeam();

		static team_t send_test_case(TestCase tc);
};