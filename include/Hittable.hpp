#pragma  once
#include "Vector3.hpp"
#include "Ray.hpp"
/**
 * Classe qui enregistre les points d'intersections du rayon
 * qui comprendra un point ==> d'intersection,
 * une distance t
 * et la normale de ce point a la surface qu'il touche
*/
class Hit_Record {
    public:
        Point3  p;
        Vector3 normal;
        double  t;
        bool front_face;

        void set_face_normal(const Ray& r, const Vector3& outward_normal)
        {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        };
};

/**
 * classe virtuelle dont heritera tout les objets 3D qu'un rayon peut toucher
 */
class Hittable
{
    public:
        virtual ~Hittable() = default;

        virtual bool    hit(const Ray& ray, double ray_tmin, double ray_tmax, Hit_Record& hit_record) const = 0;
};

