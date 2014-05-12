#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <System/PlatformIncludes.h>
#include <System/SDLWindow.h>
#include <Utils/Math.h>
#include <vector>
#include <map>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace OnionRing {
typedef std::vector<KeyFunc> KeyFuncList;
typedef std::vector<MouseMoveFunc> MouseMoveFuncList;
typedef std::vector<MouseButtonFunc> MouseButtonFuncList;

class InputManager
{
private:
    KeyFuncList             m_KeyFunctions;
    MouseMoveFuncList       m_MouseMoveFunctions;
    MouseButtonFuncList     m_MouseButtonFunctions;

    SDLWindow*                 m_GameWindow;
    bool                    m_bShowCursor;
protected:

public:
    Vec2                    MousePosition;

    InputManager() {}
    ~InputManager() {}

    int GetKey(int i) const
    {
        return 0;//TODO: New version, return glfwGetKey(m_GameWindow->GetWindow(), i);
    }

    int GetMouseButton(int i) const
    {
        return 0;//TODO: New version, return glfwGetMouseButton(m_GameWindow->GetWindow(), i);
    }

    const int GetMouseX() const
    {
        return MousePosition.x;
    }

    const int GetMouseY() const
    {
        return MousePosition.y;
    }

    void Init();
    void BindLua(lua_State* L);

    void PollEvents() {m_GameWindow->PollEvents();}
    void SetMousePosition(const Vec2& Pos) {
        if(Pos.x != MousePosition.x && Pos.y != MousePosition.y)
            SDL_WarpMouseInWindow(m_GameWindow->GetWindow(), Pos.x, Pos.y);
    }

    void HideCursor(bool Hide) {
        if(Hide)
            SDL_ShowCursor(0);
        else
            SDL_ShowCursor(1);
    }

    //Functions
    void AddKeyDownFunction(KeyFunc KF) { m_KeyFunctions.push_back(KF); }
    void AddMouseMoveFunction(MouseMoveFunc MMF) { m_MouseMoveFunctions.push_back(MMF); }
    void AddMouseButtonFunction(MouseButtonFunc MBF) { m_MouseButtonFunctions.push_back(MBF); }

    void RemoveKeyDownFunctions();
    void RemoveMouseMoveFunctions();
    void RemoveMouseButtconFunctions();

    //lower level calls, calls the cbs and funcs
    void OnMouseMove(int x, int y);
    void OnKeyDown(char Key, int Action);
    void OnMouseButton(int Button, int Action);

    void ClearFunctions()
    {
        m_KeyFunctions.clear();
        m_MouseMoveFunctions.clear();
        m_MouseButtonFunctions.clear();
    }
};
}

#endif
