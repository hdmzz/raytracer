#pragma once

#include "Vector3.hpp"

class Ray
{
	private:
		Vector3	orig;
		Vector3	dir;
	public:
		Ray();
		Ray(Vector3 origin, Vector3 direction);
		~Ray();

		const Point3&	origin() const;
		const Vector3&	direction() const;

		Point3	at(double t);
};

Ray::Ray() {};

Ray::Ray(Vector3 origin, Vector3 direction) : orig(origin), dir(direction) {};

Ray::~Ray() {};

const Point3&	Ray::origin() const { return this->orig; };
const Vector3&	Ray::direction() const { return this->dir; };

Point3			Ray::at(double t) { return (orig + t*dir); };
