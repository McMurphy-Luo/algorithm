#include <common/macro.h> // config macro staff
#include <string>
#include <memory>
#include <Windows.h>
#include <common/log_manager.h>
#include <common/logger.h>
#include "./windows/main_window.h"
#include "./windows/controller.h"

using algorithm::common::Filter;
using algorithm::common::LogManager;
using algorithm::common::Receiver;
using algorithm::common::LogLevel;

void registerDebugOutputLogAppender()
{
    Filter log_filter = [](LogLevel log_level, const std::string &log_name) -> bool {
        return log_name != "algorithm.windows.MainWindow";
    };
    Receiver log_receiver = 
        std::make_shared<std::function<void(const std::string& content)>>(
        [](const std::string& content)
        {
            OutputDebugStringA(content.c_str());
        }
    );
    LogManager::registerAppender(log_filter, log_receiver);
    LogManager::enableEnsureLineEnding(true);
}

int CALLBACK wWinMain(HINSTANCE h_instance, HINSTANCE h_preview_instance, LPWSTR cmd_string, int cmd_show)
{
    registerDebugOutputLogAppender();
    algorithm::windows::MainWindow* the_main_window = new algorithm::windows::MainWindow(h_instance);
    algorithm::windows::Controller* the_controller = new algorithm::windows::Controller(the_main_window);
    the_main_window->show();
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    delete the_controller;
    delete the_main_window;
#ifdef _CRTDBG_MAP_ALLOC // When define this, uses visual studio crt memory leaks detection feature
    LogManager::freeLogManager(); // only for memory leaks detection tools.
    // free the global singleton instance of LogManager to prevent leak.
#endif // _CRTDBG_MAP_ALLOC
    _CrtDumpMemoryLeaks();
    return static_cast<int>(msg.wParam);
}
