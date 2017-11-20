#include "scene.h"
#include <memory>
#include "circle.h"
#include "text.h"

using std::shared_ptr;
using std::dynamic_pointer_cast;
using algorithm::windows::GraphicsBase;
using algorithm::windows::Color;
using algorithm::windows::Graphics;
using algorithm::windows::Scene;
using algorithm::windows::Circle;
using algorithm::windows::Text;

namespace
{
    void renderCircle(shared_ptr<Circle> circle, ID2D1Factory *factory, ID2D1RenderTarget *render_target)
    {
        ID2D1SolidColorBrush* background_brush = nullptr;
        Color background_color = circle->getBackgroundColor();
        D2D1_COLOR_F background_color_of_d2d = D2D1::ColorF(background_color.getRed(), background_color.getGreen(), background_color.getBlue);
    }

    void renderText(shared_ptr<Text> text, ID2D1Factory *factory, ID2D1RenderTarget *render_target)
    {

    }

    void renderGraphics(shared_ptr<GraphicsBase> graphics, ID2D1Factory* factory, ID2D1RenderTarget* render_target)
    {
        switch (graphics->getType())
        {
        case Graphics::circle:
            renderCircle(dynamic_pointer_cast<Circle>(graphics), factory, render_target);
            break;
        case Graphics::text:
            renderText(dynamic_pointer_cast<Text>(graphics), factory, render_target);
        }
    }
}

void Scene::render(ID2D1Factory *factory, ID2D1RenderTarget *render_target)
{
    
}

void Scene::createD2D1Resource(ID2D1Factory *factory)
{
    
}