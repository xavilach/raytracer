#include "material.hh"

Raytracer::Random Raytracer::Material::m_random;

static Raytracer::Vec3 reflect(const Raytracer::Vec3 &v, const Raytracer::Vec3 &n)
{
    return v - 2 * v.dot(n) * n;
}

static bool refract(const Raytracer::Vec3 &v, const Raytracer::Vec3 &n, float ni, Raytracer::Vec3 &refracted)
{
    Raytracer::Vec3 uv = v.normalized();
    float dt = uv.dot(n);
    float delta = 1.0 - (ni * ni) * (1 - (dt * dt));
    if (delta > 0)
    {
        refracted = ni * (uv - (n * dt)) - (n * sqrt(delta));
        return true;
    }
    return false;
}

static double schlick(double cosine, double ref_idx)
{
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1 - cosine), 5);
}

Raytracer::NullMaterial::NullMaterial()
{
}

bool Raytracer::NullMaterial::scatter(const Raytracer::Ray &ray, const Raytracer::Surface::Record &record, Raytracer::Vec3 &attenuation, Raytracer::Ray &scattered) const
{
    return false;
}

Raytracer::LambertianMaterial::LambertianMaterial(const Vec3 &a) : m_albedo(a)
{
}

bool Raytracer::LambertianMaterial::scatter(const Raytracer::Ray &ray, const Raytracer::Surface::Record &record, Raytracer::Vec3 &attenuation, Raytracer::Ray &scattered) const
{
    Vec3 target = record.p + record.normal + m_random.sphere();
    scattered = Ray(record.p, target - record.p);
    attenuation = m_albedo;
    return true;
}

Raytracer::MetalMaterial::MetalMaterial(const Vec3 &a, double f) : m_albedo(a)
{
    if (f < 1)
        m_fuzz = f;
    else
        m_fuzz = 1;
}

bool Raytracer::MetalMaterial::scatter(const Raytracer::Ray &ray, const Raytracer::Surface::Record &record, Raytracer::Vec3 &attenuation, Raytracer::Ray &scattered) const
{
    Vec3 reflected = reflect(ray.direction().normalized(), record.normal);
    scattered = Ray(record.p, reflected + m_fuzz * m_random.sphere());
    attenuation = m_albedo;
    return (scattered.direction().dot(record.normal) > 0);
}

Raytracer::DielectricMaterial::DielectricMaterial(double ri) : m_ref_idx(ri)
{
}

bool Raytracer::DielectricMaterial::scatter(const Raytracer::Ray &ray, const Raytracer::Surface::Record &record, Raytracer::Vec3 &attenuation, Raytracer::Ray &scattered) const
{
    Vec3 outward_normal;
    float ni;
    double cosine;

    if (ray.direction().dot(record.normal) > 0)
    {
        outward_normal = -record.normal;
        ni = m_ref_idx;
        cosine = m_ref_idx * ray.direction().dot(record.normal) / ray.direction().length();
    }
    else
    {
        outward_normal = record.normal;
        ni = 1.0 / m_ref_idx;
        cosine = -ray.direction().dot(record.normal) / ray.direction().length();
    }

    Vec3 reflected = reflect(ray.direction(), record.normal);
    Vec3 refracted;

    if (refract(ray.direction(), outward_normal, ni, refracted))
    {
        double reflect_prob = schlick(cosine, m_ref_idx);

        if (m_random.range() < reflect_prob)
        {
            scattered = Ray(record.p, reflected);
        }
        else
        {
            scattered = Ray(record.p, refracted);
        }
    }
    else
    {
        scattered = Ray(record.p, reflected);
    }

    attenuation = Vec3(1, 1, 1);

    return true;
}
