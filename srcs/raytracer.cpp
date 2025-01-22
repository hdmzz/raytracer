#include <iostream>
#include "../include/Vector3.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"

/**
 * @param center The center of the sphere.
 * @param radius The radius of the sphere.
 * @param ray The ray being cast.
 * @return The distance to the sphere if hit, otherwise -1.
 */
double	hit_sphere(const Point3& center, double radius, const Ray& ray) {
	Vector3	oc = center - ray.origin();
	auto	a = dot(ray.direction(), ray.direction());
	auto	b = -2.0 * dot(ray.direction(), oc);
	auto	c = dot(oc, oc) -  radius*radius;
	auto	discriminant = b*b - 4*a*c;

	if (discriminant < 0) {
		return (-1);
	} else {
		//on resout l'equation et retourne une valeur correspondant a une distance dans notre cas la distance pour laquelle le rayon touche la sphere
		return ((-b - std::sqrt(discriminant)) / (2.0 * a));
	};
};

/**
 * @param r le rayon lancé
 * la fonction calcul le parametre t qui resout l'équation quadratique de la sphere
 * nous avons besoin du point d'intersection pour les normales
 * Donc recuperation du t, puis, calcul de la normal a partir de ce point: le point du rayon en question ( car t est une distance par rapport au point d'origine dan sune direction donnee) moins
 * le centre de la sphere que l'on touche
 *
 * r.at(t) donnera le point d'intersection auquel on soustrai le centre de la sphere V3(0,0,-1)
 *
 * Sinon on retourn une interpolation lineaire pour creer un gradient de blue vers le blanc comme au depart;
 */
Color	ray_color(const Ray& r) {
	double	t = hit_sphere(Point3(0,0,-1), 0.5, r);
	if (t > 0.0) {
		Vector3	n = unit_vector(r.at(t) - Vector3(0,0,-1));
		return (0.5*Color(n.x() + 1, n.y() + 1, n.z() + 1));
	};
	Vector3	unit_direction = unit_vector(r.direction());
	double	a = 0.5*(unit_direction.y()  + 1);

	return (1 - a) * Color(1,1,1) + Color(0.5, 0.7, 1.0) * a;
};

int	main(void)
{
	auto	aspect_ratio = 16.0 / 9.0;
	int		image_width = 400;
	int		image_height = int(image_width / aspect_ratio);
	auto	focal_lenght = 1.0;
	auto	viewport_height = 2.0;
	auto	viewport_width = viewport_height * (double(image_width)/image_height);
	auto	camera_center = Point3(0,0,0);

	auto	viewport_u = Vector3(viewport_width, 0, 0);
	auto	viewport_v = Vector3(0, -viewport_height, 0);
	std::clog << "viewport V: " << viewport_v << '\n' << std::flush;

	//vertical & horizontal deltaa vectors
	auto	pixel_delta_u = viewport_u / image_width;
	auto	pixel_delta_v = viewport_v / image_height;

	//calcul the top left pixel
	auto	viewport_uppper_left = camera_center - Vector3(0,0,focal_lenght) - viewport_u/2 - viewport_v/2;
	auto	pixel00_loc = viewport_uppper_left + 0.5 * (pixel_delta_u + pixel_delta_v);//pixel 0,0 location

	image_height = image_height < 1 ? 1: image_height;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for (int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines Remainings : " << (image_height - j) << '\n' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto	pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);//centre du pixel qui nous concerne
			auto	ray_direction = pixel_center - camera_center;
			Ray		r(camera_center, ray_direction);

			Color	pixel_color = ray_color(r);

			write_color(std::cout, pixel_color);
		};
	};
	std::clog << "\rDone.				\n";
	return (0);
};
