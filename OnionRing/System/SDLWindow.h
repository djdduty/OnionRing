#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <System/PlatformIncludes.h>
#include <Utils/Math.h>
#include <System/Window.h>
#include <string>
#include <SDL.h>

using namespace std;
namespace OnionRing {
typedef std::function<void(int, int)> KeyFunc;
typedef std::function<void(int, int)> MouseMoveFunc;
typedef std::function<void(int, int)> MouseButtonFunc;

struct WindowInitializer
{
    //stupid non initializer lists support.
    int         Width;//           =   800;
    int         Height;//          =   600;
    int         rgbaBits[4];//     =   {8,8,8,0};
    int         DepthBits;//       =   0;
    int         StencilBits;//     =   0;
    int         SamplesCount;//    =   0;
    bool        FullScreen;//      =   false;
    bool        Resizable;//       =   false;
    bool        Compatibility;//   =   false;
    int         MajorVersion;//    =   3;
    int         MinorVersion;//    =   3;
    const char* Title;//           =   "BearClaw Engine";
};

class SDLWindow
{
private:
    bool                m_CloseRequested;
    WindowInitializer   m_Initializer;
    SDL_Window*         m_Window;
    SDL_Renderer*       m_Renderer;
    SDL_Texture*        m_Texture;

    KeyFunc             m_KeyFunction;
    MouseMoveFunc       m_MouseMoveFunction;
    MouseButtonFunc     m_MouseButtonFunction;

public:
    SDLWindow(WindowInitializer &Initializer);
    ~SDLWindow();
    bool Create();
    void MakeCurrent();
    Vec2 GetWindowSize();
    void SwapBuffers();
    void PollEvents();
    void HandleEvent(SDL_Event* Event);
    void Destroy();
    void OnKeyDown(int key, int action);
    void OnMouseButton(int button, int action);
    void OnMouseMove(int x, int y);

    void SetKeyFunction(KeyFunc f) {
        m_KeyFunction = f;
    }

    void SetMouseMoveFunction(MouseMoveFunc f) {
        m_MouseMoveFunction = f;
    }

    void SetMouseButtonFunction(MouseButtonFunc f) {
        m_MouseButtonFunction = f;
    }

    int GetTimeInMS() {
        SDL_GetTicks();
    }

    int GetWidth() {
        return GetWindowSize().x;
    }

    int GetHeight() {
        return GetWindowSize().y;
    }

    void SetCloseRequested(bool close) {
        m_CloseRequested = close;
    }

    bool GetCloseRequested() {
        return m_CloseRequested;
    }

    SDL_Window* GetWindow() {
        return m_Window;
    }

    SDL_Renderer* GetRenderer() {
        return m_Renderer;
    }

    SDL_Texture* GetTexture() {
        return m_Texture;
    }

    void SetWindowFullscreen(bool f) {
        if(f)
            SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        else
            SDL_SetWindowFullscreen(m_Window, 0);
    }

    void SetWindowSize(Vec2 Size) {
        //SDL_SetWindowSize(m_Window, Size.x, Size.y);
    }

    void SetWindowTitle(const char* title) {
        SDL_SetWindowTitle(m_Window, title);
    }
};
}
#endif
