#include "controller.h"



using namespace algorithm::windows;



Controller::Controller(std::shared_ptr<MainWindow> main_window):
main_window_(main_window)
{
    
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
}
