#include <Windows.h>
#include "main_window.h"

int CALLBACK wWinMain(HINSTANCE h_instance, HINSTANCE h_preview_instance, LPWSTR cmd_string, int cmd_show) {
    
    algorithm::windows::MainWindow *the_main_window = new algorithm::windows::MainWindow(h_instance);
    the_main_window->show();

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    delete the_main_window;
    
    return msg.wParam;
}