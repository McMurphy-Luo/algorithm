#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/debug_output_backend.hpp>
#include <Windows.h>
#include "main_window.h"
#include "controller.h"


// Complete sink type
typedef boost::log::sinks::synchronous_sink< boost::log::sinks::debug_output_backend > sink_t;

void setup_logging()
{
    boost::shared_ptr< boost::log::core > core = boost::log::core::get();
    // Create the sink. The backend requires synchronization in the frontend.
    boost::shared_ptr< sink_t > sink(new sink_t());
    // Set the special filter to the frontend
    // in order to skip the sink when no debugger is available
    sink->set_filter(boost::log::expressions::is_debugger_present());
    core->add_sink(sink);
}

int CALLBACK wWinMain(HINSTANCE h_instance, HINSTANCE h_preview_instance, LPWSTR cmd_string, int cmd_show) {
    setup_logging();
    algorithm::windows::MainWindow *the_main_window = new algorithm::windows::MainWindow(h_instance);
    the_main_window->show();
    algorithm::windows::Controller *the_controller = new algorithm::windows::Controller(the_main_window);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    delete the_controller;
    delete the_main_window;
    
    return static_cast<int>(msg.wParam);
}
