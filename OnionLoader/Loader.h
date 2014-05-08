#ifndef LOADER_H
#define LOADER_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace OnionRuntime {
class OnionLoader
{
public:
    bool KeepRunning;

private:
    lua_State* m_Lua;

protected:

public:
    OnionLoader(lua_State* L);
    ~OnionLoader();
    void Load();
    void Draw();
    void Update(double DeltaTime);
    void UnLoad();
};
}

#endif
