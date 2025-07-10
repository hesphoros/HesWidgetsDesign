#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

//禁用拷贝构造函数和拷贝赋值操作符
#define HES_DISABLE_COPY_CONSTRUCTORS_AND_ASSIGNMENTS(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete; 

//禁用移动构造函数和移动赋值操作符
#define HES_DISABLE_MOVE_CONSTRUCTORS_AND_ASSIGNMENTS(ClassName) \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete;

#define HES_PRIVATE_CONSTRUCTOR_AND_DESTRUCTOR(ClassName) \
    private: \
    ClassName() = default;  /* 私有构造函数，防止外部实例化 */ \
    ~ClassName() = default; /* 私有析构函数，防止外部删除 */ \




#endif // COMMON_UTILS_H