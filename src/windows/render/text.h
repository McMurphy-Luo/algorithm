#ifndef ALGORITHM_WINDOWS_TEXT_H
#define ALGORITHM_WINDOWS_TEXT_H

#include <string>
#include <memory>
#include "./graphics_base.h"
#include "./color.h"

namespace algorithm
{
    namespace windows
    {
        class Text : public GraphicsBase
        {
        public:
            Text(std::string content, double x, double y, std::shared_ptr<GraphicsBase> parent) :
                GraphicsBase(x, y, parent),
                content_(content),
                font_color_(Color(0, 0, 0))
            {

            }

            void setColor(Color value){ font_color_ = value; }

            Color getColor() { return font_color_; }

            bool containsPoint(double x, double y) { return false; }

        private:
            Color font_color_;
            std::string content_;
        };
    }
}


#endif //ALGORITHM_WINDOWS_TEXT_H