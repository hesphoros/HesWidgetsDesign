#ifndef STDAFX_H
#define STDAFX_H

#include <QtCore/qglobal.h>

// 定义导出宏
// 如果在编译库时定义了 HESWIDGETSDESIGN_LIBRARY，则导出符号 否则导入符号。
#ifndef HESWIDGETSDESIGN_LIBRARY
#define HES_EXPORT Q_DECL_EXPORT
#else
#define HES_EXPORT Q_DECL_IMPORT
#endif


// 枚举类导出 兼容 QT5 低版本
/**
 * @brief 如果Qt版本大于等于5.14.0，
 */
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#define Q_ENUM_BEGIN(CLASS) \
    namespace CLASS { \
    Q_NAMESPACE_EXPORT(HES_EXPORT)

#define Q_ENUM_END(CLASS) }

#define Q_ENUM_REGISTER(CLASS) Q_ENUM_NS(CLASS)
#else
#define Q_ENUM_BEGIN(CLASS) \
    class HES_EXPORT CLASS : public QObject \
    { \
        Q_OBJECT \
    public:

#define Q_ENUM_END(CLASS) \
    private: \
        Q_DISABLE_COPY(CLASS) \
    }; 

#define Q_ENUM_REGISTER(CLASS) Q_ENUM(CLASS)
#endif

/**
 * @brief Q_DECLARE_PIMPL
 * @details 此宏用于在类中声明一个私有的实现类（PIMPL），
 *          以实现封装和隐藏实现细节的目的。
 */
#define Q_DECLARE_PIMPL(ClassName)                                                 \
    protected:                                                                     \
        explicit ClassName(ClassName##Private &dd,ClassName* parent = nullptr);    \
        QScopedPointer<ClassName##Private> d_ptr;                                  \
    private:                                                                       \
        Q_DISABLE_COPY(ClassName)                                                  \
        Q_DECLARE_PRIVATE(ClassName)

/**
 * @brief Q_PROPERTY_DEFINE_MEMBER_H
 * @details 此宏用于在类中定义一个属性及其相关的 getter、setter 和通知信号。
 * @details header文件中使用时，通常用于声明一个属性，
 *          以及对应的 getter 和 setter 方法。
 */
#define Q_PROPERTY_DEFINE_MEMBER_H(TYPE, M)                                        \
    Q_PROPERTY(TYPE p##M READ get##M WRITE set##M NOTIFY p##M##Changed)            \
public:                                                                            \
    Q_SIGNAL void p##M##Changed();                                                 \
    void set##M(TYPE M);                                                           \
    TYPE get##M() const;

/**
 * @brief Q_PROPERTY_DEFINE_MEMBER_CPP
 * @details 此宏用于在类的实现文件中定义一个属性及其相关的 getter、setter 和通知信号。
 */
#define Q_PROPERTY_DEFINE_MEMBER_CPP(CLASS, TYPE, M)                               \
    void CLASS::set##M(TYPE M)                                                     \
    {                                                                              \
        Q_D(CLASS);                                                                \
        d->_p##M = std::move(M);                                                   \
        Q_EMIT p##M##Changed();                                                    \
    }                                                                              \
    TYPE CLASS::get##M() const                                                     \
    {                                                                              \
        return d_ptr->_p##M;                                                       \
    }

/**
 * @brief 声明一个指向实现类的指针
 * @details 此宏用于在类中声明一个指向实现类的指针，
 *          以实现封装和隐藏实现细节的目的。
 */
#define Q_D_DECLARE_POINTER(CLASS)                                                 \
    protected:                                                                     \
        CLASS* q_ptr;                                                              \
    private:                                                                       \
        Q_DECLARE_PUBLIC(CLASS);
/**
 * @brief 类的私有部分声明一个属性 _p##M
 * @details 此宏用于在类的私有部分声明一个属性 _p##M，
 * 
 */
#define Q_PROPERTY_CREATE_PRIVATE(TYPE, M)                                         \
    private:                                                                       \
        TYPE _p##M;  // 定义私有成员变量 _p##M

#define Q_PRIVATE_CREATE(Type, M)                                                  \
    private:                                                                       \
        TYPE _p##M;

#endif // STDAFX_H