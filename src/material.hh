#ifndef MATERIAL_HH_
#define MATERIAL_HH_

#include "ray.hh"
#include "surface.hh"
#include "vec3.hh"
#include "random.hh"

namespace Raytracer
{
class Material
{
public:
    virtual bool scatter(const Ray &ray, const Surface::Record &record, Vec3 &attenuation, Ray &scattered) const = 0;

protected:
    static Random m_random;
};

class NullMaterial : public Material
{
public:
    NullMaterial();
    virtual bool scatter(const Ray &ray, const Surface::Record &record, Vec3 &attenuation, Ray &scattered) const;
};

class LambertianMaterial : public Material
{
public:
    LambertianMaterial(const Vec3 &a);
    virtual bool scatter(const Ray &ray, const Surface::Record &record, Vec3 &attenuation, Ray &scattered) const;

private:
    Vec3 m_albedo;
};

class MetalMaterial : public Material
{
public:
    MetalMaterial(const Vec3 &a, double f = 0);
    virtual bool scatter(const Ray &ray, const Surface::Record &record, Vec3 &attenuation, Ray &scattered) const;

private:
    Vec3 m_albedo;
    double m_fuzz;
};

class DielectricMaterial : public Material
{
public:
    DielectricMaterial(double ri);
    virtual bool scatter(const Ray &ray, const Surface::Record &record, Vec3 &attenuation, Ray &scattered) const;

private:
    double m_ref_idx;
};

} // namespace Raytracer

#endif /*MATERIAL_HH_*/
