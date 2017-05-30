#ifndef ALGORITHM_WINDOWS_CONTROLLER
#define ALGORITHM_WINDOWS_CONTROLLER

#include <memory>
#include <Windows.h>
#include <d2d1_1.h>
#include "main_window.h"


namespace algorithm
{
    namespace windows
    {
        class Controller
        {
        public:
            Controller(std::shared_ptr<MainWindow> main_window);
            ~Controller();

            void render();
        
        private:
            std::shared_ptr<MainWindow> main_window_;
            ID2D1Factory* factory_;
            ID2D1HwndRenderTarget* render_target_;
        };
    }
};

#endif // ALGORITHM_WINDOWS_CONTROLLER