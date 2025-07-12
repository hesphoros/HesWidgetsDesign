#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

#include "HesApplication.h"
#include "HesTheme.h"

/**
 * @brief 简单的 HesApplication 测试示例
 * 
 * 这个示例展示了 HesApplication 的基本使用方法：
 * 1. 获取单例实例
 * 2. 初始化应用程序
 * 3. 基本功能测试
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "开始 HesApplication 简单测试";
    
    // 1. 获取 HesApplication 单例实例
    qDebug() << " 获取 HesApplication 实例...";
    Q_ASSERT(hesApp != nullptr);
    qDebug() << " HesApplication 实例获取成功";
    
    // 2. 初始化 HesApplication
    qDebug() << " 初始化 HesApplication...";
    hesApp->init();
    qDebug() << " HesApplication 初始化完成";
    
    // 3. 获取 HesTheme 实例
    qDebug() << " 获取 HesTheme 实例...";
    Q_ASSERT(hesTheme != nullptr);
    qDebug() << " HesTheme 实例获取成功";
    
    // 4. 创建测试窗口
    QWidget window;
    window.setWindowTitle("HesApplication 简单测试");
    window.resize(400, 300);
    
    QVBoxLayout* layout = new QVBoxLayout(&window);
    
    // 状态标签
    QLabel* statusLabel = new QLabel();
    statusLabel->setWordWrap(true);
    statusLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 10px; border-radius: 5px; }");
    layout->addWidget(statusLabel);
    
    // 更新状态信息的函数
    auto updateStatus = [&]() {
        QString status = QString(
            "HesApplication 测试状态:\n\n"
            " 实例已创建: %1\n"
            " 已初始化: 是\n"
            " Mica 图像路径: %2\n"
            " 窗口显示模式: %3\n"
            " 当前主题: %4"
        ).arg(hesApp ? "是" : "否")
         .arg(hesApp ? hesApp->getHesMicaImagePath() : "N/A")
         .arg(static_cast<int>(hesApp ? hesApp->getWindowDisplayMode() : HesApplicationType::Normal))
         .arg(hesTheme->getThemeMode() == HesThemeType::Light ? "浅色" : "深色");
        
        statusLabel->setText(status);
    };
    
    // 初始更新状态
    updateStatus();
    
    // 测试按钮
    QPushButton* testButton = new QPushButton("测试功能", &window);
    layout->addWidget(testButton);
    
    // 连接测试按钮
    QObject::connect(testButton, &QPushButton::clicked, [&]() {
        qDebug() << " 开始功能测试...";
        
        // 测试光标检测
        bool cursorTest = hesApp->containsCursorToItem(testButton);
        qDebug() << " 光标检测测试:" << (cursorTest ? "通过" : "失败");
        
        // 测试主题切换
        auto currentTheme = hesTheme->getThemeMode();
        auto newTheme = (currentTheme == HesThemeType::Light) ? 
                        HesThemeType::Dark : HesThemeType::Light;
        hesTheme->setThemeMode(newTheme);
        qDebug() << " 主题切换测试: 从" << currentTheme << "切换到" << newTheme;
        
        // 测试窗口同步
        hesApp->syncWindowDisplayMode(&window, true);
        qDebug() << " 窗口同步测试: 已同步";
        
        updateStatus();
        qDebug() << " 功能测试完成";
    });
    
    // 信号连接测试
    QObject::connect(hesTheme, &HesTheme::themeModeChanged, [](HesThemeType::ThemeMode mode) {
        qDebug() << " 收到主题变更信号:" << (mode == HesThemeType::Light ? "浅色" : "深色");
    });
    
    QObject::connect(hesApp, &HesApplication::pWindowDisplayModeChanged, []() {
        qDebug() << " 收到窗口显示模式变更信号";
    });
    
    // 显示窗口
    window.show();
    qDebug() << "测试窗口已显示";
   
    qDebug() << " 进入事件循环...";
    return app.exec();
}
