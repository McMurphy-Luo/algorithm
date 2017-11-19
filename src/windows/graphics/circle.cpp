#include "circle.h"
#include <cmath>

using algorithm::windows::Circle;

bool Circle::containsPoint(double x, double y)
{
    double top = getTop();
    double left = getLeft();
    return std::sqrt(std::pow(top - x, 2) + std::pow(left - y, 2) ) < radius_;
}