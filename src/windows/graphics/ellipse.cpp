#include "Ellipse.h"
#include <iterator>


namespace draw
{
    Ellipse::Ellipse(
        double radius_x,
        double radius_y,
        const Color& background_color,
        const Color& border_color,
        int32_t border_width
    ):
    radius_x_(radius_x),
    radius_y_(radius_y),
    background_color_(background_color),
    border_color_(border_color),
    border_width_(border_width)
    {

    }
}