#include "screen.hh"

#include <iostream>

Raytracer::Screen::Screen(std::string title, int width, int height)
    : m_title(title), m_width(width), m_height(height)
{
}

Raytracer::Screen::~Screen()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Raytracer::Screen::init()
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init failed." << std::endl;
        return false;
    }

    m_window = SDL_CreateWindow(
        m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);
    if (!m_window)
    {
        std::cerr << "SDL_CreateWindow failed." << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
    if (!m_renderer)
    {
        std::cerr << "SDL_CreateRenderer failed." << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    return true;
}

void Raytracer::Screen::update()
{
    if (m_renderer)
    {
        SDL_RenderPresent(m_renderer);
    }
}

void Raytracer::Screen::run()
{
    bool quit = false;

    while (!quit)
    {
        unsigned int time_start = SDL_GetTicks();

        if (m_renderer)
        {
            SDL_RenderPresent(m_renderer);
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    quit = true;
                    break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        unsigned int delta = SDL_GetTicks() - time_start;

        const unsigned int frameTime = (int)(1000.0 / 60.0);
        if (delta < frameTime)
        {
            SDL_Delay(frameTime - delta);
        }
    }
}

int Raytracer::Screen::width() const
{
    return m_width;
}

int Raytracer::Screen::height() const
{
    return m_height;
}

void Raytracer::Screen::setPixel(int x, int y, const Vec3 &color)
{
    m_lock.lock();
    if (m_renderer)
    {
        SDL_SetRenderDrawColor(m_renderer, (Uint8)color.x(), (Uint8)color.y(), (Uint8)color.z(), 255);
        SDL_RenderDrawPoint(m_renderer, x, y);
    }
    m_lock.unlock();
}
