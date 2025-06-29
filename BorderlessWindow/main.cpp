#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QSlider>
#include <QProgressBar>
#include <QSpinBox>
#include <QTimer>
#include <QDebug>
#include "borderlesswindow.h"

//跨平台的无边框窗口，仅使用 Qt 提供的模块功能
class Widget : public BorderlessWindow
{
public:    
    Widget(QWidget * parent = nullptr):
        BorderlessWindow{parent}
    {
        setupUI();
        this->setWindowTitle("Star Rail");
        this->setWindowIcon(QPixmap(":/Star Rail.png"));
    }
    
private:
    void setupUI()
    {
        QWidget *centralWidget = this->qWidgetUseInSetupUi();
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        
        // 创建标题标签
        QLabel *titleLabel = new QLabel("愿此行，终抵群星");
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("QLabel { font-size: 24px; font-weight: bold; color: #333; margin: 20px; }");
        mainLayout->addWidget(titleLabel);
        
        // 创建功能区域
        QHBoxLayout *contentLayout = new QHBoxLayout();
        
        // 左侧控件组
        QGroupBox *leftGroup = new QGroupBox("控件测试");
        QVBoxLayout *leftLayout = new QVBoxLayout(leftGroup);
        
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setPlaceholderText("请输入文本...");
        leftLayout->addWidget(lineEdit);
        
        QComboBox *comboBox = new QComboBox();
        comboBox->addItems({"选项1", "选项2", "选项3"});
        leftLayout->addWidget(comboBox);
        
        QCheckBox *checkBox = new QCheckBox("启用功能");
        leftLayout->addWidget(checkBox);
        
        QRadioButton *radio1 = new QRadioButton("选项A");
        QRadioButton *radio2 = new QRadioButton("选项B");
        leftLayout->addWidget(radio1);
        leftLayout->addWidget(radio2);
        
        QSlider *slider = new QSlider(Qt::Horizontal);
        slider->setRange(0, 100);
        slider->setValue(50);
        leftLayout->addWidget(slider);
        
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setRange(0, 100);
        spinBox->setValue(50);
        leftLayout->addWidget(spinBox);
        
        QProgressBar *progressBar = new QProgressBar();
        progressBar->setValue(75);
        leftLayout->addWidget(progressBar);
        
        contentLayout->addWidget(leftGroup);
        
        // 右侧文本区域
        QGroupBox *rightGroup = new QGroupBox("文本区域");
        QVBoxLayout *rightLayout = new QVBoxLayout(rightGroup);
        
        QTextEdit *textEdit = new QTextEdit();
        textEdit->setPlainText("这是一个无边框窗口的测试界面。\n\n"
                              "功能特点：\n"
                              "- 自定义无边框设计\n"
                              "- 支持窗口拖拽调整大小\n"
                              "- 现代化的界面风格\n"
                              "- 完整的窗口控制按钮\n");
        rightLayout->addWidget(textEdit);
        
        contentLayout->addWidget(rightGroup);
        mainLayout->addLayout(contentLayout);
        
        // 底部按钮
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addStretch();
        
        QPushButton *btn1 = new QPushButton("确定");
        QPushButton *btn2 = new QPushButton("取消");
        QPushButton *btn3 = new QPushButton("应用");
        
        btn1->setStyleSheet("QPushButton { padding: 8px 16px; }");
        btn2->setStyleSheet("QPushButton { padding: 8px 16px; }");
        btn3->setStyleSheet("QPushButton { padding: 8px 16px; }");
        
        buttonLayout->addWidget(btn1);
        buttonLayout->addWidget(btn2);
        buttonLayout->addWidget(btn3);
        
        mainLayout->addLayout(buttonLayout);
        
        // 设置布局边距
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSpacing(15);
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
