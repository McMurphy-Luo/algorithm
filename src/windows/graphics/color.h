#ifndef ALGORITHM_WINDOWS_COLOR_H
#define ALGORITHM_WINDOWS_COLOR_H

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
                alpha_(1)
            {
                /* do nothing */
            }

            Color(const Color& another) = default;

            Color& operator=(const Color& another) = default;

            ~Color() = default;

            int getRed() { return red_; }

            int getGreen() { return green_; }

            int getBlue() { return blue_; }

            void setRed(int value) { red_ = value; }

            void setGreen(int value) { green_ = value; }

            void setBlue(int value) { blue_ = value; }

        private:
            int red_;
            int green_;
            int blue_;
            int alpha_;
        };
    }
}

#endif // ALGORITHM_WINDOWS_COLOR_H