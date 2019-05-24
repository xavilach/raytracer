#include "sphere.hh"

#include <math.h>

#include <assert.h>

Raytracer::Sphere::Sphere(const Vec3 &center, double radius, const Material *material) : m_center(center), m_radius(radius), m_material(material)
{
}

bool Raytracer::Sphere::hit(const Ray &ray, double t_min, double t_max, Record &record) const
{
    Vec3 oc = ray.origin() - m_center;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * oc.dot(ray.direction());
    double c = oc.dot(oc) - m_radius * m_radius;
    double delta = (b * b) - 4 * (a * c);
    if (delta > 0)
    {
        assert(a > 0);

        double temp = (-b - sqrt(delta)) / (2.0 * a);
        if (t_min < temp && temp < t_max)
        {
            record.t = temp;
            record.p = ray.at(record.t);
            record.normal = (record.p - m_center) / m_radius;
            record.material = m_material;
            return true;
        }
        temp = (-b + sqrt(delta)) / (2.0 * a);
        if (t_min < temp && temp < t_max)
        {
            record.t = temp;
            record.p = ray.at(record.t);
            record.normal = (record.p - m_center) / m_radius;
            record.material = m_material;
            return true;
        }
    }
    return false;
}
