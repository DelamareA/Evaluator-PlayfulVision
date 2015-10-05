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
#include <QDebug>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "template.h"
#include "colordata.h"
#include "numberdata.h"

typedef enum{IDX_TEAM_A = 0, IDX_TEAM_B = 1, IDX_REFEREE = 2} template_index_t;

class TeamTestCase{
	public:
        TeamTestCase(QImage* player_image, team_t expected_result, std::vector<Template*> templates);
        ~TeamTestCase();

		QImage* get_player_image();
		team_t get_expected_result();
        std::vector<Template*> get_templates();
		int get_id();

        static std::string save_test_case(TeamTestCase* tc);
        static TeamTestCase* decode_from_string(std::string str);
        static void save_testcases_to_file(std::vector<TeamTestCase*> test_cases, std::string file_name);
        static TeamTestCase* build_test_case_from_color_data(ColorData* cd);

        static std::string int_to_string(int n);
    private:
        int m_instance_id;
		QImage* m_player_image;
        team_t m_expected_result;
		std::vector<Template*> m_templates;
};


class NumTestCase{
public:
    NumTestCase(QImage* number, int expected);
    ~NumTestCase();
    QImage* get_number_image() {return m_number_image;}
    int get_expected_result() {return m_expected_result;}
    int get_id() {return m_instance_id;}

    static std::string save_test_case(NumTestCase* tc);
    static NumTestCase* decode_from_string(std::string str);
    static void save_testcases_to_file(std::vector<NumTestCase*> test_cases, std::string file_name);
    static NumTestCase* build_test_case_from_number_data(NumberData* cd);

    static int string_to_int(std::string s);

private:
    int m_instance_id;
    QImage* m_number_image;
    int m_expected_result;
};


#endif
