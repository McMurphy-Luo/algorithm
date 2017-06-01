#ifndef DRAW_D2DELLIPSE_H
#define DRAW_D2DELLIPSE_H

#include "d2d1.h"
#include "d2d_color.h"
#include "ellipse.h"


namespace algorithm
{
    namespace windows
    {
        class D2DEllipse
        {
        public:
            D2DEllipse(ID2D1Factory* factory, ID2D1RenderTarget* render_target, const Ellipse& ellipse)
                :factory_(factory),
                render_target_(render_target),
                ellipse_(ellipse),
                d2d_background_color_(D2DColor(ellipse.getBackgroundColor(), render_target)),
                d2d_border_color_(D2DColor(ellipse.getBorderColor(), render_target))
            {
                
            };

        private:
            ID2D1Factory* factory_;
            ID2D1RenderTarget* render_target_;
            Ellipse ellipse_;
            D2DColor d2d_background_color_;
            D2DColor d2d_border_color_;
        };
    }
    
}

#endif //DRAW_D2DELLIPSE_H
