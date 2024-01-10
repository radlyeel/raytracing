// Begin tracing. 
/* References:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 */
#include "rtweekend.h"
#include "color.h"
#include "hittable.h"
#include "hittablelist.h"
#include "sphere.h"

#include <iostream>

#if 0
double hit_sphere(const point3& center, double radius, const ray& r) {
    // Simplified by replacing b with 2h
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto h /* b/2 */ = dot(oc, r.direction());
    // note that dot(oc,oc) == oc.length_squared() 
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = h*h - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-h - sqrt(discriminant) ) / a;
    }
}
#endif

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r,0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    // No hit, just give background color
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}


int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = static_cast<int> (image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    // See Figure 4: Viewport and pixel grid

    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ( static_cast<double>(image_width)/image_height );
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    auto viewport_upper_left = camera_center - 
                               vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Render
    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
