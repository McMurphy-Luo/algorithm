#ifndef DRAW_D2DCOLOR_H
#define DRAW_D2DCOLOR_H

#include "d2d1.h"
#include "color.h"


namespace algorithm
{
    namespace windows
    {
        class D2DColor
        {
        public:
            D2DColor(ID2D1RenderTarget* render_target, const Color& color);
            D2DColor(const D2DColor& to);
            D2DColor& operator=(const D2DColor& to);
            ~D2DColor();

            ID2D1SolidColorBrush* getBrush() const { return d2d_brush_; };
            Color getColor() const { return color_; };
            void setColor(Color color) { color_ = color; createD2DBrush(); };


        private:
            HRESULT createD2DBrush();
            ID2D1RenderTarget* render_target_;
            ID2D1SolidColorBrush* d2d_brush_;
            Color color_;
        };

    }
}


#endif //DRAW_D2DCOLOR_H
