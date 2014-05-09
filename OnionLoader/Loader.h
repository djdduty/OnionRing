#ifndef LOADER_H
#define LOADER_H

#include <string>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace std;
namespace OnionRuntime {
class OnionLoader
{
public:

private:
    lua_State* m_Lua;
    string m_FileName;

protected:

public:
    OnionLoader(lua_State* L, string FileName);
    ~OnionLoader();
    void Init();
    void Load();
    void Draw();
    void Update(double DeltaTime);
    void UnLoad();

    void KeyCallback(int b, int a);
    void MouseMoveCallback(double x, double y);
    void MouseButtonCallback(int b, int a);

};
}

#endif
