#include <System/Environment.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace OnionRing {
Environment::Environment() : m_InputManager(new InputManager()) {
    m_ElapsedTime = 0.0;
}

Environment::~Environment() {
    PixelBuffer_Destroy(&buffer);
}

void Environment::Init(SDLWindow* Win) {
    //m_Log = fopen("DebugOutput.txt", "w");
    m_Window = Win;
    m_WindowHeight = m_Window->GetHeight();
    m_WindowWidth = m_Window->GetWidth();

    //todo Renderer, Resource managers, etc
    m_InputManager->Init();

    PixelBuffer_Create(&buffer, 4, m_Window->GetWidth(), m_Window->GetHeight());
}

void Environment::Update(double DeltaTime) {
    m_DeltaTime = DeltaTime;
    m_ElapsedTime += DeltaTime;
     if(m_WindowWidth != m_Window->GetWidth() || m_WindowHeight != m_Window->GetHeight())
    {
        m_WindowWidth = m_Window->GetWidth();
        m_WindowHeight = m_Window->GetHeight();
    }

    m_InputManager->PollEvents();
}

void Environment::Render() {
    memset(buffer.addr, 0x0, buffer.w * buffer.h * buffer.bpp);

    for(int y = 0; y < buffer.h; y++) {
        for(int x = 0; x < buffer.w; x++) {
            byte red = (x^y)&0xFF;
            byte green = 0;
            byte blue = 0;
            u32* buf = (u32*)buffer.addr;
            buf[x+y*buffer.w] = (red << 16) | (green << 8) | blue;
        }
    }

    SDL_UpdateTexture(m_Window->GetTexture(), NULL, buffer.addr, buffer.w * buffer.bpp);
    SDL_RenderClear(m_Window->GetRenderer());
    SDL_RenderCopy(m_Window->GetRenderer(), m_Window->GetTexture(), NULL, NULL);
    SDL_RenderPresent(m_Window->GetRenderer());
}
}
