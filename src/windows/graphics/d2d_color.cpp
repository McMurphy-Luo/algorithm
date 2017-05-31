#include "D2DColor.h"
#include <cassert>

namespace draw
{
    D2DColor::D2DColor(ID2D1RenderTarget* render_target, const Color& color):
    render_target_(render_target),
    color_(color)
    {
        createD2DBrush();
    }

    D2DColor::D2DColor(const D2DColor& to):
    render_target_(to.render_target_),
    color_(to.color_)
    {
        createD2DBrush();
    }

    D2DColor& D2DColor::operator=(const D2DColor& to)
    {
        render_target_ = to.render_target_;
        color_ = to.color_;
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
}