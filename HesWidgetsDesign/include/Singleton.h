#ifndef HESSINGLETON_H
#define HESSINGLETON_H

#include <mutex>
#include <memory>
#include "common/common_utils.h"

template <typename T>
class Singleton
{
public:
    // 获取单例实例的静态方法
    static T* getInstance();  // 返回指针

private:

    // HES_PRIVATE_CONSTRUCTOR_AND_DESTRUCTOR(Singleton)
    //HES_DISABLE_COPY_CONSTRUCTORS_AND_ASSIGNMENTS(Singleton)
    //HES_DISABLE_MOVE_CONSTRUCTORS_AND_ASSIGNMENTS(Singleton)
    Q_DISABLE_COPY(Singleton)
    static std::once_flag      initialized;
	static T* instance; 
    
};


template <typename T>
std::once_flag Singleton<T>::initialized;

template <typename T>
T* Singleton<T>::instance = nullptr;



template <typename T>
T* Singleton<T>::getInstance()
{
    std::call_once(initialized, []() {
        instance = new T(); 
    });

    return instance;
}


#define HES_SINGLETON_CREATE(Class)                     \
private:                                                \
    friend class Singleton<Class>;                      \
                                                        \
public:                                                 \
    static Class* getInstance()                         \
    {                                                   \
        return Singleton<Class>::getInstance();         \
    }


// singleton类的创建宏
// 这个宏用于在类定义中声明单例模式        
#define HES_SINGLETON_CREATE_H(Class)                   \
private:                                                \
    static Class* _instance;                            \
                                                        \
public:                                                 \
    static Class* getInstance();


#define HES_SINGLETON_CREATE_CPP(Class)                 \
    Class* Class::_instance = nullptr;                  \
    Class* Class::getInstance()                         \
    {                                                   \
        static std::mutex mtx;                          \
        std::lock_guard<std::mutex> locker(mtx);        \
        if (_instance == nullptr)                       \
        {                                               \
            _instance = new Class();                    \
        }                                               \
        return _instance;                               \
    }



#endif // !HESSINGLETON_H