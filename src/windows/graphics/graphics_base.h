#ifndef ALGORITHM_WINDOWS_GRAPHICS_BASE
#define ALGORITHM_WINDOWS_GRAPHICS_BASE

#include <vector>
#include <memory>

namespace algorithm
{
    namespace windows
    {
        enum class Graphics {
            circle,
            text,
            line,
            scene
        };

        struct Point
        {
            double left;
            double top;
        };

        class GraphicsBase;
        typedef std::vector<std::shared_ptr<GraphicsBase>> GraphicsContainer;

        class GraphicsBase : public std::enable_shared_from_this<GraphicsBase>
        {
        public:
            GraphicsBase(Graphics type, double left, double top):
                type_(type),
                left_(left),
                top_(top),
                parent_(std::shared_ptr<GraphicsBase>()),
                children_(),
                z_index_(0)
            {
                /* do nothing */
            }

            GraphicsBase(Graphics type):
                GraphicsBase(type, 0, 0)
            {
                /* do nothing */
            }

            GraphicsBase(const GraphicsBase& another) = default;

            GraphicsBase& operator=(const GraphicsBase& another) = default;

            virtual ~GraphicsBase() = default;

            Graphics getType() const { return type_; }

            void setTop(double top) { top_ = top; }

            void setLeft(double left) { left_ = left; }

            double getTop() const { return top_; }

            double getLeft() const { return left_; }

            int getZIndex() const { return z_index_; }

            void setZIndex(int value) { z_index_ = value; }

            Point getAbsolutePosition() const;

            std::weak_ptr<GraphicsBase> getParent() { return parent_; }

            void appendChild(std::shared_ptr<GraphicsBase> child);

            void removeChild(std::shared_ptr<GraphicsBase> child);

            void clearChildren() { children_.clear(); }

            bool hasChild() const { return children_.size() == 0; }

            GraphicsContainer getChildren() { return children_; }

            virtual bool containsPoint(double x, double y) = 0;

        private:
            Graphics type_;
            double left_;
            double top_;
            std::weak_ptr<GraphicsBase> parent_;
            GraphicsContainer children_;
            int z_index_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_GRAPHICS_BASE