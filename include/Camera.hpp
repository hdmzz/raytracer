#include "raytracer.hpp"
/**
 * @class Camera seul les params aspect ratio et image_width sont publics
 * car tout les autres params decoulent de ces deuxx  la
*/
class Camera
{
private:
    int image_height;
    double focal_lenght;
    double viewport_height;
    double viewport_width;
    Point3 camera_center;
    Vector3 viewport_u;
    Vector3 viewport_v;
   	Vector3	pixel_delta_u;
	Vector3	pixel_delta_v;
	Vector3	viewport_uppper_left;
	Vector3	pixel00_loc;


public:
    double aspect_ratio = 1.0;
    int image_width = 400;

    Camera()
    {
        image_height = int(image_width / aspect_ratio);
        focal_lenght = 1.0;
        viewport_height = 2.0;
        viewport_width = viewport_height * (double(image_width)/image_height);
        camera_center = Point3(0,0,0);
        viewport_u = Vector3(viewport_width, 0, 0);
        viewport_v = Vector3(0, -viewport_height, 0);
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;
        viewport_uppper_left = camera_center - Vector3(0,0,focal_lenght) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_uppper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    	image_height = image_height < 1 ? 1: image_height;
    };

    void render(const Hittable_list& world)
    {
    	std::clog << "viewport V: " << viewport_v << '\n' << std::flush;
    };
};
