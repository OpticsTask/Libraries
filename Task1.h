//Task1
#ifndef LEVEL
#define LEVEL

static const double L_PI = 3.1415926535897932384626433832795;

class Level
{
public:
    Level(double radius, double holeDiameter, double density);
    
	double** Dots();
	int Count() { return _n; }
	double Dimension() { return (_rlayer + _rhole) * 2; }
	void Rotate(double angle);
    /// result: in [0, 1] where 0 when not hit in the hole, 1 when hit in the hole center
    double IsHit(double x, double y);
    
private:
    double _rhole; // hole diameter
    double _rlayer; // layer radius
    double _dens; // layer holes density
	double _rotAngle; // layer rotation angle
    int _n; // number of holes in layer
	double _interval; // angle between two heighbor holes in layer    
    
    // finds the distance to the nearest layer hole
    double distanceToNearestHole(double alpha, double r, double x, double y);
    
    static double alpha(double x, double y, double radius);
    static double sqr(double x);
    static double min(double a, double b);
    static double angleDistance(double angle1, double angle2);
    static double radius(double x, double y);
    static double holeTransmittance(double distance, double holeRadius);
};

#endif
