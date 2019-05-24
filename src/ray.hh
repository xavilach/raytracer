#ifndef RAY_HH_
#define RAY_HH_

#include "vec3.hh"

namespace Raytracer
{
class Ray
{
public:
    Ray();
    Ray(const Vec3 &origin, const Vec3 &direction);

    Vec3 origin() const;
    Vec3 direction() const;
    Vec3 at(double t) const;

private:
    Vec3 m_origin;
    Vec3 m_direction;
};

} // namespace Raytracer

#endif /*RAY_HH_*/
