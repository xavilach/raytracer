#ifndef SURFACE_HH_
#define SURFACE_HH_

#include "ray.hh"
#include "vec3.hh"

namespace Raytracer
{
class Material;

class Surface
{
public:
    struct Record
    {
        double t;
        Vec3 p;
        Vec3 normal;
        const Material *material;
    };

    virtual bool hit(const Ray &ray, double t_min, double t_max, Record &record) const = 0;
};
} // namespace Raytracer

#endif /*SURFACE_HH_*/
