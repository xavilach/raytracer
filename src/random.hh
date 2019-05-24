#ifndef RANDOM_HH_
#define RANDOM_HH_

#include "vec3.hh"

#include <random>
#include <chrono>

namespace Raytracer
{
class Random
{
public:
    Random();

    double range(double min = 0.0, double max = 1.0);
    Vec3 disk(double radius = 1.0);
    Vec3 sphere(double radius = 1.0);

private:
    std::mt19937_64 m_rng;
    std::uniform_real_distribution<double> m_unif;
};
} // namespace Raytracer

#endif /*RANDOM_HH_*/
