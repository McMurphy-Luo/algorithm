#include "graphics_base.h"
#include <algorithm>

using std::shared_ptr;
using std::remove;
using algorithm::windows::GraphicsBase;

void GraphicsBase::removeChild(shared_ptr<GraphicsBase> child)
{
    children_.erase(remove(children_.begin(), children_.end(), child), children_.end());
}