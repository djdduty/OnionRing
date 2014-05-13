#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <System/SDLWindow.h>
#include <System/InputManager.h>
#include <System/EngineTypes.h>
#include <Rendering/OnionRenderer.h>

#define GameEnvironment Environment::GetEnvironment()
#define GameWindow      Environment::GetEnvironment()->GetWindow()
#define InputMgr        Environment::GetEnvironment()->GetInputManager()
#define GameRenderer    Environment::GetEnvironment()->GetRenderer()

#define WindowWidth     Environment::GetEnvironment()->GetWindowWidth()
#define WindowHeight    Environment::GetEnvironment()->GetWindowHeight()

namespace OnionRing {
class Logger;

class Environment
{
private:
    Environment();

protected:
    SDLWindow* m_Window;
    InputManager* m_InputManager;
    OnionRenderer* m_Renderer;

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

    virtual void Init(SDLWindow* Win);
    virtual void Update(double DeltaTime);
    virtual void Render();

    SDLWindow*          GetWindow()         const {return m_Window;         }
    InputManager*       GetInputManager()   const {return m_InputManager;   }
    OnionRenderer*      GetRenderer()       const {return m_Renderer;       }

    int                 GetWindowWidth()    {return m_WindowWidth;          }
    int                 GetWindowHeight()   {return m_WindowHeight;         }
    double              GetDeltaTime()      {return m_DeltaTime;            }
    double              GetElapsedTime()    {return m_ElapsedTime;          }
};
}

#endif
