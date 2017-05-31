#ifndef DRAW_POINT_H
#define DRAW_POINT_H
namespace draw
{
    class Point
    {
    public:
        Point(double x, double y);
        Point(const Point& to) = default;
        Point& operator=(const Point& to) = default;
        ~Point() = default;

        double getX() const { return x_; }
        double getY() const { return y_; }

        void setX(double value) { x_ = value; }
        void setY(double value) { y_ = value; }

    private:
        double x_;
        double y_;
    };
}

#endif //DRAW_POINT_H