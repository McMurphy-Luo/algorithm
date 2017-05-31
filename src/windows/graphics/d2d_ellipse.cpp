#include "D2DEllipse.h"
#include "DebugStream.h"


namespace draw
{
    D2DEllipse::D2DEllipse(ID2D1Factory* factory, ID2D1HwndRenderTarget* render_target, const Ellipse& ellipse, const Point position):
    ParentType(ellipse, position),
    factory_(factory),
    render_target_(render_target),
    d2d_ellipse_({ { static_cast<float>(position_.getX()), static_cast<float>(position_.getY())}, static_cast<float>(graphic_.getRadiusX()), static_cast<float>(graphic_.getRadiusY()) }),
    d2d_background_color_(D2DColor(render_target, ellipse.getBackgroundColor())),
    d2d_border_color_(D2DColor(render_target, ellipse.getBorderColor()))
    {
    }

    void D2DEllipse::move(double x, double y)
    {
        ParentType::move(x, y);
        d2d_ellipse_.point.x = position_.getX();
        d2d_ellipse_.point.y = position_.getY();
    }

    void D2DEllipse::moveTo(Point new_position)
    {
        ParentType::moveTo(new_position);
        d2d_ellipse_.point.x = position_.getX();
        d2d_ellipse_.point.y = position_.getY();
    }

    void D2DEllipse::draw()
    {
        DebugStream ds(L"D2DEllipse::draw is called!");
        render_target_->FillEllipse(d2d_ellipse_, d2d_background_color_.getBrush());
        render_target_->DrawEllipse(d2d_ellipse_, d2d_border_color_.getBrush(), graphic_.getBorderWidth());
    }

    D2DEllipse::~D2DEllipse()
    {
    }
}
