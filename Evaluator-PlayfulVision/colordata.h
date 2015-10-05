#ifndef COLORDATA_H
#define COLORDATA_H

#include <vector>
#include "template.h"
#include "data.h"

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
        static std::vector<Template*> getTemplates();
        static team_t colorToTeam(Color c);

    private:
        static std::vector<Template*> s_templates;
      Color color;
      bool isTemplate;
      QImage* image;
};

#endif // COLORDATA_H
