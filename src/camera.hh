#ifndef CAMERA_HH_
#define CAMERA_HH_

#include "ray.hh"
#include "random.hh"
#include "vec3.hh"

namespace Raytracer
{
class Camera
{
public:
    Camera(const Vec3 &position, const Vec3 &target, const Vec3 &up, double vfov, double aspect, double aperture, double focus_dist);
    Ray ray(double u, double v);

private:
    Vec3 m_origin;
    Vec3 m_ll_corner;
    Vec3 m_horizontal;
    Vec3 m_vertical;

    Vec3 m_u;
    Vec3 m_v;
    Vec3 m_w;

    double m_lens_radius;

    Random m_random;
};
} // namespace Raytracer

#endif /*CAMERA_HH_*/
