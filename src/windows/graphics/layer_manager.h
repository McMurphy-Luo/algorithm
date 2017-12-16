#ifndef ALGORITHM_WINDOWS_LAYER_MANAGER_H
#define ALGORITHM_WINDOWS_LAYER_MANAGER_H

#include <map>
#include <set>
#include <string>
#include <d2d1_1.h>

namespace algorithm
{
    namespace windows
    {
        class LayerManager
        {
        protected:
            typedef std::map<int, ID2D1BitmapRenderTarget*>::const_iterator LayerIterator;

        public:
            LayerManager():
                used_layers_of_render_round_(),
                layers_(),
                am_i_in_render_round_(false)
            {
                /* do nothing */
            }

            LayerManager(const LayerManager& another) = delete;

            LayerManager& operator=(const LayerManager& another) = delete;

            ~LayerManager();

            ID2D1BitmapRenderTarget* getLayer(int index, ID2D1RenderTarget* parent);

            void beginDraw();

            void endDraw();

            ID2D1Bitmap* combineLayer(int which, ID2D1RenderTarget* parent);

            ID2D1Bitmap* combineLayers(std::set<int> which, ID2D1RenderTarget* parent);

            ID2D1Bitmap* combineLayers(ID2D1RenderTarget* parent);

            std::string toString() const;

        private:
            std::set<int> used_layers_of_render_round_;
            std::map<int, ID2D1BitmapRenderTarget*> layers_;
            bool am_i_in_render_round_;
        };
    }
}

#endif // ALGORITHM_WINDOWS_LAYER_MANAGER_H