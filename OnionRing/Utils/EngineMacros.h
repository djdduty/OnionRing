#ifndef ENGINE_MACROS_H
#define ENGINE_MACROS_H

#ifdef __APPLE__
#define AllocArray(Type,Size) (Type *)__alloca(Size * sizeof(Type))
#else
#define AllocArray(Type,Size) (Type *)malloc(Size * sizeof(Type))
#endif

#ifdef __linux__
#define GetPos      GetPosition().__pos
#else
#define GetPos      GetPosition()
#endif

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define BC_LOG          Environment::GetEnvironment()->Log
#define BC_ERROR(...)   {Environment::GetEnvironment()->Log(__VA_ARGS__); abort(); }

#define Environ         Environment::GetEnvironment()
#define GameWindow      Environment::GetEnvironment()->GetWindow()
#define RenderSingleton Environment::GetEnvironment()->GetRenderer()
#define FileSys         Environment::GetEnvironment()->GetFileSystem()
#define InputMgr        Environment::GetEnvironment()->GetInputManager()
#define ShaderMgr       Environment::GetEnvironment()->GetShaderManager()
#define TextureMgr      Environment::GetEnvironment()->GetTextureManager()

#define WindowWidth     Environment::GetEnvironment()->GetWindowWidth()
#define WindowHeight    Environment::GetEnvironment()->GetWindowHeight()
#endif
