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
            Text(std::string content, double x, double y):
                GraphicsBase(Graphics::text, x, y),
                content_(content),
                font_color_(Color(0, 0, 0))
            {

            }

            Text(const Text& another) = default;

            Text& operator=(const Text& another) = default;

            ~Text() = default;

            void setContent(const std::string &content) { content_ = content; }

            std::string getContent() { return content_; }

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