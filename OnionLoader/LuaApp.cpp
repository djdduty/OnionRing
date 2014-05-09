#include <LuaApp.h>

namespace OnionRuntime {
LuaApp::LuaApp(WindowInitializer Init, OnionLoader* Loader) {
    m_Window = new Window(Init);
    m_Loader = Loader;
}

LuaApp::~LuaApp() {
    delete m_Window;
}

void LuaApp::Start() {
    m_Window->Create();
    m_Window->MakeCurrent();

    double DeltaTime = 0;
    double OldTime = m_Window->GetTimeInMS();

    while(!m_Window->GetCloseRequested() && m_Loader->KeepRunning) {
        DeltaTime = m_Window->GetTimeInMS() - OldTime;
        OldTime = m_Window->GetTimeInMS();

        m_Window->PollEvents();

        m_Loader->Update(DeltaTime);
        m_Loader->Draw();

        m_Window->SwapBuffers();
    }

    m_Window->Destroy();
}
}
