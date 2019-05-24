#ifndef SPHERE_HH_
#define SPHERE_HH_

#include "surface.hh"
#include "vec3.hh"

namespace Raytracer
{
class Sphere : public Surface
{
public:
    Sphere(const Vec3 &center, double radius, const Material *material);

    virtual bool hit(const Ray &ray, double t_min, double t_max, Record &rec) const;

public:
    Vec3 m_center;
    double m_radius;
    const Material *m_material;
};
} // namespace Raytracer

#endif /*SPHERE_HH_*/
