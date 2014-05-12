#include <System/SDLWindow.h>

namespace OnionRing {
SDLWindow::SDLWindow(WindowInitializer &Initializer) {
    m_CloseRequested = false;
    m_Initializer = Initializer;
    m_Window = NULL;
}

SDLWindow::~SDLWindow() {}

bool SDLWindow::Create() {
    if(m_Initializer.FullScreen)
        m_Window = SDL_CreateWindow(m_Initializer.Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Initializer.Width, m_Initializer.Height, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else
        m_Window = SDL_CreateWindow(m_Initializer.Title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Initializer.Width, m_Initializer.Height, 0);

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_SOFTWARE);
    m_Texture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_STREAMING, m_Initializer.Width, m_Initializer.Height);

    if(m_Window == NULL)
    {
        printf("Could not create SDL window: %s\n", SDL_GetError());
        return false;
    }
}

void SDLWindow::Destroy() {
    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyTexture(m_Texture);
}

Vec2 SDLWindow::GetWindowSize() {
    int width, height;

    return Vec2(width, height);
}

void SDLWindow::PollEvents() {
    SDL_Event Event;
    while(SDL_PollEvent(&Event))
    {
        HandleEvent(&Event);
    }
}

void SDLWindow::HandleEvent(SDL_Event* Event) {
    switch(Event->type) {
    case SDL_KEYUP:
        OnKeyDown(Event->key.keysym.sym, SDL_KEYUP);
        break;
    case SDL_KEYDOWN:
        OnKeyDown(Event->key.keysym.sym, SDL_KEYDOWN);
        break;
    case SDL_MOUSEMOTION:
        OnMouseMove(Event->motion.x, Event->motion.y);
        break;
    case SDL_MOUSEBUTTONDOWN:
        OnMouseButton(Event->button.button, Event->type);
        break;
    case SDL_MOUSEBUTTONUP:
        OnMouseButton(Event->button.button, Event->type);
        break;
    case SDL_QUIT:
            m_CloseRequested = true;
            break;
        default:
            break;
    }
}

void SDLWindow::OnKeyDown(int key, int action) {
    m_KeyFunction(key, action);
}

void SDLWindow::OnMouseButton(int button, int action) {
   m_MouseButtonFunction(button, action);
}

void SDLWindow::OnMouseMove(int x, int y) {
    m_MouseMoveFunction(x, y);
}

void SDLWindow::SwapBuffers() {

}

void SDLWindow::MakeCurrent() {

}
}
