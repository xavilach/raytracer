#include "ray.hh"

Raytracer::Ray::Ray() : m_origin(0), m_direction(0)
{
}

Raytracer::Ray::Ray(const Vec3 &origin, const Vec3 &direction) : m_origin(origin), m_direction(direction)
{
}

Raytracer::Vec3 Raytracer::Ray::origin() const
{
    return m_origin;
}

Raytracer::Vec3 Raytracer::Ray::direction() const
{
    return m_direction;
}

Raytracer::Vec3 Raytracer::Ray::at(double t) const
{
    return m_origin + t * m_direction;
}
