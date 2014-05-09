#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <System/Window.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>

#define AllocArray(Type,Size) (Type *)malloc(Size * sizeof(Type))
#define AllocStr(Sz) AllocArray(char,Sz)

#define OR_LOG          Environment::GetEnvironment()->Log
#define OR_ERROR(...)   {Environment::GetEnvironment()->Log(__VA_ARGS__); abort(); }

#define GameEnvironment Environment::GetEnvironment()
#define GameWindow      Environment::GetEnvironment()->GetWindow()

#define WindowWidth     Environment::GetEnvironment()->GetWindowWidth()
#define WindowHeight    Environment::GetEnvironment()->GetWindowHeight()

namespace OnionRing {
class Logger;

class Environment
{
private:
    Environment();

protected:
    Window* m_Window;
    FILE*   m_Log;

    float   m_ElapsedTime;
    float   m_DeltaTime;
    int     m_WindowWidth,
            m_WindowHeight;

public:
    ~Environment();

    static Environment* GetEnvironment()
    {
        static Environment* Env = new Environment();
        return Env;
    }

    virtual void Init(Window* Win);
    virtual void Update(double DeltaTime);

    int  Log(const char* Text, ...);

    Window*             GetWindow()         const {return m_Window;         }

    int                 GetWindowWidth()    {return m_WindowWidth;          }
    int                 GetWindowHeight()   {return m_WindowHeight;         }
    double              GetDeltaTime()      {return m_DeltaTime;            }
    double              GetElapsedTime()    {return m_ElapsedTime;          }
};
}

#endif
