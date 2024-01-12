// Begin tracing. 
/* References:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html
 */
#include "rtweekend.h"
#include "camera.h"
#include "hittablelist.h"
#include "sphere.h"

#include <iostream>



int main() {

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    

    // render
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.render(world);

    return 0;
}
