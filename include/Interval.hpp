#include "raytracer.hpp"

class Interval
{
private:
    double min, max;
public:
    Interval(double min, double max) : min(min), max(max) {};
    Interval() : min(-infinity), max(+infinity) {};
    ~Interval();
};

