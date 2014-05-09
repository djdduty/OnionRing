#include <System/InputManager.h>
#include <System/Environment.h>

namespace OnionRing {
//For lua
static int IsKeyDown(lua_State* L) {
    bool ret = false;
    int arg = luaL_checknumber(L,1);
    if(InputMgr->GetKey(arg) == GLFW_PRESS)
        ret = true;
    lua_pushboolean(L, ret);
    return 1;
}

static int IsMouseButtonDown(lua_State* L) {
    bool ret = false;
    int arg = luaL_checknumber(L,1);
    if(InputMgr->GetMouseButton(arg) == GLFW_PRESS)
        ret = true;
    lua_pushboolean(L, ret);
    return 1;
}

static int GetMX(lua_State* L) {lua_pushnumber(L, InputMgr->GetMouseX());return 1;}
static int GetMY(lua_State* L) {lua_pushnumber(L, InputMgr->GetMouseY());return 1;}
static int HideMouse(lua_State* L) {InputMgr->HideCursor(true);return 1;}
static int ShowMouse(lua_State* L) {InputMgr->HideCursor(false);return 1;}

//--------

void KeyCallback(GLFWwindow* Window, int key, int scancode, int action, int mods)
{
        InputMgr->OnKeyDown(key, action);
}

void MouseMoveCallback(GLFWwindow* Window, double x, double y)
{
    InputMgr->MousePosition = Vec2(x, y);
    InputMgr->OnMouseMove(x,y);
}

void MouseButtonCallback(GLFWwindow* Window, int Button, int Action, int mods)
{
    InputMgr->OnMouseButton(Button, Action);
}

void InputManager::Init() {
    m_GameWindow = GameWindow;
    m_bShowCursor = true;
    glfwSetKeyCallback(m_GameWindow->GetWindow(), KeyCallback);
    glfwSetCursorPosCallback(m_GameWindow->GetWindow(), MouseMoveCallback);
    glfwSetMouseButtonCallback(m_GameWindow->GetWindow(), MouseButtonCallback);
}

void InputManager::BindLua(lua_State* L) {
    lua_newtable(L);
        lua_pushcfunction(L, IsKeyDown);
        lua_setfield(L, -2, "iskeydown");
    lua_setfield(L, -2, "input");
    lua_newtable(L);
        lua_pushcfunction(L, IsMouseButtonDown);
        lua_setfield(L, -2, "isdown");
        lua_pushcfunction(L, GetMX);
        lua_setfield(L, -2, "getX");
        lua_pushcfunction(L, GetMY);
        lua_setfield(L, -2, "getY");
        lua_pushcfunction(L, HideMouse);
        lua_setfield(L, -2, "hide");
        lua_pushcfunction(L, ShowMouse);
        lua_setfield(L, -2, "show");
    lua_setfield(L, -2, "mouse");
}

void InputManager::RemoveKeyDownFunctions()
{
    for (int i = 0; i < m_KeyFunctions.size(); i++)
    {
            m_KeyFunctions.erase(m_KeyFunctions.begin() + i);

    }
}


void InputManager::RemoveMouseMoveFunctions() {
    for (int i = 0; i < m_MouseMoveFunctions.size(); i++)
    {
        m_MouseMoveFunctions.erase(m_MouseMoveFunctions.begin() + i);

    }
}

void InputManager::RemoveMouseButtconFunctions() {
    for (int i = 0; i < m_MouseButtonFunctions.size(); i++)
    {
        m_MouseButtonFunctions.erase(m_MouseButtonFunctions.begin() + i);

    }
}

void InputManager::OnKeyDown(char Key, int Action)
{
    for (int n = 0; n < m_KeyFunctions.size(); n++)
    {
        m_KeyFunctions[n](Key, Action);
    }
}

void InputManager::OnMouseMove(double x, double y)
{
    MousePosition.x = x; MousePosition.y = y;
    for (int n = 0; n < m_MouseMoveFunctions.size(); n++)
    {
        m_MouseMoveFunctions[n](x, y);
    }
}

void InputManager::OnMouseButton(int Button, int Action)
{
    for (int n = 0; n < m_MouseButtonFunctions.size(); n++)
    {
        m_MouseButtonFunctions[n](Button, Action);
    }
}
}

