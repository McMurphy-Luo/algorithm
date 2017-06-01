#ifndef ALGORITHM_WINDOWS_POINT_H
#define ALGORITHM_WINDOWS_POINT_H

namespace algorithm
{
    namespace windows
    {
        class Point
        {
        public:
            Point(double x, double y);

            double getX() const { return x_; }
            double getY() const { return y_; }

            void setX(double value) { x_ = value; }
            void setY(double value) { y_ = value; }

        private:
            double x_;
            double y_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_POINT_H