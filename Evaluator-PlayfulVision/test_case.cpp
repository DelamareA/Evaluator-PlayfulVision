#include "test_case.h"

TeamTestCase::TeamTestCase(QImage* player_image, team_t expected_result, std::vector<Template*> templates){
	m_player_image = player_image;
	m_expected_result = expected_result;
	m_templates = templates;
    static int ms_instance_number = 0;
    ms_instance_number ++;
	m_instance_id = ms_instance_number;
}

TeamTestCase::~TeamTestCase(){}

QImage* TeamTestCase::get_player_image() {return m_player_image;}
team_t TeamTestCase::get_expected_result() {return m_expected_result;}
std::vector<Template*> TeamTestCase::get_templates() {return m_templates;}
int TeamTestCase::get_id() {return m_instance_id;}


/* Test case encoding :
	file name player image % expected result (0 : team A, 1 : team B, 2 : team Referee) % file_name templateA % file_name templateB % file_name templateReferee #
*/
std::string TeamTestCase::save_test_case(TeamTestCase* tc){
    std::string file_name_player_image = "player_test_case_" + int_to_string(tc->get_id()) + ".jpg";
    bool player_save = tc->get_player_image()->save(QString::fromUtf8(file_name_player_image.c_str()));


	std::string expected;
	switch (tc->get_expected_result()){
		case TEAM_A : 		expected = int_to_string(0); break;
		case TEAM_B : 		expected = int_to_string(1); break;
		case TEAM_REFEREE : expected = int_to_string(2); break;
	}

	std::string file_name_template_A = "template_A_test_case_" + int_to_string(tc->get_id()) + ".jpg";
	std::string file_name_template_B = "template_B_test_case_" + int_to_string(tc->get_id()) + ".jpg";
	std::string file_name_template_REFEREE = "template_REFEREE_test_case_" + int_to_string(tc->get_id()) + ".jpg";

    bool template_A_save = ((tc->get_templates())[IDX_TEAM_A])->get_template().save(QString::fromUtf8(file_name_template_A.c_str()));
    bool template_B_save = ((tc->get_templates())[IDX_TEAM_B])->get_template().save(QString::fromUtf8(file_name_template_B.c_str()));
    bool template_REFEREE_save = ((tc->get_templates())[IDX_REFEREE])->get_template().save(QString::fromUtf8(file_name_template_REFEREE.c_str()));

	return file_name_player_image + "%" + expected + "%" + file_name_template_A + "%" + file_name_template_B + "%" + file_name_template_REFEREE + "#";

}

TeamTestCase* TeamTestCase::decode_from_string(std::string str){
    const char* encoded_test_case = str.c_str();
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
                case 3: file_name_template_B += *encoded_test_case; 		break;
                case 4: file_name_template_REFEREE += *encoded_test_case; 	break;
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
    bool player_image_loaded = player_image->load(QString::fromUtf8(player_file_name.c_str()));
    bool template_A_loaded = template_A_image.load(QString::fromUtf8(file_name_template_A.c_str()));
    bool template_B_loaded = template_B_image.load(QString::fromUtf8(file_name_template_B.c_str()));
    bool template_REFEREE_loaded = template_REFEREE_image.load(QString::fromUtf8(file_name_template_REFEREE.c_str()));

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

    return new TeamTestCase(player_image, expct, templates);
}

void TeamTestCase::save_testcases_to_file(std::vector<TeamTestCase*> test_cases, std::string file_name){
    std::ofstream file(file_name.c_str(), std::ios::out);
	for (int i = 0; i < test_cases.size(); i ++){
        file << TeamTestCase::save_test_case(test_cases[i]) << std::endl;
	}
	file.close();
}

TeamTestCase* TeamTestCase::build_test_case_from_color_data(ColorData* cd){
	QImage* img = cd->getImage();
	team_t expct;
	switch(cd->toColor()){
		case TEAM_1:	expct = TEAM_A;			break;
		case TEAM_2:	expct = TEAM_B;			break;
		case REFEREE:	expct = TEAM_REFEREE;	break;
	}
    return new TeamTestCase(img, expct, cd->getTemplates());
}

std::string TeamTestCase::int_to_string(int n){
	std::ostringstream oss;
    oss << n;
	return oss.str();
}

/* ****************************** */
NumTestCase::NumTestCase(QImage* number, int expected){
    m_number_image = number;
    m_expected_result = expected;
    static int ms_instance_number = 0;
    ms_instance_number ++;
    m_instance_id = ms_instance_number;
}
/* num_file_name % expected # */
std::string NumTestCase::save_test_case(NumTestCase* tc){
    std::string image_number_filename = "number_test_case_" + TeamTestCase::int_to_string(tc->get_id()) + ".jpg";
    tc->get_number_image()->save(QString::fromUtf8(image_number_filename.c_str()));
    std::string expected = TeamTestCase::int_to_string(tc->get_expected_result());
    return image_number_filename + "%" + expected + "#";
}

NumTestCase* NumTestCase::decode_from_string(std::string str){
    int percent_index = str.find_first_of('%');
    std::string filename = str.substr(0, percent_index);
    std::string expct = str.substr(percent_index+1);
    QImage* img = new QImage();
    img->load(QString::fromUtf8(filename.c_str()));
    return new NumTestCase(img, string_to_int(expct));
}

void NumTestCase::save_testcases_to_file(std::vector<NumTestCase*> test_cases, std::string file_name){
    std::ofstream file(file_name.c_str(), std::ios::out);
    for (int i = 0; i < test_cases.size(); i ++){
        file << NumTestCase::save_test_case(test_cases[i]) << std::endl;
    }
    file.close();
}

NumTestCase* NumTestCase::build_test_case_from_number_data(NumberData* cd){
    return new NumTestCase(cd->get_image(), cd->toNumber());
}

int NumTestCase::string_to_int(std::string s){
    return atoi(s.c_str());
}
