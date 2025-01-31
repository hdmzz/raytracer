#pragma once

#include "Hittable.hpp"
#include "Vector3.hpp"

class Sphere : public Hittable
{
private:
    Point3 center;
    double radius;
public:
    Sphere(const Point3& c, double r) : center(c), radius(std::fmax(0, r)) {}

    /** La fonction hit est definie comme const car elle ne modifiera pas l'objet auquel elle appartient
     * et Override indique au compilateur qu'on reecrit une fonctionde la classe abstraite dont
     * on herite ici, expemle parms d'autres,
     * si on  'indique pas que la fonction hit est reecrite le compilateur ne verifiera pas que la fonctionn est bien
     * orthgraphiée .....
     *
     * l'equation est simplifie mais reste essentielement la meme
     */
    bool    hit(const Ray& ray, double ray_tmin, double ray_tmax, Hit_Record& hit_record) const override
    {
        Vector3 oc = center - ray.origin();
        	auto	a = ray.direction().lenght_squared();
            auto	half_b = dot(ray.direction(), oc);
            auto	c = oc.lenght_squared() -  radius*radius;
            auto	discriminant = half_b*half_b - a*c;

            if (discriminant < 0) {
                return (false);
            };
            auto sqrtd = std::sqrt(discriminant);
            auto t = (half_b - sqrtd) / a;//le t etant la distance pour laquelle on a au moins une solution
            //on verifie si la distamce pour laquelle nous avons une solutions
            //est comprise entre la ddistance min et la distance max
            if (t <= ray_tmin || t >= ray_tmax) {
                //dans ce cas la on reprend l'equation qui resout t ou l'on a originelement?? -b (+ || -) sqrt(b) / 2a
                //on essaye le cas ou l'on soustrait le determinant
                t = (half_b + sqrtd) / a;
                if (t <= ray_tmin || t >= ray_tmax) {
                    //si cette condition n'est pas remplie alors on est hors des limites que nousdefinissont
                    return false;
                };
            };

            //si on passe de ce cote des conditions on a trouve une solution pour t dans la plage tmin tmax et on peut l'enregistrer dans le Hit Record
            hit_record.p = ray.at(t);
            hit_record.t = t;
            hit_record.normal = (hit_record.p - center) / radius;//norraliser

            Vector3 outward_normal = (hit_record.p - center) / radius;
            hit_record.set_face_normal(ray, outward_normal);

            return true;
    };
};
