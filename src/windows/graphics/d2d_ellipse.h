#ifndef DRAW_D2DELLIPSE_H
#define DRAW_D2DELLIPSE_H

#include <boost/noncopyable.hpp>
#include "d2d1.h"
#include "D2DColor.h"
#include "Ellipse.h"
#include "Transformation.h"


namespace draw
{
    class D2DEllipse : public Transformation<Ellipse>
    {
    public:
        typedef Transformation<Ellipse> ParentType;
        typedef Ellipse GraphicType;

    public:
        D2DEllipse( ID2D1Factory* factory, ID2D1HwndRenderTarget* render_target, const Ellipse& ellipse, const Point position = Point(0,0) );
        D2DEllipse(const D2DEllipse& to) = default;
        D2DEllipse& operator=(const D2DEllipse& to) = default;
        ~D2DEllipse() override;
        void move(double x, double y) override;
        void moveTo(Point new_position) override;
        void draw();

    private:
        ID2D1Factory* factory_;
        ID2D1HwndRenderTarget* render_target_;
        D2D1_ELLIPSE d2d_ellipse_;
        D2DColor d2d_background_color_;
        D2DColor d2d_border_color_;
    };
}

#endif //DRAW_D2DELLIPSE_H
