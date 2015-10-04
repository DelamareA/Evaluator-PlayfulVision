#include "test_case.h"

TestCase::TestCase(QImage* player_image, team_t expected_result, std::vector<Template*> templates){
	m_player_image = player_image;
	m_expected_result = expected_result;
	m_templates = templates;
	ms_instance_number ++;
	m_instance_id = ms_instance_number;
}

TestCase::~TestCase(){}

QImage* TestCase::get_player_image() {return m_player_image;}
team_t TestCase::get_expected_result() {return m_expected_result;}
std::vector<Template*> TestCase::get_templates() {return m_templates;}
int TestCase::get_id() {return m_instance_id;}


/* Test case encoding :
	file name player image % expected result (0 : team A, 1 : team B, 2 : team Referee) % file_name templateA % file_name templateB % file_name templateReferee #
*/
std::string TestCase::save_test_case(TestCase* tc){
	std::string file_name_player_image = "player_test_case_" + int_to_string(tc->get_id()) + ".jpg";
	bool player_save = tc->get_player_image()->save(file_name_player_image);
	if (!player_save){
		qDebug() << "Couldn't save the player image for test case" << endl;
	}

	std::string expected;
	switch (tc->get_expected_result()){
		case TEAM_A : 		expected = int_to_string(0); break;
		case TEAM_B : 		expected = int_to_string(1); break;
		case TEAM_REFEREE : expected = int_to_string(2); break;
	}

	std::string file_name_template_A = "template_A_test_case_" + int_to_string(tc->get_id()) + ".jpg";
	std::string file_name_template_B = "template_B_test_case_" + int_to_string(tc->get_id()) + ".jpg";
	std::string file_name_template_REFEREE = "template_REFEREE_test_case_" + int_to_string(tc->get_id()) + ".jpg";

	bool template_A_save = (tc->get_templates())[IDX_TEAM_A]->save(file_name_template_A);
	bool template_B_save = (tc->get_templates())[IDX_TEAM_B]->save(file_name_template_B);
	bool template_REFEREE_save = (tc->get_templates())[IDX_TEAM_REFEREE]->save(file_name_template_REFEREE);

	if (!template_A_save)				qDebug() << "Couldn't save template A for test case" << endl;
	else if (!template_B_save)			qDebug() << "Couldn't save template B for test case" << endl;
	else if (!template_REFEREE_save)	qDebug() << "Couldn't save template REFEREE for test case" << endl;

	return file_name_player_image + "%" + expected + "%" + file_name_template_A + "%" + file_name_template_B + "%" + file_name_template_REFEREE + "#";

}

TestCase* TestCase::decode_from_string(std::string str){
	char* encoded_test_case = str.c_str();
	std::string player_file_name;			// idx =0
	std::string expected;					// idx =1
	std::string file_name_template_A;		// idx =2
	std::string file_name_template_B;		// idx =3
	std::string file_name_template_REFEREE;	// idx =4

	int idx = 0;
	while (*encoded_test_case != '#'){
		if (*encoded_test_case != '%'){
			switch (idx){
				case 0: player_file_name += *encoded_test_case; 			break;
				case 1: expected += *encoded_test_case; 					break;
				case 2: file_name_template_A += *encoded_test_case;			break;
				case 2: file_name_template_B += *encoded_test_case; 		break;
				case 2: file_name_template_REFEREE += *encoded_test_case; 	break;
			}
		}
		else{
			idx ++;
		}
		encoded_test_case ++;
	}

	QImage* player_image;
	QImage template_A_image;
	QImage template_B_image;
	QImage template_REFEREE_image;
	bool player_image_loaded = player_image->load(player_file_name);
	bool template_A_loaded = template_A_image.load(file_name_template_A);
	bool template_B_loaded = template_B_image.load(file_name_template_B);
	bool template_REFEREE_loaded = template_REFEREE_image.load(file_name_template_REFEREE);

	team_t expct;
	if (expected == "0") expct = TEAM_A;
	else if (expected == "1") expct = TEAM_B;
	else if (expected == "2") expct = TEAM_REFEREE;

	Template* t_A = new Template(template_A_image, TEAM_A);
	Template* t_B = new Template(template_B_image, TEAM_B);
	Template* t_REFEREE = new Template(template_REFEREE_image, TEAM_REFEREE);
	std::vector<Template*> templates;
	templates.push_back(t_A);
	templates.push_back(t_B);
	templates.push_back(t_REFEREE);

	return new TestCase(player_image, expct, templates);
}

void TestCase::save_testcases_to_file(std::vector<TestCase*> test_cases, std::string file_name){
	ofstream file(file_name.c_str(), ios::out);
	for (int i = 0; i < test_cases.size(); i ++){
		file << save_test_case(test_cases[i]) << endl;
	}
	file.close();
}

TestCase* TestCase::build_test_case_from_color_data(ColorData* cd){
	QImage* img = cd->getImage();
	team_t expct;
	switch(cd->toColor()){
		case TEAM_1:	expct = TEAM_A;			break;
		case TEAM_2:	expct = TEAM_B;			break;
		case REFEREE:	expct = TEAM_REFEREE;	break;
	}
	return new TestCase(img, expct, cd->getTemplates());
}

std::string TestCase::int_to_string(int n){
	std::ostringstream oss;
	oss << i;
	return oss.str();
}
