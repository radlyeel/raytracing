#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list: public hittable {
    public:
        // Member functions
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        // Member data
        std::vector<shared_ptr<hittable> > objects;

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) {
            objects.push_back( object );
        }

        bool hit( const ray& r, interval ray_t, hit_record&
                rec) const override { 
            hit_record hr; 
            bool hit_anything = false;
            double closest_so_far = ray_t.max; 
            for (const auto& object : objects) { 
                if (object->hit(r, interval(ray_t.min, closest_so_far), hr)) { 
                    hit_anything = true; 
                    closest_so_far = hr.t; 
                    rec = hr; 
                } 
            } 
            return hit_anything; 
        } 
};
#endif  // HITABLELIST_H
