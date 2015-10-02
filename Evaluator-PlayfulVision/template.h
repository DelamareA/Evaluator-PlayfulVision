/* Class defining a template.
	A template for a team (player team or referee) is a set of images.
	A template is defined by 7 images, ie the 7 camera image for the same player 
		(we ignore the above camera, as it is useless for finding the team membership)
*/

#ifndef TEMPLATE_INCLUDED
#define TEMPLATE_INCLUDED

#include <QWidget> 
#include <QImage>
#include <vector>

typedef enum{CAMERA_0, CAMERA_1, CAMERA_2, CAMERA_3, CAMERA_4, CAMERA_5, CAMERA_6} orientation_t;

class Template{
	public:
		Template(std::vector<QImage> images);
		~Template();

		QImage get_image(orientation_t o);

	private:	
		std::vector<QImage> m_images;
};
#endif
