#ifndef ALGORITHM_WINDOWS_COLOR_H
#define ALGORITHM_WINDOWS_COLOR_H

#include <cassert>

namespace algorithm
{
    namespace windows
    {
        class Color
        {
        public:
            Color(int red, int green, int blue, int alpha):
                red_(red),
                green_(green),
                blue_(blue),
                alpha_(alpha)
            {
                /* do nothing */
            }

            Color(int red, int green, int blue):
                red_(red),
                green_(green),
                blue_(blue),
                alpha_(100)
            {
                /* do nothing */
            }

            Color(const Color& another) = default;

            Color& operator=(const Color& another) = default;

            ~Color() = default;

            int getRed() const { return red_; }

            int getGreen() const { return green_; }

            int getBlue() const { return blue_; }

            int getAlpha() const { return alpha_; }

            void setRed(int value) { assert(value >= 0 && value <= 255); red_ = value; }

            void setGreen(int value) { assert(value >= 0 && value <= 255); green_ = value; }

            void setBlue(int value) { assert(value >= 0 && value <= 255); blue_ = value; }

            void setAlpha(int value) { assert(value >= 0 && value <= 100); alpha_ = value; }

        private:
            int red_;
            int green_;
            int blue_;
            int alpha_;
        };
    }
}

#endif // ALGORITHM_WINDOWS_COLOR_H