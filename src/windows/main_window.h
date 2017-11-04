#ifndef ALGORITHM_WINDOWS_MAIN_WINDOW_H
#define ALGORITHM_WINDOWS_MAIN_WINDOW_H

#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <Windows.h>
#include "common/logger.h"

namespace algorithm
{
    namespace windows
    {
        enum class Event
        {
            LBUTTON_DOWN,
            LBUTTON_UP,
            SIZE,
            PAINT,
            COMMAND
        };

        class MainWindow
        {
        public:
            typedef std::shared_ptr<std::function<LRESULT(WPARAM, LPARAM)>> Callback;
            // Because unbind function require the event hanlder could be compared.
            // At the begining, I want just to use std::function<> as callback type,
            // but std::function<> does not support compare.

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

            void unbind(Event which); // remove all event handler of one event type

        protected:
            CallbackContainer* getCallbackContainer(Event which);

        private:
            algorithm::common::Logger class_logger;

            CallbackContainer l_button_down_callback_container_;

            CallbackContainer l_button_up_callback_container_;

            CallbackContainer resize_callback_container_;

            CallbackContainer paint_callback_container_;

            CallbackContainer command_callback_container_;

            std::wstring window_name_;

            HWND window_handler_;

            HINSTANCE app_handler_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_MAIN_WINDOW_H
