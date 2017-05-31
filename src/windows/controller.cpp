#include "controller.h"
#include <cassert>


using namespace algorithm::windows;



Controller::Controller(std::shared_ptr<MainWindow> main_window):
main_window_(main_window)
{
    HRESULT result = CoInitialize(NULL);
    assert(result == S_OK);
    result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), reinterpret_cast<void**>(&factory_));



    assert(result == S_OK);
    result = factory_->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties()

    )
    

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
