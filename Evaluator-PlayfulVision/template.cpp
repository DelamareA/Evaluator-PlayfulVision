#include "template.h"

Template::Template(QImage image, team_t team){
	m_image = image;
	m_team = team;
}
	
Template::~Template(){
	// nothing to do
}

QImage Template::get_template() {return m_image;}
team_t get_template_team() {return m_team;}