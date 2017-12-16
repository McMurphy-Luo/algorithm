#include <common/macro.h> // config macro staff
#include "./scene.h"
#include <cassert>
#include <memory>
#include <dwrite.h>
#include <common/string_util.h>
#include <common/map_util.h>
#include "./circle.h"
#include "./line.h"
#include "./text.h"

using std::shared_ptr;
using std::map;
using std::set;
using std::pair;
using std::dynamic_pointer_cast;
using algorithm::common::Logger;
using algorithm::common::LogManager;
using algorithm::common::u8StringToWString;
using algorithm::common::differenceTwoSets;
using algorithm::common::keySet;
using algorithm::windows::Line;
using algorithm::windows::GraphicsBase;
using algorithm::windows::Color;
using algorithm::windows::Point;
using algorithm::windows::Graphics;
using algorithm::windows::Scene;
using algorithm::windows::Circle;
using algorithm::windows::Text;

namespace
{
    const char *LOGGER_NAME = "algorithm.windows.Scene";

    D2D1_COLOR_F colorToD2D1Color(const Color& from)
    {
        return D2D1::ColorF(from.getRed() / 255.0f, from.getGreen() / 255.0f, from.getBlue() / 255.0f, from.getAlpha() / 100.0f);
    }

    void renderCircle(shared_ptr<Circle> circle, ID2D1RenderTarget *render_target)
    {
        D2D1_POINT_2F circle_center_point;
        Point circle_top_left_point = circle->getAbsolutePosition();
        circle_center_point.x = circle_top_left_point.left + circle->getRadius();
        circle_center_point.y = circle_top_left_point.top + circle->getRadius();
        D2D1_ELLIPSE d2d_ellipse = D2D1::Ellipse(circle_center_point, circle->getRadius(), circle->getRadius());
        ID2D1SolidColorBrush* background_brush = nullptr;
        D2D1_COLOR_F background_color_of_d2d = colorToD2D1Color(circle->getBackgroundColor());
        render_target->CreateSolidColorBrush(background_color_of_d2d, &background_brush);
        render_target->FillEllipse(d2d_ellipse, background_brush);
        ID2D1SolidColorBrush* border_brush = nullptr;
        D2D1_COLOR_F border_color_of_d2d = colorToD2D1Color(circle->getBorderColor());
        render_target->CreateSolidColorBrush(border_color_of_d2d, &border_brush);
        render_target->DrawEllipse(d2d_ellipse, border_brush, circle->getBorderWidth());
        background_brush->Release();
        border_brush->Release();
    }

    void renderText(shared_ptr<Text> text, ID2D1RenderTarget *render_target, IDWriteTextFormat* text_format)
    {
        Color text_color = text->getColor();
        D2D1_COLOR_F d2d_color = colorToD2D1Color(text_color);
        ID2D1SolidColorBrush *text_brush = nullptr;
        render_target->CreateSolidColorBrush(d2d_color, &text_brush);
        std::wstring node_text = u8StringToWString(text->getContent());
        Point text_position = text->getAbsolutePosition();
        render_target->DrawTextW(
            node_text.c_str(),
            node_text.length(),
            text_format,
            D2D1::RectF(text_position.left, text_position.top, text_position.left + 100, text_position.top + 24),
            text_brush
        );
        text_brush->Release();
    }

    void renderLine(shared_ptr<Line> line, ID2D1RenderTarget *render_target)
    {
        ID2D1SolidColorBrush* brush;
        render_target->CreateSolidColorBrush(colorToD2D1Color(line->getColor()), &brush);
        D2D1_POINT_2F left_top = D2D1::Point2F(line->getLeft(), line->getTop());
        D2D1_POINT_2F bottom_right = D2D1::Point2F(line->getRight(), line->getBottom());
        render_target->DrawLine(left_top, bottom_right, brush);
    }
}

Scene::~Scene()
{
    class_logger_.debug("Scene::~Scene is called!");
    if (text_format_) {
        text_format_->Release();
        text_format_ = nullptr;
    }
    if (write_factory_) {
        write_factory_->Release();
        write_factory_ = nullptr;
    }
}

void Scene::render(ID2D1RenderTarget *render_target)
{
    layer_manager_.beginDraw();
    for (shared_ptr<GraphicsBase> child : getChildren()) {
        renderGraphics(child, render_target);
    }
    render_target->BeginDraw();
    render_target->Clear(colorToD2D1Color(background_color_));
    ID2D1Bitmap* bitmap = layer_manager_.combineLayers(render_target);
    render_target->DrawBitmap(bitmap);
    bitmap->Release();
    layer_manager_.endDraw();
    HRESULT result = render_target->EndDraw();
    if (result == D2DERR_RECREATE_TARGET) {
        result = S_OK;
        createD2D1Resource();
    }
    assert(SUCCEEDED(result));
}

void Scene::createD2D1Resource()
{
    class_logger_.debug("Scene::createD2D1Resource is called!");
    if (text_format_) {
        text_format_->Release();
        text_format_ = nullptr;
    }
    if (write_factory_) {
        write_factory_->Release();
        write_factory_ = nullptr;
    }
    assert(SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, _uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&write_factory_))));
    assert(SUCCEEDED(write_factory_->CreateTextFormat(
        L"Consolas",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        24.0f,
        L"en-us",
        &text_format_
    )));
    text_format_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
}

void Scene::renderGraphics(shared_ptr<GraphicsBase> graphics, ID2D1RenderTarget *render_target)
{
    int z_index_of_this_graphics = graphics->getZIndex();
    ID2D1BitmapRenderTarget *target_layer_render_target = layer_manager_.getLayer(z_index_of_this_graphics, render_target);
    switch (graphics->getType())
    {
    case Graphics::circle:
        renderCircle(dynamic_pointer_cast<Circle>(graphics), target_layer_render_target);
        break;
    case Graphics::text:
        renderText(dynamic_pointer_cast<Text>(graphics), target_layer_render_target, text_format_);
        break;
    case Graphics::line:
        renderLine(dynamic_pointer_cast<Line>(graphics), target_layer_render_target);
        break;
    }
    for (shared_ptr<GraphicsBase> child : graphics->getChildren()) {
        renderGraphics(child, render_target);
    }
}