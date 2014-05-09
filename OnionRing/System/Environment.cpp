#include <System/Environment.h>

namespace OnionRing {
Environment::Environment() {
    m_ElapsedTime = 0.0;
}

void Environment::Init(Window* Win) {
    m_Log = fopen("DebugOutput.txt", "w");
    m_Window = Win;
    m_WindowHeight = m_Window->GetHeight();
    m_WindowWidth = m_Window->GetWidth();

    //todo Renderer, Resource managers, etc
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

    m_Window->PollEvents();
    //m_InputManager->PollEvents();
}

int Environment::Log(const char* Text, ...)
{
    va_list List;
    va_start(List, Text);
    int Size = strlen(Text) + 512;
    char *Formatted = AllocStr(Size);

    vsnprintf(Formatted, Size, Text, List);
    va_end(List);

    int Ret = fprintf(m_Log, "%s", Formatted);
    printf("%s", Formatted);

    free(Formatted);
    return Ret;
}
}
