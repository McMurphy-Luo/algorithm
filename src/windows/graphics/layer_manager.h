#ifndef ALGORITHM_WINDOWS_LAYER_MANAGER_H
#define ALGORITHM_WINDOWS_LAYER_MANAGER_H

#include <map>
#include <set>
#include <d2d1_1.h>
#include <memory>

namespace algorithm
{
    namespace windows
    {
        namespace detail
        {
            void release(ID2D1Resource *target) { target->Release(); }
        }

        class LayerManager
        {
        public:
            LayerManager() :
                layers_()
            {
                /* do nothing */
            }

            ID2D1BitmapRenderTarget* getLayer(int index, ID2D1RenderTarget* parent);

            void freeLayer(int index);

            void freeLayers(std::set<int> layers);

            std::size_t size() { return layers_.size(); }

            std::shared_ptr<ID2D1Bitmap> combineLayers(std::set<int> which);

        private:
            std::map<int, ID2D1BitmapRenderTarget*> layers_;
        };
    }
}

#endif // ALGORITHM_WINDOWS_LAYER_MANAGER_H