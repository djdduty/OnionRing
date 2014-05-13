#ifndef ONIONRENDERER_H
#define ONIONRENDERER_H

#include <Rendering/PixelBuffer.h>
#include <System/EngineTypes.h>
#include <System/SDLWindow.h>
#include <Rendering/Raytracer.h>

namespace OnionRing {
class OnionRenderer
{
private:
    PixelBuffer_t   m_Buffer;
    SDL_Texture*    m_Texture;
    SDL_Renderer*   m_Renderer;

    std::vector<Sphere*> spheres;

protected:

public:
    OnionRenderer();
    ~OnionRenderer();

    void Init();
    void Render();

    SDL_Renderer* GetRenderer() {
        return m_Renderer;
    }

    SDL_Texture* GetTexture() {
        return m_Texture;
    }
};
}

#endif // ONIONRENDERER_H
