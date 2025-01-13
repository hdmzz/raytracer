#include <iostream>
#include "../include/Vector3.hpp"
#include "../include/Color.hpp"
//le format PPM: un fichier qui contient dans les premieres lignes:
//P3 ==> le format PPM = portable pixmap
//3 2  ==> le nombre de colonnes et le nombre de ligne ici 3 col 2 ligne
//255 ==> le chiffre max pour la couleur
// puis des sequences de chiffre rgb encoded par triplet
int	main(void)
{
	int	img_width = 256;
	int	img_height = 256;
	std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
	for (int j = 0; j < img_height; j++) {
		std::clog << "\rScanlines Remainings : " << (img_height - j) << ' ' << std::flush;
		for (int i = 0; i < img_width; i++) {
			Vector3	v = Vector3(double(i) / (img_width - 1), double(j) / (img_height - 1), 0.0);
			write_color(std::cout, v);
		};
	};
	std::clog << "\rDone.				\n";
	return (0);
};
