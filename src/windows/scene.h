#ifndef ALGORITHM_WINDOWS_SCENE_H
#define ALGORITHM_WINDOWS_SCENE_H

#include "./render/graphics_base.h"

namespace algorithm
{
    namespace windows
    {
        class Scene : public GraphicsBase
        {
        public:
            Scene() :
                GraphicsBase(0, 0, nullptr)
            {
                /* do nothing */
            }

            virtual bool containsPoint(double x, double y) override { return true; }
        };
    }
}

#endif //ALGORITHM_WINDOWS_SCENE_H