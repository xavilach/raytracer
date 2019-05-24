#include "camera.hh"

#include <math.h>

Raytracer::Camera::Camera(const Vec3 &position, const Vec3 &target, const Vec3 &up, double vfov, double aspect, double aperture, double focus_dist) : m_origin(position), m_lens_radius(aperture / 2)
{
    double theta = vfov * (M_PI / 180);
    double half_height = tan(theta / 2.0) * focus_dist;
    double half_width = aspect * half_height;

    m_w = (position - target).normalize();
    m_u = up.cross(m_w).normalize();
    m_v = m_w.cross(m_u);

    m_ll_corner = m_origin - (half_width * m_u) - (half_height * m_v) - (focus_dist * m_w);
    m_horizontal = (2 * half_width) * m_u;
    m_vertical = (2 * half_height) * m_v;
}

Raytracer::Ray Raytracer::Camera::ray(double u, double v)
{
    Vec3 rd = m_random.disk(m_lens_radius);
    Vec3 offset = m_u * rd.x() + m_v * rd.y() + m_origin;
    return Ray(offset, m_ll_corner + u * m_horizontal + v * m_vertical - offset);
}
