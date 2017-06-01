#include "d2d_color.h"
#include <cassert>

using namespace algorithm::windows;

D2DColor::D2DColor(Color color, ID2D1RenderTarget* render_target):
color_(color),
render_target_(render_target)
{
    createD2DBrush();
}

D2DColor::D2DColor(const D2DColor& to) :
color_(to.color_),
render_target_(to.render_target_)
{
    createD2DBrush();
}

D2DColor& D2DColor::operator=(const D2DColor& to)
{
    if (&to == this)
    {
        return *this;
    }
    if (d2d_brush_)
    {
        d2d_brush_->Release();
    }
    render_target_ = to.render_target_;
    createD2DBrush();
    return *this;
}

D2DColor::~D2DColor()
{
    if (d2d_brush_)
    {
        d2d_brush_->Release();
    }
}

HRESULT D2DColor::createD2DBrush()
{
    HRESULT result = render_target_->CreateSolidColorBrush(
        D2D1::ColorF(
            color_.getRed(),
            color_.getGreen(),
            color_.getBlue(),
            color_.getAlpha()
        ),
        &d2d_brush_
    );
    assert(SUCCEEDED(result));
    return result;
}
