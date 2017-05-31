#ifndef ALGORITHM_WINDOWS_COLOR_H
#define ALGORITHM_WINDOWS_COLOR_H

#include <cstdint>
#include <cassert>

namespace draw
{
    class Color
    {
    public:
        Color(int32_t red, int32_t green, int32_t blue, int32_t alpha);
        Color(const Color& to) = default;
        Color& Color::operator=(const Color& to) = default;
        ~Color() = default;

        int32_t getRed() const { return red_; };
        int32_t getGreen() const { return green_; };
        int32_t getBlue() const { return blue_; };
        int32_t getAlpha() const { return alpha_; };
        inline void setRed(int32_t value);
        inline void setGreen(int32_t value);
        inline void setBlue(int32_t value);
        inline void setAlpha(int32_t value);

    private:
        int32_t red_;
        int32_t green_;
        int32_t blue_;
        int32_t alpha_;
    };
}

#endif //DRAW_COLOR_H