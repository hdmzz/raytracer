#include "raytracer.hpp"
#include "Hittable_list.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

int	main(void)
{
    Hittable_list world;
    Camera cam;
    world.add(make_shared<Sphere>(Point3(0, 0, -1), 0.4));
    world.add(make_shared<Sphere>(Point3(0.9, 0, -1), 0.4));

    cam.render(world);

    return 0;
};
