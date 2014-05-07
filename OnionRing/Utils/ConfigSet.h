#ifndef CONFIG_SET_H

#include <System/Environment.h>
#include <System/BcTypes.h>
#include <Utils/BcString.h>
#include <unordered_map>

namespace BearClaw {
    typedef std::unordered_map<const char*, f64> Settings;

class ConfigSet
{
private:
    std::unordered_map<const char*, f64> m_Settings;
protected:
    void NewSetting(const char* Name, f64 Value)
    {
        m_Settings[Name] = Value;
    }

public:
    f64 Get(const char* Name) const
    {
        Settings::const_iterator it = m_Settings.find(Name);
        if(it != m_Settings.end())
        {
            return it->second;
        }
        else
        {
            BC_LOG("ERROR: Setting not found\n");
            //TODO Exception;
        }
    }

    f64 get(const char* Name)
    {
        Settings::iterator it = m_Settings.find(Name);
        if(it != m_Settings.end())
        {
            return it->second;
        }
        else
        {
            BC_LOG("ERROR: Setting not found\n");
            //TODO Exception;
        }
    }

    void Set(const char* Name, f64 Value)
    {
        Settings::iterator it = m_Settings.find(Name);
        if(it != m_Settings.end())
        {
            it->second = Value;
        }
        else
        {
            BC_LOG("ERROR: Setting not found\n");
            //TODO Exception;
        }
    }
};
}

#endif