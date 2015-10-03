/* TestCase is a class containing all the informations for a test
* 	It has the following :
		-> Image of the rectangle (player) taken by the user using the Evaluator.
		-> The expected result, ie the team of the player. Defined by the user.
		-> Images of the templates used to find the team membership, and defined by the user using the Evaluator.
			-> There are 3 templates, the 2 teams and the referee.
*/
#ifndef TESTCASE_H_INCLUDED
#define TESTCASE_H_INCLUDED

#include <QWidget>
#include <QImage>
#include <vector> 
#include <string>
#include <sstream>
#include <fstream>

#include "../template.h"

typedef enum{IDX_TEAM_A = 0, IDX_TEAM_B = 1, IDX_REFEREE = 2} template_index_t;

class TestCase{
	public:
		TestCase(QImage player_image, team_t expected_result, std::vector<Template> templates);
		~TestCase();

		QImage* get_player_image();
		team_t get_expected_result();
		std::vector<Template> get_templates();

		static std::string save_test_case(TestCase tc);
		static TestCase decode_from_string(std::string str);
		static void save_testcases_to_file(std::vector<TestCase> test_cases, std::string file_name);

	private:
		std::string int_to_string(int n);
		static int ms_instance_number = 0;
		QImage m_player_image;
		Team m_expected_result; 
		std::vector<Template> m_templates;
};
#endif
