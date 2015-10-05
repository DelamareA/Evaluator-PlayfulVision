#include "comparator_team.h"

ComparatorTeam::ComparatorTeam(std::string test_case_file){
    std::ifstream file(test_case_file.c_str(), std::ios::in);
	std::string line;
	while (getline(file, line)){
        m_test_cases.push_back(TeamTestCase::decode_from_string(line));
	}
	file.close();

	m_results.success = 0;
	m_results.fails = 0;
	m_results.undermined = 0;
	m_results.num_test = m_test_cases.size();
}

ComparatorTeam::~ComparatorTeam() {}

void ComparatorTeam::run_test_cases(){
	for (int i = 0; i < m_test_cases.size(); i ++){
		team_t algo_result = InterfaceTeam::send_test_case(m_test_cases[i]);
        if (algo_result == m_test_cases[i]->get_expected_result()){
			m_results.success ++;
		}
		else if (algo_result == TEAM_UNKNOWN){
			m_results.undermined ++;
		}
		else{
			m_results.fails ++;
		}
	}
}

comparison_results_t ComparatorTeam::retreive_test_results(){
	return m_results;
}
