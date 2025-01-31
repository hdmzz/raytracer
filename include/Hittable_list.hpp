#pragma once

#include "Hittable.hpp"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

/**
 * on aura une liste d'objet hittable
 * pour chaque objet on va appeller la fonction hit qui calcul si le rayon touche l'objet,
 * en fait c'est lobjet qui se debrouille tout seul
 * pour ce faire,
 * il faut un enrregistreur que lon passe a la fonction hit de chaque objet
 */

class Hittable_list : public Hittable
{
private:
    /* data */
public:
    std::vector<shared_ptr<Hittable>> objects;
    void clear() { objects.clear(); };

    void add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    };

/**
 * le but de cette fonction est de calculer la premiere intersection du rayon pour ne pas avoir a refaire tout les calcul pour tout les objets??
*/
    bool hit(const Ray& ray, double ray_tmin, double ray_tmax, Hit_Record& hit_record) const override
    {
        Hit_Record temp_hit_record;
        bool hit_anything =  false;
        auto closest_so_far = ray_tmax;//le t pour lequel on a une intersection le plus proche

        for (const auto& object : objects) {
            if (object->hit(ray, ray_tmin, ray_tmax, temp_hit_record)) {
                //si on la hit function renvoie true, la reference de hit  record contiendra le t pour lequel le  rayo touche l'objet
                hit_anything = true;
                closest_so_far = temp_hit_record.t;
                hit_record = temp_hit_record;
            };
        };
        return hit_anything;
    };
};
