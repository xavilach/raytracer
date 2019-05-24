#include "screen.hh"
#include "world.hh"
#include "sphere.hh"
#include "camera.hh"
#include "ray.hh"
#include "vec3.hh"
#include "random.hh"
#include "threadpool.hh"
#include "material.hh"

#include <iostream>
#include <limits>
#include <thread>
#include <assert.h>

using namespace Raytracer;

struct rect_t
{
    int x;
    int y;
    int width;
    int height;
};

static Vec3 cast_ray(const Ray &ray, const World &world, int depth)
{
    Surface::Record record;
    if (world.hit(ray, 0.001, std::numeric_limits<double>::max(), record))
    {
        Ray scattered;
        Vec3 attenuation;

        assert(record.material != nullptr);

        if ((depth < 50) && (record.material->scatter(ray, record, attenuation, scattered)))
        {
            return attenuation * cast_ray(scattered, world, depth + 1);
        }
        else
        {
            return Vec3(0, 0, 0);
        }
    }
    else
    {
        Vec3 dir = ray.direction().normalized();
        double t = 0.5 * (dir.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

static void render(rect_t to_render, int ns, Screen *screen, Camera *camera, World *world, Random *rand)
{
    for (int j = to_render.y; j < to_render.y + to_render.height; j++)
    {
        for (int i = to_render.x; i < to_render.x + to_render.width; i++)
        {
            Vec3 pixel(0, 0, 0);
            if (ns > 0)
            {
                for (int s = 0; s < ns; s++)
                {
                    double u = double(i + rand->range(-1, 1)) / double(screen->width());
                    double v = double(j + rand->range(-1, 1)) / double(screen->height());

                    pixel += cast_ray(camera->ray(u, v), *world, 0);
                }
                pixel /= double(ns);
            }
            else
            {
                double u = double(i) / double(screen->width());
                double v = double(j) / double(screen->height());

                pixel += cast_ray(camera->ray(u, v), *world, 0);
            }

            screen->setPixel(i, screen->height() - 1 - j, pixel * 255.99);
        }
    }
}

int main(int argc, char *argv[])
{
    int nx = 800;
    int ny = 400;
    int ns = 100;

    int nt = 8;
    int nw = 10;
    int nh = 10;

    Screen screen("Raytracer", nx, ny);

    if (!screen.init())
    {
        std::cerr << "Raytracer::Screen::init failed." << std::endl;
        return -1;
    }

    Random rand;

    World world;
    world.add(new Sphere(Vec3(0, 0, -1), 0.5, new LambertianMaterial(Vec3(0.1, 0.2, 0.5))));
    world.add(new Sphere(Vec3(0, -100.5, -1), 100, new LambertianMaterial(Vec3(0.8, 0.8, 0.0))));
    world.add(new Sphere(Vec3(1, 0, -1), 0.5, new MetalMaterial(Vec3(0.8, 0.6, 0.2), 0.0)));
    world.add(new Sphere(Vec3(-1, 0, -1), 0.5, new DielectricMaterial(1.5)));

    world.make_random(50);

    Vec3 cameraPosition(0, 10, 10);
    Vec3 cameraTarget(0, 0, -1);
    double dist_to_focus = (cameraTarget - cameraPosition).length();
    Camera camera(cameraPosition, cameraTarget, Vec3(0, 1, 0), 70.0, double(nx) / double(ny), 0, dist_to_focus);

    ThreadPool pool(nt);
    for (int h = 0; h < nh; h++)
    {
        for (int w = 0; w < nw; w++)
        {
            rect_t to_render = {
                (screen.width() / nw) * w,
                (screen.height() / nh) * h,
                screen.width() / nw,
                screen.height() / nh};
            pool.enqueue(render, to_render, ns, &screen, &camera, &world, &rand);
        }
    }

    screen.run();

    return 0;
}