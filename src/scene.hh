#ifndef SCENE_HH_
#define SCENE_HH_

#include "vec3.hh"
#include "SDL2/SDL.h"

#include <string>
#include <mutex>

namespace Raytracer
{
class Scene
{
public:
    Scene(std::string title, int width, int height);
    ~Scene();

    bool init();
    void update();
    void run();

    void setPixel(int x, int y, const Vec3 &color);

private:
    std::string m_title;
    int m_width;
    int m_height;
    std::mutex m_lock;

    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
};
} // namespace Raytracer

#endif /*SCENE_HH_*/
