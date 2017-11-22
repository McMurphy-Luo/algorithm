#include "./scene.h"
#include <cassert>
#include <memory>
#include <dwrite.h>
#include "./circle.h"
#include "./text.h"

using std::shared_ptr;
using std::dynamic_pointer_cast;
using algorithm::windows::GraphicsBase;
using algorithm::windows::Color;
using algorithm::windows::Point;
using algorithm::windows::Graphics;
using algorithm::windows::Scene;
using algorithm::windows::Circle;
using algorithm::windows::Text;

namespace
{
    void renderCircle(shared_ptr<Circle> circle, ID2D1Factory *factory, ID2D1RenderTarget *render_target)
    {
        D2D1_POINT_2F circle_center_point;
        Point circle_top_left_point = circle->getAbsolutePosition();
        circle_center_point.x = circle_top_left_point.x + circle->getRadius();
        circle_center_point.y = circle_top_left_point.y + circle->getRadius();
        D2D1_ELLIPSE d2d_ellipse = D2D1::Ellipse(circle_center_point, circle->getRadius(), circle->getRadius());

        ID2D1SolidColorBrush* background_brush = nullptr;
        Color background_color = circle->getBackgroundColor();
        D2D1_COLOR_F background_color_of_d2d = D2D1::ColorF(background_color.getRed(), background_color.getGreen(), background_color.getBlue());
        render_target->CreateSolidColorBrush(background_color_of_d2d, &background_brush);
        render_target->FillEllipse(d2d_ellipse, background_brush);

        ID2D1SolidColorBrush* border_brush = nullptr;
        Color border_color = circle->getBorderColor();
        D2D1_COLOR_F border_color_of_d2d = D2D1::ColorF(border_color.getRed(), border_color.getGreen(), border_color.getBlue());
        render_target->CreateSolidColorBrush(border_color_of_d2d, &border_brush);
        render_target->DrawEllipse(d2d_ellipse, border_brush);

        background_brush->Release();
        border_brush->Release();
    }

    void renderLine(shared_ptr<Text> text, ID2D1Factory *factory, ID2D1RenderTarget *render_target)
    {

    }

    void renderText(shared_ptr<Text> text, ID2D1Factory *factory, ID2D1RenderTarget *render_target)
    {

    }

    void renderGraphics(shared_ptr<GraphicsBase> graphics, ID2D1Factory *factory, ID2D1RenderTarget *render_target)
    {
        switch (graphics->getType())
        {
        case Graphics::circle:
            renderCircle(dynamic_pointer_cast<Circle>(graphics), factory, render_target);
            break;
        case Graphics::text:
            renderText(dynamic_pointer_cast<Text>(graphics), factory, render_target);
        case Graphics::line:
            
        }
        for (shared_ptr<GraphicsBase> child : graphics->getChildren()) {
            renderGraphics(child, factory, render_target);
        }
    }
}

Scene::~Scene()
{
    if (text_format_) {
        text_format_->Release();
    }
    if (write_factory_) {
        write_factory_->Release();
    }
}

void Scene::render(ID2D1Factory *factory, ID2D1RenderTarget *render_target)
{
    
}

void Scene::createD2D1Resource(ID2D1Factory *factory, ID2D1RenderTarget *render_target)
{
    HRESULT result;
    result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, _uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&write_factory_));
    assert(SUCCEEDED(result));
    result = write_factory_->CreateTextFormat(
        L"Consolas",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        24.0f,
        L"en-us",
        &text_format_
    );
    assert(SUCCEEDED(result));
}