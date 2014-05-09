#include <Loader.h>
#include <iostream>
#include <System/Environment.h>

using namespace OnionRing;
namespace OnionRuntime {
OnionLoader* LoadInstance;

//Lua function bindings
static int Quit(lua_State* L) {GameWindow->SetCloseRequested(true);}

OnionLoader::OnionLoader(lua_State* L) {
    m_Lua = L;

    if (luaL_loadfile(m_Lua, "main.lua")) {
        std::cerr << "Something went wrong loading the chunk (syntax error?)\n";
        std::cerr << lua_tostring(m_Lua, -1) << std::endl;
        lua_pop(m_Lua,1);
    }

    lua_newtable(m_Lua);
    int top = lua_gettop(m_Lua);
    lua_pushliteral(L, "quit");
    lua_pushcfunction(L, Quit);
    lua_settable(L, top);
    lua_setglobal(m_Lua, "onion");

    if (lua_pcall(m_Lua,0, LUA_MULTRET, 0)) {
        std::cerr << "Something went wrong during execution\n";
        std::cerr << lua_tostring(m_Lua, -1) << std::endl;
        lua_pop(m_Lua,1);
    }

    KeepRunning = true;
    LoadInstance = this;
}

OnionLoader::~OnionLoader() {
    lua_close(m_Lua);
}

void OnionLoader::Load() {
    lua_getglobal(m_Lua, "onion");
    lua_getfield(m_Lua, -1, "load");
    lua_pcall(m_Lua, 0, 0, 0);
    lua_pop(m_Lua,1);
}

void OnionLoader::Draw() {
    lua_getglobal(m_Lua, "onion");
    lua_getfield(m_Lua, -1, "draw");
    lua_pcall(m_Lua, 0, 0, 0);
    lua_pop(m_Lua,1);
}

void OnionLoader::Update(double DeltaTime) {
    lua_getglobal(m_Lua, "onion");
    lua_getfield(m_Lua, -1, "update");
    lua_pushnumber(m_Lua, DeltaTime);
    lua_pcall(m_Lua, 1, 0, 0);
    lua_pop(m_Lua,1);
}

void OnionLoader::UnLoad() {
    lua_getglobal(m_Lua, "onion");
    lua_getfield(m_Lua, -1, "unload");
    lua_pcall(m_Lua, 0, 0, 0);
    lua_pop(m_Lua,1);
}
}
