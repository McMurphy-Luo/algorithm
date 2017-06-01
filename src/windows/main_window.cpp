#include "main_window.h"
#include <Windows.h>


using namespace algorithm::windows;


namespace //unamed namespace start for this file static staff
{
    LRESULT CALLBACK windowProcedure(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param)
    {
        switch(msg)
        {
        case WM_CREATE:
            //CREATESTRUCT* p_create_struct = reinterpret_cast<CREATESTRUCT*>(l_param);
            //MainWindow* p_created_wnd = reinterpret_cast<MainWindow*>(p_create_struct->lpCreateParams);
            //SetWindowLongPtr(h_wnd, GWLP_USERDATA, (LONG_PTR)p_created_wnd);
            //return p_created_wnd->onCreate(w_param, l_param);
            break;

        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        }
        return DefWindowProc(h_wnd, msg, w_param, l_param);
    }

    void registerWindowClass(const MainWindow* main_window)
    {
        WNDCLASSEX window_class;
        window_class.cbClsExtra = 0;
        window_class.cbSize = sizeof(window_class);
        window_class.hInstance = main_window->getAppHandler();
        window_class.hIcon = nullptr;
        window_class.style = CS_HREDRAW | CS_VREDRAW;
        window_class.hCursor = LoadCursor(nullptr, MAKEINTRESOURCE(32512));
        window_class.cbWndExtra = 0;
        window_class.hIcon = nullptr;
        window_class.hIconSm = nullptr;
		HBRUSH white_brush = CreateSolidBrush(9999);
        window_class.hbrBackground = white_brush;
        window_class.lpszMenuName = nullptr;
        window_class.lpfnWndProc = windowProcedure;
        std::wstring class_name = main_window->getWindowName();
        window_class.lpszClassName = class_name.c_str();
        RegisterClassEx(&window_class);
    }
}//unamed namespace end


MainWindow::MainWindow(HINSTANCE app_handler):
window_name_(L"Main Window"),
app_handler_(app_handler)
{
    registerWindowClass(this);
    window_handler_ = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        window_name_.c_str(),
        window_name_.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        app_handler,
        this
    );
}

MainWindow::~MainWindow()
{
            
}