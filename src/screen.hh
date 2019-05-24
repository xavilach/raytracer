#ifndef SCREEN_HH_
#define SCREEN_HH_

#include "vec3.hh"
#include "SDL2/SDL.h"

#include <string>
#include <mutex>

namespace Raytracer
{
class Screen
{
public:
    Screen(std::string title, int width, int height);
    ~Screen();

    bool init();
    void update();
    void run();

    int width() const;
    int height() const;

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

#endif /*SCREEN_HH_*/
