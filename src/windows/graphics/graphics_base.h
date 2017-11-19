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
            double x;
            double y;
        };

        class GraphicsBase;
        typedef std::vector<std::shared_ptr<GraphicsBase>> GraphicsContainer;

        class GraphicsBase : public std::enable_shared_from_this<GraphicsBase>
        {
        public:
            GraphicsBase(Graphics type, double top, double left):
                type_(type),
                top_(top),
                left_(left),
                parent_(shared_ptr<GraphicsBase>(nullptr)),
                children_()
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

            Point getAbsolutePosition() const;

            std::weak_ptr<GraphicsBase> getParent() { return parent_; }

            void appendChild(std::shared_ptr<GraphicsBase> child);

            void removeChild(std::shared_ptr<GraphicsBase> child);

            void clearChild() { children_.clear(); }

            bool hasChild() const { return children_.size() == 0; }

            GraphicsContainer getChildren() { return children_; }

            virtual bool containsPoint(double x, double y) = 0;

        private:
            Graphics type_;
            double top_;
            double left_;
            std::weak_ptr<GraphicsBase> parent_;
            GraphicsContainer children_;
        };
    }
}

#endif //ALGORITHM_WINDOWS_GRAPHICS_BASE