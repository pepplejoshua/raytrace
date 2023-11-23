#pragma once

#include "vec3.h"

class ray {
public:
    ray() {}
    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const {
        // using interpolation formula P(t) = A + tb
        // where A is the origin and b is the direction
        return orig + (t * dir);
    }

private:
    point3 orig;
    vec3 dir;
};