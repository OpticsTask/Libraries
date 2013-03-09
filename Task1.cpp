#include "stdafx.h"
#include "Task1.h"
#include <math.h>

Level::Level(double radius, double holeDiameter, double density)
{
    _rlayer = radius;
    _rhole = holeDiameter / 2.0;
    _dens = density;
    
	int maxHolesCount;
	if (radius == 0)
	{
		maxHolesCount = 1;
	}
	else
	{
		maxHolesCount = (int)(L_PI / asin(_rhole / _rlayer));
	}

    _n = (int)(_dens * maxHolesCount);
    _interval = 2 * L_PI / _n;
}

void Level::Rotate(double angle)
{
	double angleRad = - angle * L_PI / 180;

    _rotAngle = fmod(angleRad, _interval);
}

// computing on the fly
double** Level::Dots()
{
    double **dots = new double*[_n];
    for (int i=0; i<_n; ++i)
        dots[i]=new double[2];

    for (int i = 0; i < _n; i++)
    {
        double angle = i * _interval + _rotAngle;
        dots[i][0] = _rlayer * cos(angle);
        dots[i][1] = _rlayer * sin(angle);
    }
    return dots;
}

double Level::IsHit(double x, double y)
{
    double radius = Level::radius(x, y);
    double alpha = Level::alpha(x, y, radius);
    double distance = distanceToNearestHole(alpha, radius, x, y);
    return holeTransmittance(distance, _rhole);
}

double Level::alpha(double x, double y, double radius)
{
    if (radius == 0) return 0;

		double result;
		if (y >= 0)
			result = acos(x / radius);
		else
			result = 2 * L_PI - acos(x / radius);

    return fmod(result, 2 * L_PI);
}

double Level::sqr(double x)
{
    return x * x;
}

double Level::min(double a, double b)
{
    return (a <= b ? a : b);
}

double Level::angleDistance(double angle1, double angle2)
{
    double diff = min(fabs(angle1 - angle2 + 2 * L_PI), fabs(angle1 - angle2 - 2 * L_PI));
    diff = min (diff, fabs(angle1 - angle2));

    return diff;
}

double Level::radius(double x, double y)
{
    return sqrt(Level::sqr(x) + Level::sqr(y));
}
    
double Level::holeTransmittance(double distance, double holeRadius)
{
    return (distance < holeRadius ? 1 : 0);
    //return (distance < (holeDiameter / 2.0) ? (holeDiameter / 2.0 - distance) / (holeDiameter / 2.0) : 0);
}

double Level::distanceToNearestHole(double alpha, double r, double x, double y)
{
    int holeNum = (int)(alpha / _interval);
    double angle1 = fmod( holeNum * _interval + _rotAngle, 2 * L_PI);
    double angle2 = fmod((holeNum + 1) * _interval + _rotAngle, 2 * L_PI);
    double angleDistance1 = Level::angleDistance(angle1, alpha);
    double angleDistance2 = Level::angleDistance(angle2, alpha);
    double nearestHoleAngle = (angleDistance1 < angleDistance2 ? angle1 : angle2);

	return sqrt(Level::sqr(x - _rlayer * cos(nearestHoleAngle)) + Level::sqr(y - _rlayer * sin(nearestHoleAngle)));
}
