#pragma once

#include "Vector3.hpp"
#include <iostream>

using	Color = Vector3;

void	write_color(std::ostream& out, const Color& pixel_color) {
	auto	r = pixel_color.x();
	auto	g = pixel_color.y();
	auto	b = pixel_color.z();

	//transormer les valeurs comprise dans la classe Vector3  entre [0, 1] dans la plage [0, 255]
	int		rbyte = int(255.999999 * r);
	int		gbyte = int(255.999999 * g);
	int		bbyte = int(255.999999 * b);

	//ecrire la valeur de couleur sur la sortie
	out << rbyte << ' ' <<  gbyte << ' ' << bbyte << '\n';
};
