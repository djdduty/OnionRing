#ifndef WINDOW_H
#define WINDOW_H

#include <System/PlatformIncludes.h>
#include <Utils/Math.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace std;
namespace OnionRing {
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

class Window
{
private:
    bool                m_CloseRequested;
    GLFWwindow*         m_Window;
    WindowInitializer   m_Initializer;

public:
    Window(WindowInitializer &Initializer);
    ~Window();
    void Create();
    void MakeCurrent();
    Vec2 GetWindowSize();
    void SwapBuffers();
    void PollEvents();
    void Destroy();

    double GetTimeInMS() {
        return glfwGetTime()*1000.0;
    }

    double GetTimeInSeconds() {
        return glfwGetTime();
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
        if(glfwWindowShouldClose(m_Window))
            return true;
        return m_CloseRequested;
    }

    GLFWwindow* GetWindow() {
        return m_Window;
    }

    void SetWindowSize(Vec2 Size) {
        glfwSetWindowSize(m_Window, Size.x, Size.y);
    }

    void SetWindowTitle(const char* title) {
        glfwSetWindowTitle(m_Window, title);
    }
};
}
#endif
