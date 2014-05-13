#include <System/Environment.h>

namespace OnionRing {
Environment::Environment() : m_InputManager(new InputManager()), m_Renderer(new OnionRenderer()) {
    m_ElapsedTime = 0.0;
}

Environment::~Environment() {
    delete(m_InputManager);
    delete(m_Renderer);
}

void Environment::Init(SDLWindow* Win) {
    m_Window = Win;
    m_WindowHeight = m_Window->GetHeight();
    m_WindowWidth = m_Window->GetWidth();

    //todo Renderer, Resource managers, etc
    m_InputManager->Init();
    m_Renderer->Init();
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
    m_Renderer->Render();
}
}
