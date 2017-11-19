#include "graphics_base.h"
#include <algorithm>

using std::shared_ptr;
using std::remove;
using std::weak_ptr;
using algorithm::windows::GraphicsBase;
using algorithm::windows::Point;

void GraphicsBase::removeChild(shared_ptr<GraphicsBase> child)
{
    children_.erase(remove(children_.begin(), children_.end(), child), children_.end());
    child->parent_ = shared_ptr<GraphicsBase>();
}

void GraphicsBase::appendChild(std::shared_ptr<GraphicsBase> child)
{
    children_.push_back(child);
    child->parent_ = shared_from_this();
}

Point GraphicsBase::getAbsolutePosition() const
{
    Point result;
    result.x = left_;
    result.y = top_;
    for (weak_ptr<GraphicsBase> ancestor = parent_; !ancestor.expired();)
    {
        shared_ptr<GraphicsBase> ancestor_pointer = ancestor.lock();
        result.x += ancestor_pointer->left_;
        result.y += ancestor_pointer->top_;
        ancestor = ancestor_pointer->parent_;
    }
    return result;
}