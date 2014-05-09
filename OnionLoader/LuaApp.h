#ifndef LUA_APP_H
#define LUA_APP_H

#include <System/Window.h>
#include <Loader.h>

using namespace OnionRing;
namespace OnionRuntime {
class LuaApp
{
private:
    Window* m_Window;
    OnionLoader* m_Loader;

protected:

public:
    LuaApp(WindowInitializer Init, OnionLoader* Loader);
    ~LuaApp();
    void Start();
};
}

#endif

