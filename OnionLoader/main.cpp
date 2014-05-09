#include <Loader.h>
#include <LuaApp.h>
#include <System/Window.h>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace std;
using namespace OnionRing;
using namespace OnionRuntime;

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    OnionLoader* Loader = new OnionLoader(L);
    Loader->Load();

    WindowInitializer WinInit;
    WinInit.Width           =   1280;
    WinInit.Height          =   720;
    WinInit.rgbaBits[0]     =   8;
    WinInit.rgbaBits[1]     =   8;
    WinInit.rgbaBits[2]     =   8;
    WinInit.rgbaBits[3]     =   0;
    WinInit.DepthBits       =   0;
    WinInit.StencilBits     =   0;
    WinInit.SamplesCount    =   0;
    WinInit.FullScreen      =   false;
    WinInit.Resizable       =   true;
    WinInit.Compatibility   =   false;
    WinInit.MajorVersion    =   3;
    WinInit.MinorVersion    =   0;
    WinInit.Title           =   "OnionLoader";

    LuaApp* App = new LuaApp(WinInit, Loader);
    App->Start();

    Loader->UnLoad();
    delete(Loader);
    delete(App);
}
