#include "world.hh"

#include "sphere.hh"

#include <assert.h>

Raytracer::World::World()
{
}

Raytracer::World::~World()
{
    for (std::vector<Surface *>::iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
    {
        delete *it;
    }
    m_surfaces.clear();
}

bool Raytracer::World::hit(const Ray &ray, double t_min, double t_max, Record &record) const
{
    Record tempRecord;
    bool hit_anything = false;
    double closest = t_max;

    for (int i = 0; i < m_surfaces.size(); i++)
    {
        assert(m_surfaces.at(i) != nullptr);

        if (m_surfaces.at(i)->hit(ray, t_min, closest, tempRecord))
        {
            hit_anything = true;
            closest = tempRecord.t;
            record = tempRecord;
        }
    }
    return hit_anything;
}

void Raytracer::World::make_random(int n)
{
    for (int i = 0; i < n; i++)
    {
        Vec3 center(m_random.range(-10, 10), 0, m_random.range(-10, 10));

        double mat_rd = m_random.range();

        if (mat_rd < 0.8)
        {
            Vec3 albedo(m_random.range(), m_random.range(), m_random.range());
            add(new Sphere(center, 0.5, new LambertianMaterial(albedo)));
        }
        else if (mat_rd < 0.95)
        {
            Vec3 albedo(m_random.range(), m_random.range(), m_random.range());
            double fuzz = m_random.range();
            add(new Sphere(center, 0.5, new MetalMaterial(albedo, fuzz)));
        }
        else
        {
            add(new Sphere(center, 0.5, new DielectricMaterial(1.5)));
        }
    }
}

void Raytracer::World::add(Surface *surface)
{
    m_surfaces.push_back(surface);
}
