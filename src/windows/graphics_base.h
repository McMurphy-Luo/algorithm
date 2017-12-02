#ifndef ALGORITHM_WINDOWS_GRAPHICS_BASE
#define ALGORITHM_WINDOWS_GRAPHICS_BASE

#include <vector>
#include <memory>

namespace algorithm
{
    namespace windows
    {
        class GraphicsBase;
        typedef std::vector<std::shared_ptr<GraphicsBase>> GraphicsContainer;

        class GraphicsBase
        {
        public:
            GraphicsBase(double top, double left, std::shared_ptr<GraphicsBase> parent):
                top_(top),
                left_(left),
                parent_(parent),
                children_()
            {
                /* do nothing */
            }

            GraphicsBase(double top, double left) :
                GraphicsBase(top, left, nullptr)
            {
                /* do nothing */
            }

            GraphicsBase(std::shared_ptr<GraphicsBase> parent):
                GraphicsBase(0, 0, parent)
            {
                /* do nothing */
            }

            GraphicsBase():
                GraphicsBase(0, 0, nullptr)
            {
                /* do nothing */
            }

            GraphicsBase(const GraphicsBase& another) = default;

            GraphicsBase& operator=(const GraphicsBase& another) = default;

            virtual ~GraphicsBase() = default;

            void setTop(double top) { top_ = top; }

            void setLeft(double left) { left_ = left; }

            double getTop() { return top_; }

            double getLeft() { return left_; }

            std::weak_ptr<GraphicsBase> getParent() { return parent_; }

            virtual bool containsPoint(double x, double y) = 0;

        private:
            double top_;
            double left_;
            std::weak_ptr<GraphicsBase> parent_;
            GraphicsContainer children_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_GRAPHICS_BASE