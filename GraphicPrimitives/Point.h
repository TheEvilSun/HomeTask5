#pragma once

#include <math.h>

namespace GraphicPrimitive {

struct Point
{
    double x = 0;
    double y = 0;

    Point(double x_val, double y_val) : x(x_val), y(y_val) {

    }

    bool operator==(const Point& other) {
        return std::abs(x - other.x) < 0.0000000000001 && std::abs(y - other.y) < 0.0000000000001;
    }

    bool operator !=(const Point& other) {
        return std::abs(x - other.x) > 0.0000000000001 || std::abs(y - other.y) > 0.0000000000001;
    }
};
}
