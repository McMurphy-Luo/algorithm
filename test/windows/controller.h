#ifndef ALGORITHM_WINDOWS_CONTROLLER_H
#define ALGORITHM_WINDOWS_CONTROLLER_H

#include <string>
#include <d2d1_1.h>
#include <data_structure/binary_tree.h>
#include <data_structure/rb_tree.h>
#include <common/logger.h>
#include "./main_window.h"
#include "./graphics/scene.h"
#include "./graphics/circle.h"

namespace algorithm
{
    namespace windows
    {
        namespace detail
        {
            int string_comparator(const std::string& lhs, const std::string& rhs);
        }

        class Controller final
        {
        public:
            explicit Controller(MainWindow* main_window);

            Controller(const Controller& another) = delete;

            Controller& operator=(const Controller& rhs) = delete;

            ~Controller();

            ID2D1HwndRenderTarget* getRenderTarget() const { return render_target_; };

            void render();

        protected:
            void reArrangeChildWindow();

            LRESULT onCommand(WPARAM w_param, LPARAM l_param);

            LRESULT onPaint(WPARAM w_param, LPARAM l_param);

            LRESULT onSize(WPARAM w_param, LPARAM l_param);

            LRESULT onMouseMove(WPARAM w_param, LPARAM l_param);

        private:
            algorithm::common::Logger class_logger;

            MainWindow* main_window_;

            MainWindow::Callback resize_callback_;
            
            MainWindow::Callback paint_callback_;

            MainWindow::Callback command_callback_;

            MainWindow::Callback mouse_move_callback_;

            bool need_resize_;

            std::shared_ptr<Scene> main_scene_;

            std::shared_ptr<GraphicsBase> current_graphics_under_mouse_;

            Color previous_border_color_of_circle_;

            algorithm::data_structure::RBTree<std::string, std::string, detail::string_comparator> the_tree_;

            HWND button_;

            HWND input_;

            ID2D1Factory* factory_;

            ID2D1HwndRenderTarget* render_target_;
        };
    }
};

#endif // ALGORITHM_WINDOWS_CONTROLLER_H
