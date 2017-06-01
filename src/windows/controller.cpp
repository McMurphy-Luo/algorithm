#include "controller.h"
#include <cassert>


using namespace algorithm::windows;



Controller::Controller(MainWindow* main_window):
main_window_(main_window)
{
    HRESULT result = CoInitialize(NULL);
    assert(result == S_OK);
    result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), reinterpret_cast<void**>(&factory_));

    assert(result == S_OK);
    result = factory_->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(main_window->getWindowHandler(), D2D1::Size(1000U, 1000U)),
        &render_target_
    );
    assert(result == S_OK);
	result = render_target_->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &black_brush);
	assert(result == S_OK);

}

void Controller::render()
{
	OutputDebugString(L"rendering");
	HRESULT result;
	render_target_->BeginDraw();
	D2D1_ELLIPSE ellipse;
	ellipse.point.x = 100;
	ellipse.point.y = 100;
	ellipse.radiusX = 500;
	ellipse.radiusY = 500;
	

	render_target_->FillEllipse(ellipse, black_brush);
	result = render_target_->EndDraw();
	assert(result == S_OK);
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
