#ifndef ALGORITHM_WINDOWS_COLOR_H
#define ALGORITHM_WINDOWS_COLOR_H

#include <cstdint>
#include <cassert>

namespace algorithm
{
    namespace windows
    {
        class Color
        {
        public:
            Color(int32_t red, int32_t green, int32_t blue, int32_t alpha):
            red_(red),green_(green),blue_(blue),alpha_(alpha)
            {
                assert(red >= 0 && red <= 256);
                assert(green >= 0 && green <= 256);
                assert(blue >= 0 && blue <= 256);
                assert(alpha >= 0 && alpha <= 100);
            };
            int32_t getRed() const { return red_; };
            int32_t getGreen() const { return green_; };
            int32_t getBlue() const { return blue_; };
            int32_t getAlpha() const { return alpha_; };
            inline void setRed(int32_t value) { assert(value >= 0 && value <= 256); red_ = value; };
            inline void setGreen(int32_t value) { assert(value >= 0 && value <= 256); green_ = value; };
            inline void setBlue(int32_t value){ assert(value >= 0 && value <= 256); blue_ = value; };
            inline void setAlpha(int32_t value){ assert(value >= 0 && value <= 100); alpha_ = value; };

        private:
            int32_t red_;
            int32_t green_;
            int32_t blue_;
            int32_t alpha_;
        };
    }
}

#endif //DRAW_COLOR_H