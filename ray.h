/* Reference: Chapter 3:  Rays, a simple camera, and background
 *
 * Shirley, Peter. Ray Tracing in One Weekend (Ray Tracing Minibooks Book 1) 
 * (p. 9). Kindle Edition. 
 */
 
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction): orig(origin), dir(direction) {}
        point3 origin()    const { return orig; }
        vec3 direction()   const { return dir; }
        point3 at(double t) const { return orig + t * dir; }

    private:
        point3 orig;
        vec3 dir;
};


#endif // RAY_H
