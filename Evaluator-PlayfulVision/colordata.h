#ifndef COLORDATA_H
#define COLORDATA_H

#include <vector>
<<<<<<< HEAD
#include "template.h"
=======
//#include "templates.h"
>>>>>>> 4b8b4ed5e72c494ad1cde9fbc80b7977c769a0cb
#include "data.h"

/*
 * This class is used to represent a data used for colors
 *
*/
class ColorData : public Data {

    public:
        ColorData();
        ColorData(Color c);
        ColorData(Color c, bool isTemplate);
        ~ColorData();

        unsigned int toNumber();
        Color toColor();
        bool isNumber();
        bool isColor();

        void setTemplated(bool);
        void setImage(QImage*);
        bool getTemplate();
        QImage* getImage();

        static Color intToColor(int);
        static int colorToInt(Color c);
<<<<<<< HEAD
        static std::vector<Template*> getTemplates();
        static team_t colorToTeam(Color c);
=======
        //static std::vector<Template*> getTemplates();
>>>>>>> 4b8b4ed5e72c494ad1cde9fbc80b7977c769a0cb

    private:
        //static std::vector<Template*> s_templates;
      Color color;
      bool isTemplate;
      QImage* image;
};

#endif // COLORDATA_H
