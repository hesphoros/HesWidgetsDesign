#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QDebug>

#include "HesApplication.h"
#include "HesTheme.h"

class HesApplicationTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HesApplicationTestWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setupUI();
        connectSignals();
        updateStatus();
    }

private slots:
    void onInitClicked()
    {
        // 初始化 HesApplication
        hesApp->init();
        logOutput->append(" HesApplication 已初始化");
        updateStatus();
    }

    void onWindowDisplayModeChanged()
    {
        auto mode = static_cast<HesApplicationType::WindowDisplayMode>(
            displayModeCombo->currentData().toInt());
        
        hesApp->setWindowDisplayMode(mode);
        logOutput->append(QString(" 窗口显示模式已更改为: %1")
                         .arg(getDisplayModeString(mode)));
        updateStatus();
    }

    void onThemeModeChanged()
    {
        auto mode = static_cast<HesThemeType::ThemeMode>(
            themeModeCombo->currentData().toInt());
        
        hesTheme->setThemeMode(mode);
        logOutput->append(QString(" 主题模式已更改为: %1")
                         .arg(mode == HesThemeType::Light ? "浅色" : "深色"));
        updateStatus();
    }

    void onSyncWindowClicked()
    {
        hesApp->syncWindowDisplayMode(this, true);
        logOutput->append(" 窗口已同步显示模式");
        updateStatus();
    }

    void onTestCursorClicked()
    {
        bool isUnderCursor = hesApp->containsCursorToItem(testButton);
        logOutput->append(QString(" 光标测试结果: %1")
                         .arg(isUnderCursor ? "光标在按钮上" : "光标不在按钮上"));
    }

