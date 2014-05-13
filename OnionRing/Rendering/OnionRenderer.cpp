#include <Rendering/OnionRenderer.h>
#include <System/Environment.h>
#include <string.h>

#define TexMultiplier 1.0

namespace OnionRing {
OnionRenderer::OnionRenderer() {}

OnionRenderer::~OnionRenderer() {
    PixelBuffer_Destroy(&m_Buffer);
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyTexture(m_Texture);
}

void OnionRenderer::Init() {
    PixelBuffer_Create(&m_Buffer, 4, GameWindow->GetWidth()*TexMultiplier, GameWindow->GetHeight()*TexMultiplier);

    m_Renderer = SDL_CreateRenderer(GameWindow->GetWindow(), -1, SDL_RENDERER_SOFTWARE);
    m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, GameWindow->GetWidth()*TexMultiplier, GameWindow->GetHeight()*TexMultiplier);

    spheres.push_back(new Sphere(Vec3(0, -10004, -20), 10000, Vec3(0.0, 0.0, 0.5), 0, 0.0));
    spheres.push_back(new Sphere(Vec3(0, 0, -20), 4, Vec3(1.00, 0.32, 0.36), 1, 0.0));
    spheres.push_back(new Sphere(Vec3(-5, -1, -15), 2, Vec3(0.90, 0.76, 0.46), 1, 0.0));
    spheres.push_back(new Sphere(Vec3(5, 0, -25), 3, Vec3(0.65, 0.77, 0.97), 1, 0.0));
}

void OnionRenderer::Render() {
    //memset(m_Buffer.addr, 0x0, m_Buffer.w * m_Buffer.h * m_Buffer.bpp);

    unsigned width = WindowWidth*TexMultiplier, height = WindowHeight*TexMultiplier;
    float invWidth = 1 / float(width);
    float invHeight = 1 / float(height);
    float fov = 60, aspectratio = width / float(height);
    float angle = tan(M_PI * 0.5 * fov / float(180));
    // Trace rays
    Vec3 pixel;
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vec3 raydir(xx, yy, -1);
            raydir.Normalize();
            pixel = TraceRay(Vec3(), raydir, spheres, 0);
            //pixel.Normalize();
            u32* buf = (u32*)m_Buffer.addr;
            buf[x+y*m_Buffer.w] = ((int)(pixel.x*255) << 16) | ((int)(pixel.y*255) << 8) | (int)(pixel.z*255);
        }
    }

    SDL_UpdateTexture(m_Texture, NULL, m_Buffer.addr, m_Buffer.w * m_Buffer.bpp);
    SDL_RenderClear(m_Renderer);
    SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
    SDL_RenderPresent(m_Renderer);
}
}
