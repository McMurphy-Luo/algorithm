#include <string>
#include <Windows.h>

namespace algorithm
{
    namespace windows
    {
        class MainWindow
        {
        public:
            MainWindow(HINSTANCE app_handler);
            ~MainWindow();

            std::wstring getWindowName() const
            {
                return window_name_;
            }

            HWND getWindowHandler() const
            {
                return window_handler_;
            }

            HINSTANCE getAppHandler() const
            {
                return app_handler_;
            }

            void show() const
            {
                ShowWindow(window_handler_, SW_SHOW);
                UpdateWindow(window_handler_);
            }

            void hide() const
            {
                ShowWindow(window_handler_, SW_HIDE);
            }

        private:
            std::wstring window_name_;
            HWND window_handler_;
            HINSTANCE app_handler_;
        };
    }
}