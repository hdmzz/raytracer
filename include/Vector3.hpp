#ifndef	VECTOR3_H
#define	VECTOR3_H
#include <cmath>
#include <iostream>

class	Vector3 {
	public:
		double	e[3];// tableau de double pour les coordonnees x y z
		Vector3(): e{0, 0, 0} {};
		Vector3(double x, double y, double z): e{x, y, z} {};
		~Vector3(){};

		double	x()  const { return e[0]; }
		double	y()  const { return e[1]; }
		double	z()  const { return e[2]; }

		Vector3	operator-() const {
			return Vector3(-e[0], -e[1], -e[2]);
		};

		double	operator[](int i) const {
			return e[i];
		};

		double&	operator[](int i) {
			return e[i];
		};

		Vector3&	operator+=(const Vector3& v) {
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];

			return *this;
		};

		Vector3&	operator*=(double t) {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;

			return *this;
		};

		Vector3&	operator/=(double t) {
			return *this *= 1/t;
		};

		double	lenght_squared() const {
			return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
		};

		double	lenght() const {
			return std::sqrt(this->lenght_squared());
		};

};

using	Point3 = Vector3;//on peut appeler la classe Vector 3 en la nommant Point3 au lieu de Vector3
//surcharge d'operateur utils
inline std::ostream&	operator<<(std::ostream& out, const Vector3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
};

//addition disponible uniquement entre 2 vecteurs
inline Vector3	operator+(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
};

inline Vector3	operator-(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
};

inline Vector3	operator*(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
};

inline Vector3	operator*(double t, const Vector3& v) {
	return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
};

inline Vector3	operator*(const Vector3& v, double t) {
	return t * v;
};

inline Vector3	operator/(double t, const Vector3& v) {
	return (1/t) * v;
};

inline double	dot(const Vector3& u, const Vector3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
};

inline Vector3	cross(const Vector3& u, const Vector3& v) {
	return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
				u.e[2] * v.e[0] - u.e[0] * v.e[2],
				u.e[0] * v.e[1] - u.e[1] * v.e[0]);
};

#endif
