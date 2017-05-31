#ifndef DRAW_TRANSFORMATION_H
#define DRAW_TRANSFORMATION_H

#include "Point.h"

namespace draw
{
    template<typename T>
    class Transformation
    {
    public:
        explicit Transformation(const T& graphic, const Point position = Point(0,0)):
        graphic_(graphic),
        position_(position)
        {
            
        }
        Transformation(const Transformation& to) = default;
        Transformation& operator=(const Transformation& to) = default;
        virtual ~Transformation() = default;

        virtual T getGraphic() const
        {
            return graphic_;
        }

        virtual double getPositionX() const
        {
            return position_.getX();
        }

        virtual double getPositionY() const
        {
            return position_.getY();
        }

        virtual Point getPosition() const
        {
            return position_;
        }

    protected:
        virtual void setGraphic(const T& graphic)
        {
            graphic_ = graphic;
        }

        virtual void rePosition()
        {
            position_.setX(0);
            position_.setY(0);
        }

        virtual void moveTo(const Point to)
        {
            position_ = to;
        }

        virtual void move(double x, double y)
        {
            position_.setX(x + position_.getX());
            position_.setY(y + position_.getY());
        }

    protected:
        T graphic_;
        Point position_;
    };
}


#endif //DRAW_TRANSFORMATION_H