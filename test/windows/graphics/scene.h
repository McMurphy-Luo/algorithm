#ifndef ALGORITHM_WINDOWS_SCENE_H
#define ALGORITHM_WINDOWS_SCENE_H

#include <memory>
#include <map>
#include <set>
#include <d2d1_1.h>
#include <common/log_manager.h>
#include <common/logger.h>
#include "./graphics_base.h"
#include "./layer_manager.h"
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
    layer_manager_(),
    background_color_(135, 206, 235),
    write_factory_(nullptr),
    text_format_(nullptr)
  {
    // do nothing
  }

  virtual ~Scene();

  void discard();

  void render(ID2D1RenderTarget* render_target);

  Color getBackgroundColor() const { return background_color_; }

  void setBackgroundColor(const Color& value) { background_color_ = value; }

  virtual bool containsPoint(double x, double y) override { return true; }

protected:
  void renderGraphics(std::shared_ptr<GraphicsBase> graphics, ID2D1RenderTarget* render_target);

private:
  algorithm::common::Logger class_logger_;
  LayerManager layer_manager_;
  Color background_color_;
  IDWriteFactory* write_factory_;
  IDWriteTextFormat* text_format_;
};

}
}

#endif //ALGORITHM_WINDOWS_SCENE_H