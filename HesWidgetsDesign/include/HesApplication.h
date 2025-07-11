#ifndef HESAPPLICATION_H
#define HESAPPLICATION_H

#include <QIcon>
#include <QObject>
#include "common/common_defs.h"
#include "Singleton.h"

#define hesApp HesApplication::getInstance()

class HesApplicationPrivate;

class HES_EXPORT HesApplication : public QObject
{
    Q_OBJECT
    // PIMPL
    Q_DECLARE_PIMPL(HesApplication)
    // Singleton
    HES_SINGLETON_CREATE_H(HesApplication)

    Q_PROPERTY_DEFINE_MEMBER_H(HesApplicationType::WindowDisplayMode, WindowDisplayMode)
    // Mica Image Path
    Q_PROPERTY_DEFINE_MEMBER_H(QString, HesMicaImagePath)
private:
    explicit HesApplication(QObject* parent = nullptr);
    ~HesApplication() override;
public:
    void init();
    /**
     * @brief Synchronize the window display mode.
     *
     * @param widget The widget to synchronize.
     * @param isSync Whether to synchronize the display mode.
     */
    void syncWindowDisplayMode(QWidget* widget, bool isSync = true);
    
    /**
     * @brief Check if the cursor is within the item.
     * 检查光标是否在指定控件上
     *
     * @param item The item to check.
     * @return true If the cursor is within the item.
     * @return false If the cursor is not within the item.
     */
    static bool containsCursorToItem(QWidget* item);
};


#endif // HESAPPLICATION_H