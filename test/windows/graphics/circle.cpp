#include <common/macro.h> // config macro staff
#include "./circle.h"
#include <cmath>

using algorithm::windows::Circle;

bool Circle::containsPoint(double x, double y)
{
    double top = getTop();
    double left = getLeft();
    return std::sqrt(std::pow(top + radius_ - y, 2) + std::pow(left + radius_ - x, 2) ) < radius_;
}