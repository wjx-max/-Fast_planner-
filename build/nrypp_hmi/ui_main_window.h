/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_title;
    QPushButton *pushButton_init;
    QPushButton *pushButton_control;
    QPushButton *pushButton_random;
    QPushButton *pushButton_massed;
    QPushButton *pushButton_open;
    QPushButton *pushButton_close;
    QPushButton *pushButton_move;
    QPushButton *pushButton_change;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout_rviz;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QStringLiteral("MainWindowDesign"));
        MainWindowDesign->resize(956, 510);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QStringLiteral("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 956, 510));
        label->setTextFormat(Qt::AutoText);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/nryppbj.jpg")));
        label_title = new QLabel(centralwidget);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(710, 100, 148, 50));
        label_title->setPixmap(QPixmap(QString::fromUtf8(":/images/title.jpg")));
        pushButton_init = new QPushButton(centralwidget);
        pushButton_init->setObjectName(QStringLiteral("pushButton_init"));
        pushButton_init->setGeometry(QRect(650, 160, 121, 41));
        pushButton_init->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb1.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb1_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_control = new QPushButton(centralwidget);
        pushButton_control->setObjectName(QStringLiteral("pushButton_control"));
        pushButton_control->setGeometry(QRect(790, 160, 121, 41));
        pushButton_control->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb2.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb2_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_random = new QPushButton(centralwidget);
        pushButton_random->setObjectName(QStringLiteral("pushButton_random"));
        pushButton_random->setGeometry(QRect(650, 240, 121, 41));
        pushButton_random->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb3.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb3_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_massed = new QPushButton(centralwidget);
        pushButton_massed->setObjectName(QStringLiteral("pushButton_massed"));
        pushButton_massed->setGeometry(QRect(790, 240, 121, 41));
        pushButton_massed->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb4.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb4_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_open = new QPushButton(centralwidget);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(650, 320, 121, 41));
        pushButton_open->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb5.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb5_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_close = new QPushButton(centralwidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(790, 320, 121, 41));
        pushButton_close->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb6.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb6_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_move = new QPushButton(centralwidget);
        pushButton_move->setObjectName(QStringLiteral("pushButton_move"));
        pushButton_move->setGeometry(QRect(650, 400, 121, 41));
        pushButton_move->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb7.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb7_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        pushButton_change = new QPushButton(centralwidget);
        pushButton_change->setObjectName(QStringLiteral("pushButton_change"));
        pushButton_change->setGeometry(QRect(790, 400, 121, 41));
        pushButton_change->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"\n"
"image:url(:/images/pb8.jpg);\n"
"border:2px double rgb(114, 159, 207);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::hover\n"
"{\n"
"\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"\n"
"image:url(:/images/pb8_pressed.jpg);\n"
"border:2px double rgb(238, 238, 236);\n"
"border-radius:8px;\n"
"\n"
"}"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 70, 491, 411));
        layout_rviz = new QVBoxLayout(verticalLayoutWidget);
        layout_rviz->setSpacing(0);
        layout_rviz->setObjectName(QStringLiteral("layout_rviz"));
        layout_rviz->setContentsMargins(0, 0, 0, 0);
        MainWindowDesign->setCentralWidget(centralwidget);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", Q_NULLPTR));
        label->setText(QString());
        label_title->setText(QString());
        pushButton_init->setText(QString());
        pushButton_control->setText(QString());
        pushButton_random->setText(QString());
        pushButton_massed->setText(QString());
        pushButton_open->setText(QString());
        pushButton_close->setText(QString());
        pushButton_move->setText(QString());
        pushButton_change->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
