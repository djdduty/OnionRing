#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <System/Window.h>
#include <System/InputManager.h>

#define GameEnvironment Environment::GetEnvironment()
#define GameWindow      Environment::GetEnvironment()->GetWindow()
#define InputMgr        Environment::GetEnvironment()->GetInputManager()

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
    InputManager* m_InputManager;

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

    Window*             GetWindow()         const {return m_Window;         }
    InputManager*       GetInputManager()   const {return m_InputManager;   }

    int                 GetWindowWidth()    {return m_WindowWidth;          }
    int                 GetWindowHeight()   {return m_WindowHeight;         }
    double              GetDeltaTime()      {return m_DeltaTime;            }
    double              GetElapsedTime()    {return m_ElapsedTime;          }
};
}

#endif
