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
        OutputDebugString(L"Resizing");
        return 0;
    }
}


Controller::Controller(MainWindow* main_window):
main_window_(main_window)
{
    HRESULT result = CoInitialize(NULL);
    assert(result == S_OK);
    result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), reinterpret_cast<void**>(&factory_));
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
    result = render_target_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &black_brush);
    main_window->bind(Event::SIZE, std::bind(resize_callback, main_window, this, std::placeholders::_1, std::placeholders::_2));
    std::thread(std::bind([](Controller* controller) { controller->render(); }, this)).detach();
    assert(result == S_OK);
}

void Controller::render()
{
    HRESULT result;
    
    while(true)
    {
        render_target_->BeginDraw();
        render_target_->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

        D2D1_ELLIPSE ellipse;
        ellipse.point.x = 50;
        ellipse.point.y = 50;
        ellipse.radiusX = 100;
        ellipse.radiusY = 100;

        render_target_->FillEllipse(ellipse, black_brush);
        result = render_target_->EndDraw();
        assert(result == S_OK);
    }
}


Controller::~Controller()
{
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
