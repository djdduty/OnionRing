#include <Loader.h>
#include <iostream>
#include <functional>
#include <System/Environment.h>

using namespace OnionRing;
namespace OnionRuntime {
//Lua function bindings

//misc
static int Quit(lua_State* L) {GameWindow->SetCloseRequested(true); return 1;}

OnionLoader::OnionLoader(lua_State* L, string FileName) {
    m_Lua = L;
    m_FileName = FileName;
}

OnionLoader::~OnionLoader() {
    lua_close(m_Lua);
}

void OnionLoader::Init() {
    //Lua
    if (luaL_loadfile(m_Lua, m_FileName.c_str())) {
        std::cerr << "Something went wrong loading the chunk (syntax error?)\n";
        std::cerr << lua_tostring(m_Lua, -1) << std::endl;
        lua_pop(m_Lua,1);
    }

    lua_newtable(m_Lua);
        lua_pushcfunction(m_Lua, Quit);
        lua_setfield(m_Lua, -2, "quit");
        InputMgr->BindLua(m_Lua);
    lua_setglobal(m_Lua, "onion");

    if (lua_pcall(m_Lua,0, LUA_MULTRET, 0)) {
        std::cerr << "Something went wrong during execution\n";
        std::cerr << lua_tostring(m_Lua, -1) << std::endl;
        lua_pop(m_Lua,1);
    }

    //Input Functions
    using std::placeholders::_1;
    using std::placeholders::_2;
    KeyFunc KeyFunction = std::bind(&OnionLoader::KeyCallback, this, _1, _2);
    MouseMoveFunc MMFunc = std::bind(&OnionLoader::MouseMoveCallback, this, _1, _2);
    MouseButtonFunc MBFunc = std::bind(&OnionLoader::MouseButtonCallback, this, _1, _2);
    InputMgr->AddKeyDownFunction(KeyFunction);
    InputMgr->AddMouseMoveFunction(MMFunc);
    InputMgr->AddMouseButtonFunction(MBFunc);
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

void OnionLoader::KeyCallback(int b, int a) {
    lua_getglobal(m_Lua, "onion");
    if(a == GLFW_PRESS)
        lua_getfield(m_Lua, -1, "keydown");
    if(a == GLFW_RELEASE)
        lua_getfield(m_Lua, -1, "keyup");
    lua_pushnumber(m_Lua, b);
    lua_pcall(m_Lua, 1, 0, 0);
    lua_pop(m_Lua,1);
}

void OnionLoader::MouseMoveCallback(double x, double y) {
    lua_getglobal(m_Lua, "onion");
    lua_getfield(m_Lua, -1, "mousemove");
    lua_pushnumber(m_Lua, x);
    lua_pushnumber(m_Lua, y);
    lua_pcall(m_Lua, 2, 0, 0);
    lua_pop(m_Lua,1);
}

void OnionLoader::MouseButtonCallback(int b, int a) {
    lua_getglobal(m_Lua, "onion");
    if(a == GLFW_PRESS)
        lua_getfield(m_Lua, -1, "mousedown");
    if(a == GLFW_RELEASE)
        lua_getfield(m_Lua, -1, "mouseup");
    lua_pushnumber(m_Lua, b);
    lua_pcall(m_Lua, 1, 0, 0);
    lua_pop(m_Lua,1);
}
}
