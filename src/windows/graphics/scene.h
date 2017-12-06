#ifndef ALGORITHM_WINDOWS_SCENE_H
#define ALGORITHM_WINDOWS_SCENE_H

#include <memory>
#include <map>
#include <set>
#include <d2d1_1.h>
#include <common/log_manager.h>
#include <common/logger.h>
#include "./graphics_base.h"
#include "./color.h"

namespace algorithm
{
    namespace windows
    {
        class Scene : public GraphicsBase
        {
        public:
            Scene():
                GraphicsBase(Graphics::scene, 0, 0),
                class_logger_(algorithm::common::LogManager::getLogger("algorithm.windows.Scene")),
                layers_(),
                background_color_(135, 206, 235),
                write_factory_(nullptr),
                text_format_(nullptr)
            {
                createD2D1Resource();
            }

            virtual ~Scene();

            void render(ID2D1RenderTarget *render_target);

            Color getBackgroundColor() const { return background_color_; }

            void setBackgroundColor(const Color& value) { background_color_ = value; }

            virtual bool containsPoint(double x, double y) override { return true; }

        protected:
            typedef std::map<int, ID2D1BitmapRenderTarget *>::iterator LayerIterator;

            typedef std::map<int, ID2D1BitmapRenderTarget *>::const_iterator ConstLayerIterator;

            void createD2D1Resource();

            void renderGraphics(std::shared_ptr<GraphicsBase> graphics, ID2D1RenderTarget *render_target);

        private:
            algorithm::common::Logger class_logger_;
            std::map<int, ID2D1BitmapRenderTarget*> layers_;
            std::set<int> used_layers_of_render_round_;
            Color background_color_;
            IDWriteFactory *write_factory_;
            IDWriteTextFormat *text_format_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_SCENE_H