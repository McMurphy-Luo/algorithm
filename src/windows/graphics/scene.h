#ifndef ALGORITHM_WINDOWS_SCENE_H
#define ALGORITHM_WINDOWS_SCENE_H

#include <memory>
#include <d2d1_1.h>
#include "./graphics_base.h"

namespace algorithm
{
    namespace windows
    {
        class Scene : public GraphicsBase
        {
        public:
            Scene():
                GraphicsBase(Graphics::scene, 0, 0)
            {
                /* do nothing */
            }

            void render(ID2D1Factory *factory, ID2D1RenderTarget *render_target);

            virtual bool containsPoint(double x, double y) override { return true; }

            void createD2D1Resource(ID2D1Factory *factory);

        private:
            IDWriteFactory *write_factory_;
            IDWriteTextFormat *text_format_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_SCENE_H