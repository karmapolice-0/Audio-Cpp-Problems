#pragma once

#include "speaker.hpp"
#include "utils.hpp"

class Observer
{
public:
    Observer(double left_x, double left_y, double right_x, double right_y) :
        _leftX(left_x), _leftY(left_y), _rightX(right_x), _rightY(right_y)
    {};
    double getEarDelta(Speaker speaker)
    {
        double left_distance = distance(speaker.getX(), speaker.getY(), _leftX, _leftY);
        double right_distance = distance(speaker.getX(), speaker.getY(), _rightX, _rightY);
        return left_distance - right_distance;
    }

private:
    double _leftX;
    double _leftY;
    double _rightX;
    double _rightY;
};