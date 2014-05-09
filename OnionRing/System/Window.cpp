#include <System/Window.h>

namespace OnionRing {
Window::Window(WindowInitializer &Initializer)
{
    m_CloseRequested = false;
    m_Initializer = Initializer;
}

Window::~Window()
{}

void Window::Create()
{
    //I can has glfw?
    if(!glfwInit())
    {
        glfwTerminate();
        printf("Glfw could not initialize!\n");
    }
    //Gl context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_Initializer.MajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_Initializer.MinorVersion);

    if(m_Initializer.Compatibility)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    //Set bits
    glfwWindowHint(GLFW_RED_BITS,       m_Initializer.rgbaBits[0]);
    glfwWindowHint(GLFW_GREEN_BITS,     m_Initializer.rgbaBits[1]);
    glfwWindowHint(GLFW_BLUE_BITS,      m_Initializer.rgbaBits[2]);
    glfwWindowHint(GLFW_ALPHA_BITS,     m_Initializer.rgbaBits[3]);
    glfwWindowHint(GLFW_DEPTH_BITS,     m_Initializer.DepthBits);
    glfwWindowHint(GLFW_STENCIL_BITS,   m_Initializer.StencilBits);

    //Samples
    glfwWindowHint(GLFW_SAMPLES,        m_Initializer.SamplesCount);

    //Resizable?
    glfwWindowHint(GLFW_RESIZABLE,      m_Initializer.Resizable);

    //FullScreen?
    if(!m_Initializer.FullScreen)
        m_Window = glfwCreateWindow(m_Initializer.Width, m_Initializer.Height, m_Initializer.Title, NULL, NULL);
    else
        m_Window = glfwCreateWindow(m_Initializer.Width, m_Initializer.Height, m_Initializer.Title, glfwGetPrimaryMonitor(), NULL);

    //All is good?
    if(!m_Window)
    {
        glfwTerminate();
        printf("Creating the glfw window failed, you most likely lack OpenGL %d.%d support!\n", m_Initializer.MajorVersion, m_Initializer.MinorVersion);
    }

    // GLEW
    MakeCurrent();
    if(!m_Initializer.Compatibility)
        glewExperimental = GL_TRUE;

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        printf("Glew initialization failed: %s\n", glewGetErrorString(err));
    }
    glGetError();
}

void Window::Destroy()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

Vec2 Window::GetWindowSize()
{
    int width, height;
    glfwGetWindowSize(m_Window, &width, &height);
    return Vec2(width, height);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void Window::MakeCurrent()
{
    glfwMakeContextCurrent(m_Window);
}
}
