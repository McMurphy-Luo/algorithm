#include "Color.h"
#include <cassert>

namespace draw
{
    Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha):
    red_(red),
    green_(green),
    blue_(blue),
    alpha_(alpha)
    {
        assert(red >= 0 && red <= 256);
        assert(green >= 0 && green <= 256);
        assert(blue >= 0 && blue <= 256);
        assert(alpha >= 0 && alpha <= 100);
    }

    inline void Color::setRed(int32_t value)
    {
        assert(value >= 0 && value <= 256);
        red_ = value;
    };
    

    void Color::setGreen(int32_t value)
    {
        assert(value >= 0 && value <= 256);
        green_ = value;
    }

    void Color::setBlue(int32_t value)
    {
        assert(value >= 0 && value <= 256);
        blue_ = value;
    }

    void Color::setAlpha(int32_t value)
    {
        assert(value >= 0 && value <= 256);
        alpha_ = value;
    }
}