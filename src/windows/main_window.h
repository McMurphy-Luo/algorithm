#ifndef ALGORITHM_WINDOWS_MAIN_WINDOW_H
#define ALGORITHM_WINDOWS_MAIN_WINDOW_H

#include <string>
#include <vector>
#include <functional>
#include <Windows.h>

namespace algorithm
{
    namespace windows
    {
        enum class Event
        {
            LBUTTON_DOWN,
            LBUTTON_UP,
            SIZE
        };
        class MainWindow
        {
        public:
            typedef LRESULT(*Callback)(WPARAM, LPARAM);

            typedef std::vector<Callback> CallbackContainer;

        public:
            MainWindow(HINSTANCE app_handler);

            MainWindow(const MainWindow&) = delete;

            MainWindow& operator=(MainWindow& rhs) = delete;

            ~MainWindow();

            std::wstring getWindowName() const { return window_name_; }

            HWND getWindowHandler() const { return window_handler_; }

            HINSTANCE getAppHandler() const { return app_handler_; }

            RECT getSize() const;

            void show() const { ShowWindow(window_handler_, SW_SHOW); UpdateWindow(window_handler_); }

            void hide() const { ShowWindow(window_handler_, SW_HIDE); }

            void trigger(Event whitch, WPARAM w_param, LPARAM l_param);

            void bind(Event which, Callback callback);

            void unbind(Event which, Callback callback);

        protected:
            CallbackContainer* getCallbackContainer(Event which);

        private:
            CallbackContainer l_button_down_callback_container_;

            CallbackContainer l_button_up_callback_container_;

            CallbackContainer resize_callback_container_;

            std::wstring window_name_;

            HWND window_handler_;

            HINSTANCE app_handler_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_MAIN_WINDOW_H