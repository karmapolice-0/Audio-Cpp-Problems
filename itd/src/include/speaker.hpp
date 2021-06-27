#pragma once

#include <cmath>

class Speaker
{
    public:
        Speaker(double center_x, double center_y, double radius, double angle_sound_velocity) :
            _centerX(center_x), _centerY(center_y), _radius(radius),
            _angleSoundVelocity(angle_sound_velocity)
        {
            calcNextPoint();
        };

        double getX() { return _x; }
        double getY() { return _y; }
        double getAngle() { return _angle; }
        double getVelocity() { return _angleSoundVelocity; }

        void calcNextPoint()
        {
            _x = _radius * cos(_angle) + _centerX;
            _y = _radius * sin(_angle) + _centerY;
            _angle += _angleSoundVelocity;
            if (_angle > 2 * M_PI)
                _angle = 0.0;
        }

        void accelerate(double val) {
            _angleSoundVelocity = val;
        }

    private:
        double _centerX;
        double _centerY;
        double _radius;
        double _x;
        double _y;
        double _angle = 0.0;
        double _angleSoundVelocity;  // meters per samples
};