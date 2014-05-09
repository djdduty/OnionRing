#include <System/Environment.h>

namespace OnionRing {
Environment::Environment() : m_InputManager(new InputManager()) {
    m_ElapsedTime = 0.0;
}

void Environment::Init(Window* Win) {
    //m_Log = fopen("DebugOutput.txt", "w");
    m_Window = Win;
    m_WindowHeight = m_Window->GetHeight();
    m_WindowWidth = m_Window->GetWidth();

    //todo Renderer, Resource managers, etc
    m_InputManager->Init();
}

void Environment::Update(double DeltaTime) {
    m_DeltaTime = DeltaTime;
    m_ElapsedTime += DeltaTime;
     if(m_WindowWidth != m_Window->GetWidth() || m_WindowHeight != m_Window->GetHeight())
    {
        m_WindowWidth = m_Window->GetWidth();
        m_WindowHeight = m_Window->GetHeight();
        glViewport(0,0,m_WindowWidth, m_WindowHeight);
    }

    m_InputManager->PollEvents();
    //m_InputManager->PollEvents();
}
}
