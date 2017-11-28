#ifndef ALGORITHM_WINDOWS_SCENE_H
#define ALGORITHM_WINDOWS_SCENE_H

#include <memory>
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
            void createD2D1Resource();

        private:
            algorithm::common::Logger class_logger_;
            Color background_color_;
            IDWriteFactory *write_factory_;
            IDWriteTextFormat *text_format_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_SCENE_H