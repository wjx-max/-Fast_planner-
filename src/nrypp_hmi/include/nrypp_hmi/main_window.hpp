/**
 * @file /include/nrypp_hmi/main_window.hpp
 *
 * @brief Qt based gui for nrypp_hmi.
 *
 * @date November 2010
 **/
#ifndef nrypp_hmi_MAIN_WINDOW_H
#define nrypp_hmi_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "qrviz.hpp"
#include <QProcess>


/*****************************************************************************
** Namespace
*****************************************************************************/

namespace nrypp_hmi {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

    void closeEvent(QCloseEvent *event); // Overloaded function
    void paintEvent(QPaintEvent *event);

    //BackgroundColor 将 QColor 转换为 Ogre::ColourValue
    Ogre::ColourValue QColorToOgreColourValue(const QColor& color);
    //检查形成开路节点是否存在
    void checkOpenNodeExistence();
    //检查缺口愈合节点是否存在
    void checkCloseNodeExistence();
    //检查队形变换节点是否存在
    void checkChangeNodeExistence();
    //检查编队迁移节点是否存在
    void checkMoveNodeExistence();

    //优雅的关闭打开的进程
    void closeProcess();



public Q_SLOTS:
	void on_actionAbout_triggered();



private slots:
    void on_pushButton_init_clicked();
    void on_pushButton_control_clicked();
    void on_pushButton_random_clicked();
    void on_pushButton_massed_clicked();
    void on_pushButton_open_clicked();
    void on_pushButton_close_clicked();
    void on_pushButton_move_clicked();
    void on_pushButton_change_clicked();

private:
	Ui::MainWindowDesign ui;
	QNode qnode;
    qrviz* myrviz=nullptr;


    QProcess *tb3 = NULL;
    QProcess *tb3_close = NULL;



};

}  // namespace nrypp_hmi

#endif // nrypp_hmi_MAIN_WINDOW_H
