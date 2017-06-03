#include "controller.h"
#include <cassert>
#include <thread>


using namespace algorithm::windows;


namespace
{
    LRESULT resize_callback(MainWindow* window, Controller* controller, WPARAM w_param, LPARAM l_param)
    {
        RECT client_rect = window->getSize();
        D2D1_SIZE_U client_size;
        client_size.width = client_rect.right - client_rect.left;
        client_size.height = client_rect.bottom - client_rect.top;
        controller->getRenderTarget()->Resize(client_size);
        return 0;
    }

    void render(Controller *controller)
    {
        HRESULT result;

        ID2D1RenderTarget* render_target = controller->getRenderTarget();
        ID2D1SolidColorBrush* black_brush;

        render_target->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &black_brush);

        while (controller->getRendering())
        {
            controller->getRenderTarget()->BeginDraw();
            render_target->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

            D2D1_ELLIPSE ellipse;
            ellipse.point.x = 50;
            ellipse.point.y = 50;
            ellipse.radiusX = 100;
            ellipse.radiusY = 100;

            render_target->FillEllipse(ellipse, black_brush);
            result = render_target->EndDraw();
            assert(result == S_OK);
        }
    }
}


Controller::Controller(MainWindow* main_window):
main_window_(main_window),
rendering_(false)
{
    HRESULT result = CoInitialize(NULL);
    assert(result == S_OK);
    result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory), reinterpret_cast<void**>(&factory_));
    assert(result == S_OK);
    RECT client_rect = main_window->getSize();
    D2D1_SIZE_U client_size;
    client_size.width = client_rect.right - client_rect.left;
    client_size.height = client_rect.bottom - client_rect.top;
    result = factory_->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(main_window->getWindowHandler(), client_size),
        &render_target_
    );
    assert(result == S_OK);
    render_ = std::bind(&render, this);
    this->startRender();
    std::thread(render_).detach();
    main_window->bind(Event::SIZE, std::bind(resize_callback, main_window, this, std::placeholders::_1, std::placeholders::_2));
    assert(result == S_OK);
}



Controller::~Controller()
{
    this->stopRender();
    if (factory_)
    {
        factory_->Release();
    }
    if (render_target_)
    {
        render_target_->Release();
    }
    CoUninitialize();
}
