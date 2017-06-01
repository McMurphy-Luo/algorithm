#ifndef ALGORITHM_WINDOWS_ELLIPSE_H
#define ALGORITHM_WINDOWS_ELLIPSE_H

#include <cstdint>
#include "color.h"
#include "transformation.h"

namespace algorithm
{
    namespace windows
    {
        class Ellipse : public Transformation
        {
        public:
            Ellipse(double radius_x, double radius_y, const Color& background_color, const Color& border_color, int32_t border_width)
                :radius_x_(radius_x), radius_y_(radius_y), background_color_(background_color), border_color_(border_color), border_width_(border_width)
            {};
            double getRadiusX() const { return radius_x_; }
            double getRadiusY() const { return radius_y_; }
            int32_t getBorderWidth() const { return border_width_; }
            Color getBackgroundColor() const { return background_color_; }
            Color getBorderColor() const { return border_color_; }

            void setRadiusX(double radius_x) { radius_x_ = radius_x; }
            void setRadiusY(double radius_y) { radius_y_ = radius_y; }
            void setBorderWidth(int32_t border_width) { border_width_ = border_width; }
            void setBackgroundColor(const Color& color) { background_color_ = color; }
            void setBorderColor(const Color& color) { border_color_ = color; }

        private:
            Color background_color_;
            Color border_color_;
            int32_t border_width_;
            double radius_x_;
            double radius_y_;
        };
    }
    
}

#endif //ALGORITHM_WINDOWS_ELLIPSE_H