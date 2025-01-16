#include <iostream>
#include "../include/Vector3.hpp"
#include "../include/Color.hpp"
#include "../include/Ray.hpp"
//le format PPM: un fichier qui contient dans les premieres lignes:
//P3 ==> le format PPM = portable pixmap
//3 2  ==> le nombre de colonnes et le nombre de ligne ici 3 col 2 ligne
//255 ==> le chiffre max pour la couleur
// puis des sequences de chiffre rgb encoded par triplet

//Pour le calcul de la couleur, normaliser le vecteur, puis, definir un facteur t qui varie entre 0 et 1 pour le lerp, ici, on prendra la valeur y du vecteur nomalise
// + 1 diviser par 2
Color	ray_color(const Ray& r) {
	Vector3	unit_direction = unit_vector(r.direction());
	//le facteur t
	double	t = 0.5*(unit_direction.y()  + 1);
	//return LERP (1-t) * startValue + t * endValue avec start value==> couleur blanche et end value ==> couleur bleu pour test gradient
	//ce qui produit un gradient progressif entre le blanc et le bleu en fonction de la valeur de r qui est le rayon partant de chaque pixel du viewport
	return (1 - t) * Color(1,1,1) + Color(0.5, 0.7, 1.0) * t;
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
