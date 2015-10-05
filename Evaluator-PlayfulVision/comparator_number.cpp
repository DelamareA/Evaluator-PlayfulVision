#include "comparator_number.h"

ComparatorNumber::ComparatorNumber(std::string test_case_file){
    std::ifstream file(test_case_file.c_str(), std::ios::in);
    std::string line;
    while (getline(file, line)){
        m_test_cases.push_back(NumTestCase::decode_from_string(line));
    }
    file.close();

    m_results.success = 0;
    m_results.fails = 0;
    m_results.undermined = 0;
    m_results.num_test = m_test_cases.size();
}

ComparatorNumber::~ComparatorNumber() {}

void ComparatorNumber::run_test_cases(){
    std::string terminal_message;
    MainWindow::add_message_to_terminal("Number recognition tests running ...");
    for (int i = 0; i < m_test_cases.size(); i ++){
        if (m_test_cases[i] == NULL){
            qDebug() << "Error at ComparatorNumber::run_test_case, null pointer in test cases";
        }
        terminal_message = "Test " + TeamTestCase::int_to_string(i) + " : ";
        int algo_result = InterfaceNumber::send_test_case(m_test_cases[i]);
        if (algo_result == m_test_cases[i]->get_expected_result()){
            m_results.success ++;
            terminal_message += "SUCCESS.";
        }
        else{
            m_results.fails ++;
            terminal_message += "FAILED";
        }
    }
}

comparison_results_t ComparatorNumber::retreive_test_results(){
    return m_results;
}
