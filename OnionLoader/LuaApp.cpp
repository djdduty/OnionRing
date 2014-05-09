#include <LuaApp.h>
#include <System/Environment.h>

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
    GameEnvironment->Init(m_Window);
    m_Loader->Init();
    m_Loader->Load();
    while(!m_Window->GetCloseRequested()) {
        DeltaTime = m_Window->GetTimeInMS() - OldTime;
        OldTime = m_Window->GetTimeInMS();

        GameEnvironment->Update(DeltaTime);

        m_Loader->Update(DeltaTime);
        m_Loader->Draw();

        m_Window->SwapBuffers();
    }
    m_Loader->UnLoad();
    m_Window->Destroy();
}
}
