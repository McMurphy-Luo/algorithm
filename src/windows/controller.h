﻿#ifndef ALGORITHM_WINDOWS_CONTROLLER_H
#define ALGORITHM_WINDOWS_CONTROLLER_H


#include <d2d1_1.h>
#include "main_window.h"
#include "render/tree_render.h"


namespace algorithm
{
    namespace windows
    {
        namespace detail
        {
            int string_comparator(const std::string& lhs, const std::string& rhs);
        }

        class Controller
        {
        public:
            explicit Controller(MainWindow *main_window);

            Controller(const Controller&) = delete;

            Controller& operator=(const Controller& rhs) = delete;

            ~Controller();

            ID2D1Factory* getFactory() const { return factory_; };

            ID2D1HwndRenderTarget* getRenderTarget() const { return render_target_; };

            void startRender() const;

            void render();

            void stopRender() const;

            bool getNeedResize() const { return need_resize_; };

            void setNeedResize(bool value) { need_resize_ = value; };
        
        private:
            MainWindow *main_window_;

            ID2D1Factory* factory_;

            ID2D1HwndRenderTarget* render_target_;

            bool need_resize_;

            TreeRender<detail::string_comparator>* tree_render_;
        };
    }
};

#endif // ALGORITHM_WINDOWS_CONTROLLER_H