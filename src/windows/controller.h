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
            Controller(MainWindow *main_window);
            ~Controller();
			
            void render();
        
        private:
            MainWindow *main_window_;
            ID2D1Factory* factory_;
            ID2D1HwndRenderTarget* render_target_;
			ID2D1SolidColorBrush* black_brush;
        };
    }
};

#endif // ALGORITHM_WINDOWS_CONTROLLER