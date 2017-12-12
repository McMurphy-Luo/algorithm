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
        class LayerManager
        {
        public:
            LayerManager():
                layers_()
            {
                /* do nothing */
            }

            std::size_t size() { return layers_.size(); }

            ID2D1BitmapRenderTarget* getLayer(int index, ID2D1RenderTarget* parent);

            bool hasLayer(int index) { return layers_.find(index) != layers_.end(); };

            void freeLayer(int index);

            void freeLayers(std::set<int> layers);

            void freeLayers();

            ID2D1Bitmap* combineLayer(int which, ID2D1RenderTarget* parent);

            ID2D1Bitmap* combineLayers(std::set<int> which, ID2D1RenderTarget* parent);

            ID2D1Bitmap* combineLayers(ID2D1RenderTarget* parent);

        private:
            std::map<int, ID2D1BitmapRenderTarget*> layers_;
        };
    }
}

#endif // ALGORITHM_WINDOWS_LAYER_MANAGER_H