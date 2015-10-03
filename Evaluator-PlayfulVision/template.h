/* Class defining a template.
*/

#ifndef TEMPLATE_INCLUDED
#define TEMPLATE_INCLUDED

#include <QWidget> 
#include <QImage>
#include <vector>

typedef enum{TEAM_A, TEAM_B, TEAM_REFEREE, TEAM_UNKNOWN} team_t;

class Template{
	public:
		Template(QImage image, team_t team);
		~Template();

		QImage get_template();
		team_t get_template_team();

	private:	
		QImage m_image;
		team_t m_team;
};
#endif
