#include <string>
#include <memory>
#include <Windows.h>
#include "common/log_manager.h"
#include "common/logger.h"
#include "main_window.h"
#include "controller.h"

using algorithm::common::Filter;
using algorithm::common::LogManager;
using algorithm::common::Receiver;
using algorithm::common::LogLevel;

void registerDebugOutputLogAppender()
{
    Filter log_filter = [](LogLevel log_level, const std::string &log_name) -> bool {
        return true;
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
