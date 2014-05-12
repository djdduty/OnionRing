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

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i],"-h") == 0 || strcmp(argv[i],"--help") == 0) {
            printf("OnionLoader - Onion Engine loader for lua games\n");
            printf("Copyright (c) 2014 -- Jordan Duty\n\n");
            printf("Usage:\n");
            printf("  OnionLoader option\n");
            printf("  OnionLoader [options] ZipFile.ext\n");
            printf("  OnionLoader [options] MainLuaFile.lua\n\n");
            printf("-v  --version               Shows the version\n");
            printf("-h  --help                  Shows this help\n");
        }
        else if(strcmp(argv[i],"-v") == 0 || strcmp(argv[i],"--version") == 0) {
            printf("OnionEngine - Version 0.1\n");
            printf("OnionLoader - Version 0.2\n");
        }
    {
            OnionLoader* Loader = new OnionLoader(L, argv[1]);//argv[1]
            lua_State* LConf = luaL_newstate();
            luaL_openlibs(LConf);
            bool ConfGood = true;

            if (luaL_loadfile(LConf, "conf.lua")) {
                std::cerr << lua_tostring(LConf, -1) << std::endl;
                lua_pop(LConf,1);
                ConfGood = false;
            }

            if(ConfGood) {
                if (lua_pcall(LConf,0, LUA_MULTRET, 0)) {
                    std::cerr << lua_tostring(LConf, -1) << std::endl;
                    lua_pop(LConf,1);
                    ConfGood = false;
                }
            }

            if(ConfGood) {
                lua_getglobal(LConf, "fullscreen");
                if(!lua_isnil(LConf, -1))
                    WinInit.FullScreen = lua_toboolean(LConf,-1);
                lua_pop(LConf,1);

                lua_getglobal(LConf, "resizable");
                if(!lua_isnil(LConf, -1))
                    WinInit.Resizable = lua_toboolean(LConf,-1);
                lua_pop(LConf,1);

                lua_getglobal(LConf, "windowwidth");
                if(!lua_isnil(LConf, -1))
                    WinInit.Width = lua_tonumber(LConf,-1);
                lua_pop(LConf,1);

                lua_getglobal(LConf, "windowheight");
                if(!lua_isnil(LConf, -1))
                    WinInit.Height = lua_tonumber(LConf,-1);
                lua_pop(LConf,1);
            }

            LuaApp* App = new LuaApp(WinInit, Loader);
            App->Start();

            delete(Loader);
            delete(App);

            exit(0);
        }
    }
    printf("Usage is \"OnionLoader FileName\", where FileName is the main lua file or zip archive. Use -h for more help.\n");

    for(int x = 0; x < WinInit.Width; x++) {
        for(int y = 0; y < WinInit.Height; y++) {

        }
    }
}
