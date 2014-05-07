#ifndef SINGLETON_H
#define SINGLETON_H

#ifdef __linux__
namespace BearClaw {
template<typename T>
class Singleton
{
public:
    typedef T Value;

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton() = delete;
    ~Singleton() = delete;

    static Value& get()
    {
        return *(instance ? instance : (instance = new Value));
    }

private:
    static Value* instance;
};
}
#endif

#endif
