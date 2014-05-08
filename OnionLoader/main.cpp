#include <Loader.h>

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace std;
using namespace OnionRuntime;

int main() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	OnionLoader* Loader = new OnionLoader(L);
	Loader->Load();
  
	while(Loader->KeepRunning) {
		Loader->Update(1);
		Loader->Draw();
	}
	
	Loader->UnLoad();
	delete(Loader);
}
