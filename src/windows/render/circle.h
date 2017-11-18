#ifndef ALGORITHM_WINDOWS_TREE_NODE_H
#define ALGORITHM_WINDOWS_TREE_NODE_H

#include "./graphics_base.h"
#include "./color.h"

namespace algorithm
{
    namespace windows
    {
        class Circle : public GraphicsBase
        {
        public:
            Circle(double radius, Color background_color, Color border_color, double top, double left, std::shared_ptr<GraphicsBase> parent):
                GraphicsBase(top, left, parent),
                background_color_(background_color),
                border_color_(border_color),
                radius_(radius)
            {
                /* do nothing */
            }

            Circle(double radius, double top, double left, std::shared_ptr<GraphicsBase> parent):
                Circle(radius, Color(0, 0, 0), Color(0, 0, 0), top, left, parent)
            {
                /* do nothing */
            }

            Circle(double radius, std::shared_ptr<GraphicsBase> parent):
                Circle(radius, Color(0, 0, 0), Color(0, 0, 0), 0, 0, parent)
            {
                /* do nothing */
            }

            Circle(double radius):
                Circle(radius, Color(0, 0, 0), Color(0, 0, 0), 0, 0, nullptr)
            {
                /* do nothing */
            }

            Circle(const Circle& another) = default;

            Circle& operator=(const Circle& another) = default;

            virtual ~Circle() = default;

            Color getBorderColor() const { return border_color_; }

            Color getBackgroundColor() const { return background_color_; }

            void setBorderColor(Color border_color) { border_color_ = border_color;  }

            void setBackgroundColor(Color background_color) { background_color = background_color; }

            virtual bool containsPoint(double x, double y) override;

        private:
            Color background_color_;
            Color border_color_;
            double radius_;
        };
    }
}

#endif // ALGORITHM_WINDOWS_TREE_NODE_H