private:
    void setupUI()
    {
        setWindowTitle("HesApplication 测试示例");
        setMinimumSize(800, 600);
        
        auto* mainLayout = new QVBoxLayout(this);
        
        // 创建控制面板
        auto* controlGroup = new QGroupBox("控制面板", this);
        auto* controlLayout = new QVBoxLayout(controlGroup);
        
        // 初始化按钮
        initButton = new QPushButton("初始化 HesApplication", this);
        controlLayout->addWidget(initButton);
        
        // 窗口显示模式选择
        auto* displayModeLayout = new QHBoxLayout();
        displayModeLayout->addWidget(new QLabel("窗口显示模式:", this));
        displayModeCombo = new QComboBox(this);
        displayModeCombo->addItem("正常", static_cast<int>(HesApplicationType::Normal));
        displayModeCombo->addItem("Hes Mica", static_cast<int>(HesApplicationType::HesMica));
        displayModeCombo->addItem("Mica", static_cast<int>(HesApplicationType::Mica));
        displayModeCombo->addItem("Mica Alt", static_cast<int>(HesApplicationType::MicaAlt));
        displayModeCombo->addItem("Acrylic", static_cast<int>(HesApplicationType::Acrylic));
        displayModeCombo->addItem("DWM Blur", static_cast<int>(HesApplicationType::DWMBlur));
        displayModeLayout->addWidget(displayModeCombo);
        controlLayout->addLayout(displayModeLayout);
        
        // 主题模式选择
        auto* themeModeLayout = new QHBoxLayout();
        themeModeLayout->addWidget(new QLabel("主题模式:", this));
        themeModeCombo = new QComboBox(this);
        themeModeCombo->addItem("浅色", static_cast<int>(HesThemeType::Light));
        themeModeCombo->addItem("深色", static_cast<int>(HesThemeType::Dark));
        themeModeLayout->addWidget(themeModeCombo);
        controlLayout->addLayout(themeModeLayout);
        
        // 功能测试按钮
        auto* buttonLayout = new QHBoxLayout();
        syncWindowButton = new QPushButton("同步窗口显示模式", this);
        testButton = new QPushButton("测试光标检测", this);
        buttonLayout->addWidget(syncWindowButton);
        buttonLayout->addWidget(testButton);
        controlLayout->addLayout(buttonLayout);
        
        mainLayout->addWidget(controlGroup);
        
        // 状态显示面板
        auto* statusGroup = new QGroupBox("当前状态", this);
        auto* statusLayout = new QVBoxLayout(statusGroup);
        
        statusLabel = new QLabel("状态信息将在这里显示...", this);
        statusLabel->setWordWrap(true);
        statusLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: 10px; border-radius: 5px; }");
        statusLayout->addWidget(statusLabel);
        
        mainLayout->addWidget(statusGroup);
        
        // 日志输出面板
        auto* logGroup = new QGroupBox("操作日志", this);
        auto* logLayout = new QVBoxLayout(logGroup);
        
        logOutput = new QTextEdit(this);
        logOutput->setMaximumHeight(200);
        logOutput->setReadOnly(true);
        logOutput->append(" HesApplication 测试示例已启动");
        logLayout->addWidget(logOutput);
        
        mainLayout->addWidget(logGroup);
    }

    void connectSignals()
    {
        connect(initButton, &QPushButton::clicked, this, &HesApplicationTestWidget::onInitClicked);
        connect(displayModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &HesApplicationTestWidget::onWindowDisplayModeChanged);
        connect(themeModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &HesApplicationTestWidget::onThemeModeChanged);
        connect(syncWindowButton, &QPushButton::clicked, this, &HesApplicationTestWidget::onSyncWindowClicked);
        connect(testButton, &QPushButton::clicked, this, &HesApplicationTestWidget::onTestCursorClicked);
        
        // 连接HesApplication信号
        connect(hesApp, &HesApplication::pWindowDisplayModeChanged, [this]() {
            logOutput->append(" 收到窗口显示模式变更信号");
            updateStatus();
        });
        
        // 连接HesTheme信号
        connect(hesTheme, &HesTheme::themeModeChanged, [this](HesThemeType::ThemeMode mode) {
            logOutput->append(QString(" 收到主题模式变更信号: %1")
                             .arg(mode == HesThemeType::Light ? "浅色" : "深色"));
        });
    }

    void updateStatus()
    {
        QString status = QString(
            " HesApplication 实例状态:\n"
            " 窗口显示模式: %1\n"
            " Mica图像路径: %2\n\n"
            " HesTheme 实例状态:\n"
            " 当前主题模式: %3"
        ).arg(getDisplayModeString(hesApp->getWindowDisplayMode()))
         .arg(hesApp->getHesMicaImagePath())
         .arg(hesTheme->getThemeMode() == HesThemeType::Light ? "浅色" : "深色");
        
        statusLabel->setText(status);
        
        // 更新组合框的当前选择
        displayModeCombo->setCurrentIndex(
            displayModeCombo->findData(static_cast<int>(hesApp->getWindowDisplayMode())));
        themeModeCombo->setCurrentIndex(
            themeModeCombo->findData(static_cast<int>(hesTheme->getThemeMode())));
    }

    QString getDisplayModeString(HesApplicationType::WindowDisplayMode mode)
    {
        switch (mode) {
            case HesApplicationType::Normal: return "正常";
            case HesApplicationType::HesMica: return "Hes Mica";
            case HesApplicationType::Mica: return "Mica";
            case HesApplicationType::MicaAlt: return "Mica Alt";
            case HesApplicationType::Acrylic: return "Acrylic";
            case HesApplicationType::DWMBlur: return "DWM Blur";
            default: return "未知";
        }
    }

private:
    QPushButton* initButton;
    QComboBox* displayModeCombo;
    QComboBox* themeModeCombo;
    QPushButton* syncWindowButton;
    QPushButton* testButton;
    QLabel* statusLabel;
    QTextEdit* logOutput;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序基本信息
    app.setApplicationName("HesWidgetsDesign Example");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Hesphoros");
    
    qDebug() << " 启动 HesWidgetsDesign 测试示例";
    
    // 创建并显示测试窗口
    HesApplicationTestWidget testWidget;
    testWidget.show();
    
    qDebug() << " 测试窗口已创建并显示";
    
    return app.exec();
}

#include "main.moc"

