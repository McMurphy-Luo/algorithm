#ifndef ALGORITHM_WINDOWS_GRAPHICS_BASE
#define ALGORITHM_WINDOWS_GRAPHICS_BASE

namespace algorithm
{
    namespace windows
    {
        class GraphicsBase
        {
        public:
            void setTop(double top) { top_ = top; };
            void setLeft(double left) { left_ = left; };
            void setWidth(double width) { width_ = width; };
            void setHeight(double height) { height_ = height; };
            double getTop() { return top_; };
            double getLeft() { return left_; };
            double getWidth() { return width_; };
            double getHeight() { return height_; };

        private:
            double top_;
            double left_;
            double width_;
            double height_;
            GraphicsBase* parent_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_GRAPHICS_BASE