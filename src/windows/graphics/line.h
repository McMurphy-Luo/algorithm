#ifndef ALGORITHM_WINDOWS_LINE_H
#define ALGORITHM_WINDOWS_LINE_H

#include "./graphics_base.h"
#include "./color.h"

namespace algorithm
{
    namespace windows
    {
        class Line : public GraphicsBase
        {
        public:
            Line(double right, double bottom, Color color, double width, double left, double top):
                GraphicsBase(Graphics::line, left, top),
                right_(right),
                bottom_(bottom),
                color_(color),
                width_(width)
            {
                /* do nothing */
            }

            Line(double right, double bottom, double left, double top) :
                GraphicsBase(Graphics::line, left, top),
                right_(right),
                bottom_(bottom),
                color_(0, 0, 0), // black
                width_(1)
            {
                /* do nothing */
            }

            bool containsPoint(double x, double y) override;

        private:
            double right_;
            double bottom_;
            Color color_;
            double width_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_LINE_H