#include <iostream>

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
	for (int j = 0; j < img_width; j++) {
		for (int i = 0; i < img_height; i++) {
			//i et j sont caster  en double, on se retrouve avec des chiffres entre 0 et -1
			auto	r = double(i) / (img_width - 1);
			auto	g = double(j) / (img_height - 1);
			auto	b = 0.0;
			//mutiplier par 255.999 pour s'assurer que les valeurs s'etalent bien sur la plage 0 ==> 255
			int		ir = int(255.999 * r);
			int		ig = int(255.999 * g);
			int		ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		};
	};
	return (0);
};
