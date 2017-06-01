#ifndef ALGORITHM_WINDOWS_D2DCOLOR_H
#define ALGORITHM_WINDOWS_D2DCOLOR_H

#include "d2d1_1.h"
#include "color.h"


namespace algorithm
{
    namespace windows
    {
        class D2DColor
        {
        public:
            D2DColor(Color color_, ID2D1RenderTarget* render_target);
            D2DColor(const D2DColor& to);
            D2DColor& operator=(const D2DColor& to);
            ~D2DColor();
            ID2D1SolidColorBrush* getBrush() const { return d2d_brush_; };


        private:
            Color color_;
            HRESULT createD2DBrush();
            ID2D1RenderTarget* render_target_;
            ID2D1SolidColorBrush* d2d_brush_;
        };

    }
}


#endif //ALGORITHM_WINDOWS_D2DCOLOR_H
