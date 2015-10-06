/* 
		LEFT EMPTY UNTIL WE KNOW HOW TO GIVE
        TEST CASES TO OUR ALGO.
*/

#include "interface_team.h"

team_t InterfaceTeam::send_test_case(TeamTestCase* tc){
    if (tc == NULL){
        qDebug() << "Error at interface team";
        return TEAM_UNKNOWN;
    }
    else{
        return tc->get_expected_result();
    }
}
