#ifndef ALGORITHM_WINDOWS_CONTROLLER_H
#define ALGORITHM_WINDOWS_CONTROLLER_H

#include <thread>
#include <d2d1_1.h>
#include "main_window.h"

namespace algorithm
{
    namespace windows
    {
        class Controller
        {
        public:
            explicit Controller(MainWindow *main_window);

            Controller(const Controller&) = delete;

            Controller& operator=(const Controller& rhs) = delete;

            ~Controller();

            ID2D1Factory* getFactory() const { return factory_; };

            ID2D1HwndRenderTarget* getRenderTarget() const { return render_target_; };

            void startRender() { rendering_ = true; };

            bool getRendering() const { return rendering_; };

            void stopRender() { rendering_ = false; };

            bool getNeedResize() { return need_resize_; };

            void setNeedResize(bool value) { need_resize_ = value; };
        
        private:
            std::thread render_thread_;

            MainWindow *main_window_;

            ID2D1Factory* factory_;

            ID2D1HwndRenderTarget* render_target_;

            bool rendering_;

            bool need_resize_;
        };
    }
};

#endif // ALGORITHM_WINDOWS_CONTROLLER_H