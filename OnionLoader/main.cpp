#include <Loader.h>
#include <LuaApp.h>
#include <System/Window.h>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace std;
using namespace OnionRing;
using namespace OnionRuntime;

int main(int argc, char* argv[]) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if(argc == 2 && argc < 3) {
        OnionLoader* Loader = new OnionLoader(L, argv[1]);

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

        delete(Loader);
        delete(App);
    }
    else {
        //Todo: Explain the usage of the program
    }
}
