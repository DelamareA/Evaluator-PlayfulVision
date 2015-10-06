#include "test_case.h"

TeamTestCase::TeamTestCase(QImage* player_image, team_t expected_result, std::vector<Template*> templates){
    if (player_image == NULL){
        qDebug() << "Error in TeamTestCase::TeamTestCase, given image is null";
    }
    else if (templates.size() != 3){
        qDebug() << "Error in TeamTestCase::TeamTestCase, invalid number of templates.";
    }
    else if (templates[0] == NULL || templates[1] == NULL || templates[2] == NULL){
        qDebug() << "Error in TeamTestCase::TeamTestCase, null pointer in templates.";
    }
    else{
        m_player_image = player_image;
        m_expected_result = expected_result;
        m_templates = templates;
        static int ms_instance_number = 0;
        ms_instance_number ++;
        m_instance_id = ms_instance_number;
    }
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
    if (tc == NULL){
        qDebug() << "Error at TeamTestCase::save_test_case, given test case is NULL";
    }

    std::string file_name_player_image = "player_test_case_" + int_to_string(tc->get_id()) + ".jpg";
    QImage* player_image = tc->get_player_image();
    if (player_image == NULL){
        qDebug() << "Error at TeamTestCase::save_test_case, null pointer on player image, testcase with id " << tc->get_id();
    }
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

    std::vector<Template*> templates = tc->get_templates();
    if (templates.size() != 3){
        qDebug() << "Error in TeamTestCase::save_test_case, " << templates.size() << " instead of 3.";
    }
    if (templates[0] == NULL || templates[1] == NULL || templates[2] == NULL){
        qDebug() << "Error in TeamTestCase::save_test_case, null pointer in templates for test case with id " << tc->get_id();
    }

    bool template_A_save = templates[IDX_TEAM_A]->get_template().save(QString::fromUtf8(file_name_template_A.c_str()));
    bool template_B_save = templates[IDX_TEAM_B]->get_template().save(QString::fromUtf8(file_name_template_B.c_str()));
    bool template_REFEREE_save = templates[IDX_REFEREE]->get_template().save(QString::fromUtf8(file_name_template_REFEREE.c_str()));

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
        qDebug() << *encoded_test_case << "     " << idx;
		if (*encoded_test_case != '%'){
			switch (idx){
				case 0: player_file_name += *encoded_test_case; 			break;
                case 1: expected = *encoded_test_case;                      break;
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
    qDebug() << player_file_name.c_str() << "|   |" << expected.c_str() << "|  " << file_name_template_A.c_str() << "  " << file_name_template_B.c_str() << "  " << file_name_template_REFEREE.c_str();

    QImage* player_image = new QImage();
	QImage template_A_image;
	QImage template_B_image;
	QImage template_REFEREE_image;
    bool player_image_loaded = player_image->load(QString::fromUtf8(player_file_name.c_str()));
    bool template_A_loaded = template_A_image.load(QString::fromUtf8(file_name_template_A.c_str()));
    bool template_B_loaded = template_B_image.load(QString::fromUtf8(file_name_template_B.c_str()));
    bool template_REFEREE_loaded = template_REFEREE_image.load(QString::fromUtf8(file_name_template_REFEREE.c_str()));

    if (!player_image_loaded){
        qDebug() << "Error in TeamTestCase::decode_from_string, couldn't load player image";
    }
    else if (!template_A_loaded || !template_B_loaded || !template_REFEREE_loaded){
        qDebug() << "Error in TeamTestCase::decode_from_string, couldn't load template";
    }
    int expected_int = NumTestCase::string_to_int(expected);
    qDebug() << "Images loaded";

	team_t expct;
    if (expected_int == 0) expct = TEAM_A;
    else if (expected_int == 1) expct = TEAM_B;
    else if (expected_int == 2) expct = TEAM_REFEREE;
    else qDebug() << "Error in TeamTestCase::decode_from_string, invalid expected team : " << QString::fromUtf8(expected.c_str());

    qDebug() << "Expected value retrieved";

	Template* t_A = new Template(template_A_image, TEAM_A);
	Template* t_B = new Template(template_B_image, TEAM_B);
	Template* t_REFEREE = new Template(template_REFEREE_image, TEAM_REFEREE);
    if (t_A == NULL || t_B == NULL || t_REFEREE == NULL){
        qDebug() << "Error in TeamTestCase::decode_from_string, couldn't create tenmplate.";
    }
    else qDebug() << "Templates created";

	std::vector<Template*> templates;
	templates.push_back(t_A);
    templates.push_back(t_B);
	templates.push_back(t_REFEREE);

    qDebug() << "Template vector created";

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
    if (cd == NULL){
        qDebug() << "Error in TeamTestCase::build_test_case_from_color_data, given data is null";
    }
	QImage* img = cd->getImage();
    if (img == NULL){
        qDebug() << "Error in TeamTestCase::build_test_case_from_color_data, image of data is NULL";
    }
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
    if (number == NULL){
        qDebug() << "Error in NumTestCase::NumTestCase, given number image is null";
    }
    m_number_image = number;
    m_expected_result = expected;
    static int ms_instance_number = 0;
    ms_instance_number ++;
    m_instance_id = ms_instance_number;
}
/* num_file_name % expected # */
std::string NumTestCase::save_test_case(NumTestCase* tc){
    if (tc == NULL){
        qDebug() << "Error in NumTestCase::save_test_case, given test case is null";
    }
    std::string image_number_filename = "number_test_case_" + TeamTestCase::int_to_string(tc->get_id()) + ".jpg";
    QImage* number_image = tc->get_number_image();
    if (number_image == NULL){
        qDebug() << "Error in NumTestCase::save_test_case, number_image for the given test case is null";
    }
    number_image->save(QString::fromUtf8(image_number_filename.c_str()));
    std::string expected = TeamTestCase::int_to_string(tc->get_expected_result());
    return image_number_filename + "%" + expected + "#";
}

NumTestCase* NumTestCase::decode_from_string(std::string str){
    int percent_index = str.find_first_of('%');
    int end_index = str.find_first_of('#');
    std::string filename = "";
    std::string expct = "";

    const char* c = str.c_str();
    int idx = 0;
    while (*c != '#'){
        if (*c != '%'){
            switch (idx){
                case 0: filename += *c; break;
                case 1: expct += *c; break;
            }
        }
        else{
            idx ++;
        }
        c = c + 1;
    }
    QImage* img = new QImage();
    img->load(QString::fromUtf8(filename.c_str()));
    if (img == NULL){
        qDebug() << "Error in NumTestCase::decode_from_string, can't load image " << QString::fromUtf8(filename.c_str());
    }
    else{
        qDebug() << "NumTestCase parsed filename=" << filename.c_str() << " expected=" << expct.c_str();
    }
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
