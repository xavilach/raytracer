#ifndef WORLD_HH_
#define WORLD_HH_

#include "material.hh"
#include "surface.hh"
#include "random.hh"

#include <vector>

namespace Raytracer
{
class World : public Surface
{
public:
    World();
    ~World();
    virtual bool hit(const Ray &ray, double t_min, double t_max, Record &record) const;

    void make_random(int n);
    void add(Surface *surface);

private:
    std::vector<Surface *> m_surfaces;
    Random m_random;
};
} // namespace Raytracer

#endif /*WORLD_HH_*/
