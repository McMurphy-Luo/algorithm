#include "main_window.h"
#include <cassert>
#include <algorithm>
#include <Windows.h>
#include <boost/log/trivial.hpp>


using namespace algorithm::windows;


namespace //unamed namespace start for this file static staff
{
    LRESULT CALLBACK windowProcedure(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param)
    {
        switch(msg)
        {
        case WM_CREATE:
            {
            CREATESTRUCT* p_create_struct = reinterpret_cast<CREATESTRUCT*>(l_param);
            MainWindow* p_created_wnd = reinterpret_cast<MainWindow*>(p_create_struct->lpCreateParams);
            SetWindowLongPtr(h_wnd, GWLP_USERDATA, (LONG_PTR)p_created_wnd);
            return 0;
            }

        case WM_LBUTTONDOWN:
            reinterpret_cast<MainWindow*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA))->trigger(Event::LBUTTON_DOWN, w_param, l_param);
            return 0;

        case WM_PAINT:
            reinterpret_cast<MainWindow*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA))->trigger(Event::PAINT, w_param, l_param);
            return 0;

        case WM_LBUTTONUP:
            reinterpret_cast<MainWindow*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA))->trigger(Event::LBUTTON_UP, w_param, l_param);
            return 0;

        case WM_SIZE:
            reinterpret_cast<MainWindow*>(GetWindowLongPtr(h_wnd, GWLP_USERDATA))->trigger(Event::SIZE, w_param, l_param);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;


        case BN_CLICKED:

            return 0;
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
        window_class.style = 0;
        window_class.hCursor = LoadCursor(nullptr, MAKEINTRESOURCE(32512));
        window_class.cbWndExtra = 0;
        window_class.hIcon = nullptr;
        window_class.hIconSm = nullptr;
        window_class.hbrBackground = nullptr;
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
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        app_handler,
        this
    );

    button_ = CreateWindow(
        L"BUTTON",
        L"OK",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10,
        10,
        70,
        40,
        window_handler_,
        nullptr,
        app_handler,
        nullptr
    );

}

MainWindow::~MainWindow()
{

}


void MainWindow::trigger(Event which, WPARAM w_param, LPARAM l_param)
{
    CallbackContainer* callback_list = getCallbackContainer(which);
    CallbackContainer::const_iterator iter;
    for (iter = callback_list->cbegin(); iter != callback_list->cend(); ++iter)
    {
        (*(*iter))(w_param, l_param);
    }
}


MainWindow::CallbackContainer* MainWindow::getCallbackContainer(Event which) {
    switch (which)
    {
    case Event::LBUTTON_DOWN:
        return &l_button_down_callback_container_;
    case Event::LBUTTON_UP:
        return &l_button_up_callback_container_;
    case Event::SIZE:
        return &resize_callback_container_;
    case Event::PAINT:
        return &paint_callback_container_;
    }
    assert(false); //should never be here
    return nullptr;
}

RECT MainWindow::getSize() const
{
    RECT client_rect;
    GetClientRect(window_handler_, &client_rect);
    return client_rect;
}

void MainWindow::bind(Event which, Callback call_back)
{
    getCallbackContainer(which)->push_back(call_back);
}

void MainWindow::unbind(Event which, Callback call_back)
{
    CallbackContainer* container_of_which = getCallbackContainer(which);
    container_of_which->erase(std::remove(container_of_which->begin(), container_of_which->end(), call_back), container_of_which->end());
}
