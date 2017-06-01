#ifndef DRAW_TRANSFORMATION_H
#define DRAW_TRANSFORMATION_H

#include "point.h"

namespace algorithm
{
    namespace windows
    {
        class Transformation
        {
        public:
            explicit Transformation(const Point position = Point(0, 0))
                :position_(position)
            {

            }

            virtual ~Transformation() = default;

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

            virtual void moveTo(const Point to)
            {
                position_ = to;
            }

            virtual void move(double x, double y)
            {
                position_.setX(x + position_.getX());
                position_.setY(y + position_.getY());
            }

        private:
            Point position_;
        };
    }
}


#endif //DRAW_TRANSFORMATION_H