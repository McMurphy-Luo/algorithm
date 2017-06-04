#include "tree_render.h"

namespace algorithm
{
    namespace windows
    {
        namespace detail
        {
            void render_node(ID2D1RenderTarget* render_target, ID2D1SolidColorBrush* brush, double x, double y)
            {
                D2D1_ELLIPSE ellipse;
                ellipse.point.x = static_cast<float>(x);
                ellipse.point.y = static_cast<float>(y);
                ellipse.radiusX = 50;
                ellipse.radiusY = 50;
                render_target->FillEllipse(ellipse, brush);
            }

            void render_line(ID2D1SolidColorBrush* brush, double x1, double y1, double x2, double y2)
            {

            }
        }
    }
}