#include <common/macro.h>
#include "./line.h"
#include <cmath>

using algorithm::windows::Line;

namespace
{
    double PRECISION = 0.00001;
}

bool Line::containsPoint(double x, double y)
{
    double distance_to_top_left = std::sqrt(std::pow(x - getLeft(), 2) + std::pow(y - getTop(), 2));
    double distance_to_bottom_right = std::sqrt(std::pow(x - getRight(), 2) + std::pow(y - getBottom(), 2));
    double length_of_me = std::sqrt(std::pow(getLeft() - getRight(), 2) + std::pow(getTop() - getBottom(), 2));
    return distance_to_top_left + distance_to_bottom_right - length_of_me < PRECISION;
}