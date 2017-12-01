#include <common/macro.h> // config macro staff
#include "./scene.h"
#include <cassert>
#include <memory>
#include <dwrite.h>
#include <common/string_util.h>
#include "./circle.h"
#include "./text.h"

using std::shared_ptr;
using std::dynamic_pointer_cast;
using algorithm::common::Logger;
using algorithm::common::LogManager;
using algorithm::common::u8StringToWString;
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
        Logger class_logger = LogManager::getLogger(LOGGER_NAME);
        class_logger.debug("rendering an circle");
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

        render_target->DrawEllipse(d2d_ellipse, border_brush, 4);

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

    void renderScene(shared_ptr<Scene> scene, ID2D1RenderTarget* render_target)
    {
        ID2D1SolidColorBrush* background_brush = nullptr;
        D2D1_COLOR_F d2d_color = colorToD2D1Color(scene->getBackgroundColor());
        render_target->Clear(d2d_color);
    }

    void renderGraphics(shared_ptr<GraphicsBase> graphics, ID2D1RenderTarget *render_target, IDWriteTextFormat* text_format)
    {
        switch (graphics->getType())
        {
        case Graphics::circle:
            renderCircle(dynamic_pointer_cast<Circle>(graphics), render_target);
            break;
        case Graphics::text:
            renderText(dynamic_pointer_cast<Text>(graphics), render_target, text_format);
            break;
        case Graphics::scene:
            renderScene(dynamic_pointer_cast<Scene>(graphics), render_target);
        }
        for (shared_ptr<GraphicsBase> child : graphics->getChildren()) {
            renderGraphics(child, render_target, text_format);
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

void Scene::render(ID2D1RenderTarget *render_target)
{    
    render_target->BeginDraw();
    renderGraphics(shared_from_this(), render_target, text_format_);
    HRESULT result;
    result = render_target->EndDraw();
    if (result == D2DERR_RECREATE_TARGET) {
        result == S_OK;
        createD2D1Resource();
    }
    assert(SUCCEEDED(result));
}

void Scene::createD2D1Resource()
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
    text_format_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    assert(SUCCEEDED(result));
}