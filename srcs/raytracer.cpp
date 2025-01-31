#include "raytracer.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"
#include <random>
/**
 * @param r le rayon lancé
 * @param world une reference constante a un objet de type hittable, l'objet est un Hittable List mais on recoit un hittable 
 * dont hittable list herite la conversion est implicite
 * la fonction calcul le parametre t qui resout l'équation quadratique de la sphere
 * nous avons besoin du point d'intersection pour les normales
 * Donc recuperation du t, puis, calcul de la normal a partir de ce point: le point du rayon en question
 * ( car t est une distance par rapport au point d'origine dans une direction donnee) moins le centre de la sphere que l'on touche
 *
 * r.at(t) donnera le point d'intersection auquel on soustrai le centre de la sphere V3(0,0,-1)
 *
 * Sinon, on retourne une interpolation lineaire pour creer un gradient de blue vers le blanc comme au depart;
 *
 *
 * Nouvelle facon de faire:
 * pour chaque objet contenu dans le 'monde' world==> appeller la fonction hit de l'objet et lui passer le rayon le tmin et tmax et un objet de type hit Record

 */
Color	ray_color(const Ray& r, const Hittable& world)
{
    Hit_Record  hit_record;

    if (world.hit(r, 0, infinity, hit_record)) {
        return 0.5 * (hit_record.normal + Color(1,1,1));
    };

	Vector3	unit_direction = unit_vector(r.direction());
	double	a = 0.5*(unit_direction.y()  + 1);

	return (1 - a) * Color(1,1,1) + Color(0.5, 0.7, 1.0) * a;
};

// Amélioration de la fonction random_double avec plus de précision
inline double random_double() {
    static std::mt19937_64 gen(std::random_device{}());  // 64-bit Mersenne Twister
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
}

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

    Hittable_list world;

    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.4));
    world.add(make_shared<Sphere>(Point3(0.9, 0, -1), 0.4));

    // Augmentation significative du nombre d'échantillons
    int samples_per_pixel = 100;  // 100 échantillons au lieu de 4

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
	for (int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines Remainings : " << (image_height - j) << '\n' << std::flush;
		for (int i = 0; i < image_width; i++) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                auto u = (i + random_double()) / (image_width - 1.0);
                auto v = (j + random_double()) / (image_height - 1.0);
                auto sample_loc = viewport_uppper_left + (u * viewport_u) + (v * viewport_v);
                Ray r(camera_center, sample_loc - camera_center);
                pixel_color += ray_color(r, world);
            }
            auto r = sqrt(pixel_color.x() / samples_per_pixel);
            auto g = sqrt(pixel_color.y() / samples_per_pixel);
            auto b = sqrt(pixel_color.z() / samples_per_pixel);

            write_color(std::cout, Color(r, g, b));
		};
	};
	std::clog << "\rDone.\n";
	return (0);
};
