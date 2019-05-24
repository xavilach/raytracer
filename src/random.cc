#include "random.hh"

Raytracer::Random::Random() : m_rng(), m_unif(0.0, 1.0)
{
    uint64_t seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed >> 32)};

    m_rng.seed(ss);
}

double Raytracer::Random::range(double min, double max)
{
    return ((max - min) * m_unif(m_rng)) + min;
    //return (max + min) / 2;
}

Raytracer::Vec3 Raytracer::Random::disk(double radius)
{
    Vec3 p;
    do
    {
        p = Vec3(
            range(-1, 1),
            range(-1, 1),
            0);
    } while (p.square_length() >= 1.0);
    return p * radius;
}

Raytracer::Vec3 Raytracer::Random::sphere(double radius)
{
    Vec3 p;
    do
    {
        p = Vec3(
            range(-1, 1),
            range(-1, 1),
            range(-1, 1));
    } while (p.square_length() >= 1.0);
    return p * radius;
}
