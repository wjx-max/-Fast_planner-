/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/nrypp_hmi/main_window.hpp"

#include <OgreColourValue.h>
#include <QInputDialog>
#include <QProcess>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <QComboBox>
#include <QDialog>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace nrypp_hmi {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/


// 将 QColor 转换为 Ogre::ColourValue
Ogre::ColourValue MainWindow::QColorToOgreColourValue(const QColor& color) {
    return Ogre::ColourValue(
        color.redF(),   // 将 red 转换为 [0, 1] 范围的浮动值
        color.greenF(), // 将 green 转换为 [0, 1] 范围的浮动值
        color.blueF(),  // 将 blue 转换为 [0, 1] 范围的浮动值
        color.alphaF()  // 将 alpha 转换为 [0, 1] 范围的浮动值
    );
}



MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{

    // ROS 初始化
    int argc_copy = argc;
    char **argv_copy = argv;

    ros::init(argc_copy, argv_copy, "qt_gui_node");
	ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.


    //设置窗口为固定大小
    this->setFixedSize(956, 510);

    setWindowTitle("虚实结合操作系统平台");
	setWindowIcon(QIcon(":/images/icon.png"));

    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    //初始化rviz
    myrviz=new qrviz(ui.layout_rviz);


    //rviz传入默认参数设置
    //Fixed Frame
    myrviz->Set_FixedFrame("world");

    //BackgroundColor
    QColor BackgroundColor(255, 255, 255);  // 设置rviz的背景颜色
    Ogre::ColourValue ogreColor = QColorToOgreColourValue(BackgroundColor);
    myrviz->Set_BackgroundColor(ogreColor);

    //Grid
    QColor color=QColor(0,160,160);
    myrviz->Display_Grid(30,color,true);

    //RobotModel
    //RobotModel1
    //myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);
    //RobotModel2
    //myrviz->Display_RobotModel2("/tb3_2/robot_description","/tb3_2",true);
    //RobotModel3
    //myrviz->Display_RobotModel3("/tb3_3/robot_description","/tb3_3",false);
    //RobotModel4
    //myrviz->Display_RobotModel4("/tb3_4/robot_description","/tb3_4",false);

    //Map
    //localmap1
    //myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);
    //localmap2
    //myrviz->Display_localmap2("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);
    //localmap3
    //myrviz->Display_localmap3("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

    //Robotmap
    //robotmap1
    //QColor Robotmapcolor1=QColor(15,255,255);
    //myrviz->Display_Robotmap1("/tb3_1/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor1,true);
    //QColor Robotmapcolor2=QColor(15,255,255);
    //myrviz->Display_Robotmap2("/tb3_2/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor2,true);

}

MainWindow::~MainWindow() {}





void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 获取当前窗口的大小
    QRect rect(0, 0, this->width(), this->height());  // 使用窗口的宽高作为矩形的大小

    QImage image(":images/nryppbj.jpg");
    image = image.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawImage(rect, image);

    //会自动在rect区域进行缩放
    painter.drawImage(rect,image);

}


//按钮1初始化
void nrypp_hmi::MainWindow::closeProcess()
{
    if (tb3 != nullptr) {
        tb3->terminate();  // 尝试优雅地关闭进程
        //tb3->waitForFinished(20000);  // 等待最多20秒钟，允许进程完成清理工作

        if (tb3->state() != QProcess::NotRunning) {

            tb3_close=new QProcess;
            tb3_close->start("bash");
            tb3_close->write("killall gzserver\n");
            tb3_close->write("rosnode list | xargs rosnode kill\n");
            tb3->terminate();
            qDebug()<<"111"<<endl;
        }

        delete tb3;  // 删除 QProcess 实例
        tb3 = nullptr;
    }
}




void nrypp_hmi::MainWindow::on_pushButton_init_clicked()
{

    int value = QInputDialog::getInt(
                this,
                "请输入机器人数量",
                "输入范围1-6");


    if(value == 1){
        closeProcess();

        tb3=new QProcess;
        tb3->start("bash");
        tb3->write("roslaunch plan_manage tb3_1.launch\n");



        myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);

        //Map
        //localmap1
        myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

    }

    else if(value == 2){
        closeProcess();

        tb3=new QProcess;
        tb3->start("bash");
        tb3->write("roslaunch plan_manage tb3_2.launch\n");


        myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);
        myrviz->Display_RobotModel2("/tb3_2/robot_description","/tb3_2",true);


        //Map
        //localmap1
        myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

        //Robotmap
        //robotmap1
        QColor Robotmapcolor1=QColor(15,255,255);
        myrviz->Display_Robotmap1("/tb3_1/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor1,true);
        //robotmap2
        QColor Robotmapcolor2=QColor(15,255,255);
        myrviz->Display_Robotmap2("/tb3_2/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor2,true);

    }

    else if(value == 3){
        closeProcess();

        tb3=new QProcess;
        tb3->start("bash");
        tb3->write("roslaunch plan_manage tb3_3.launch\n");


        myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);
        myrviz->Display_RobotModel2("/tb3_2/robot_description","/tb3_2",true);
        myrviz->Display_RobotModel3("/tb3_3/robot_description","/tb3_3",true);


        //Map
        //localmap1
        myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

        //Robotmap
        //robotmap1
        QColor Robotmapcolor1=QColor(15,255,255);
        myrviz->Display_Robotmap1("/tb3_1/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor1,true);
        //robotmap2
        QColor Robotmapcolor2=QColor(15,255,255);
        myrviz->Display_Robotmap2("/tb3_2/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor2,true);
        //robotmap2
        QColor Robotmapcolor3=QColor(15,255,255);
        myrviz->Display_Robotmap3("/tb3_3/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor3,true);


    }



    else if(value == 4){
        closeProcess();

        tb3=new QProcess;
        tb3->start("bash");
        tb3->write("roslaunch plan_manage tb3_4.launch\n");


        myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);
        myrviz->Display_RobotModel2("/tb3_2/robot_description","/tb3_2",true);
        myrviz->Display_RobotModel3("/tb3_3/robot_description","/tb3_3",true);
        myrviz->Display_RobotModel4("/tb3_4/robot_description","/tb3_4",true);


        //Map
        //localmap1
        myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

        //Robotmap
        //robotmap1
        QColor Robotmapcolor1=QColor(15,255,255);
        myrviz->Display_Robotmap1("/tb3_1/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor1,true);
        //robotmap2
        QColor Robotmapcolor2=QColor(15,255,255);
        myrviz->Display_Robotmap2("/tb3_2/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor2,true);
        //robotmap3
        QColor Robotmapcolor3=QColor(15,255,255);
        myrviz->Display_Robotmap3("/tb3_3/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor3,true);
        //robotmap4
        QColor Robotmapcolor4=QColor(15,255,255);
        myrviz->Display_Robotmap4("/tb3_4/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor4,true);


    }


    else if(value == 5){
        closeProcess();

        tb3=new QProcess;
        tb3->start("bash");
        tb3->write("roslaunch plan_manage tb3_5.launch\n");


        myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);
        myrviz->Display_RobotModel2("/tb3_2/robot_description","/tb3_2",true);
        myrviz->Display_RobotModel3("/tb3_3/robot_description","/tb3_3",true);
        myrviz->Display_RobotModel4("/tb3_4/robot_description","/tb3_4",true);
        myrviz->Display_RobotModel5("/tb3_5/robot_description","/tb3_5",true);


        //Map
        //localmap1
        myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

        //Robotmap
        //robotmap1
        QColor Robotmapcolor1=QColor(15,255,255);
        myrviz->Display_Robotmap1("/tb3_1/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor1,true);
        //robotmap2
        QColor Robotmapcolor2=QColor(15,255,255);
        myrviz->Display_Robotmap2("/tb3_2/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor2,true);
        //robotmap3
        QColor Robotmapcolor3=QColor(15,255,255);
        myrviz->Display_Robotmap3("/tb3_3/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor3,true);
        //robotmap4
        QColor Robotmapcolor4=QColor(15,255,255);
        myrviz->Display_Robotmap4("/tb3_4/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor4,true);
        //robotmap4
        QColor Robotmapcolor5=QColor(15,255,255);
        myrviz->Display_Robotmap5("/tb3_5/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor5,true);

    }



    else if(value == 6){
        closeProcess();

        tb3=new QProcess;
        tb3->start("bash");
        tb3->write("roslaunch plan_manage tb3_6.launch\n");


        myrviz->Display_RobotModel1("/tb3_1/robot_description","/tb3_1",true);
        myrviz->Display_RobotModel2("/tb3_2/robot_description","/tb3_2",true);
        myrviz->Display_RobotModel3("/tb3_3/robot_description","/tb3_3",true);
        myrviz->Display_RobotModel4("/tb3_4/robot_description","/tb3_4",true);
        myrviz->Display_RobotModel5("/tb3_5/robot_description","/tb3_5",true);
        myrviz->Display_RobotModel6("/tb3_6/robot_description","/tb3_6",true);



        //Map
        //localmap1
        myrviz->Display_localmap1("/map_generator/global_cloud","Flat Squares",0.15,"AxisColor",true);

        //Robotmap
        //robotmap1
        QColor Robotmapcolor1=QColor(15,255,255);
        myrviz->Display_Robotmap1("/tb3_1/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor1,true);
        //robotmap2
        QColor Robotmapcolor2=QColor(15,255,255);
        myrviz->Display_Robotmap2("/tb3_2/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor2,true);
        //robotmap3
        QColor Robotmapcolor3=QColor(15,255,255);
        myrviz->Display_Robotmap3("/tb3_3/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor3,true);
        //robotmap4
        QColor Robotmapcolor4=QColor(15,255,255);
        myrviz->Display_Robotmap4("/tb3_4/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor4,true);
        //robotmap5
        QColor Robotmapcolor5=QColor(15,255,255);
        myrviz->Display_Robotmap5("/tb3_5/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor5,true);
        //robotmap6
        QColor Robotmapcolor6=QColor(15,255,255);
        myrviz->Display_Robotmap6("/tb3_5/point_cloud_map","Boxes",0.15,"FlatColor",Robotmapcolor6,true);

    }


    else{
        QMessageBox::about(this,"警告","机器人数量应在1-6之间");
        tb3_close=new QProcess;
        tb3_close->start("bash");
        tb3_close->write("killall gzserver\n");
        tb3_close->write("rosnode list | xargs rosnode kill\n");
        tb3->terminate();
    }


}



//按钮2控制机器人移动
void nrypp_hmi::MainWindow::on_pushButton_control_clicked()
{

    int value = QInputDialog::getInt(
                this,
                "输入机器人序号",
                "输入范围1-6");

    myrviz->Set_Goal_Pose(value);

    if(value==0||value>6) {
        QMessageBox::about(this,"警告","机器人序号应在1-6之间");
    }


}



//按钮3使机器人在环境中随机分布
void nrypp_hmi::MainWindow::on_pushButton_random_clicked()
{
    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_randomRun_node";  // 你要检查的节点名称
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
        QMessageBox::about(this, "随机分布", "当前任务已终止 \n正在重新分配 ...");
    }

    // 启动新的进程，运行 roslaunch
    QProcess* tb3 = new QProcess;
    tb3->start("bash");
    QTextStream stream(tb3);
    stream << "roslaunch formation tb3_all_randomRun.launch\n";
    QMessageBox::about(this, "随机分布", "已随机分配目标位置.");
}


//按钮4 是机器人在指定目标位置集合

void nrypp_hmi::MainWindow::on_pushButton_massed_clicked()
{

    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_assemble_node";  // 要检查的节点名称
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
        QMessageBox::information(this, "编队集结", "编队正在集结中 ...");
        return;
    }

    // 如果节点未运行，启动新的进程
    tb3 = new QProcess;
    tb3->start("bash");
    QTextStream stream(tb3);
    stream << "roslaunch formation tb3_all_assemble.launch\n";
    QMessageBox::about(this, "编队集结", "编队集结已启动.");


//        QString node_name = "/tb3_all_assembleNew_node";  // 要检查的节点名称
//        QProcess check_node;

//        // 执行 rosnode list 命令来检查节点是否在运行
//        check_node.start("rosnode list");
//        check_node.waitForFinished();  // 等待命令执行完毕

//        QString output = check_node.readAllStandardOutput();

//        // 判断是否包含节点名称
//        if (output.contains(node_name)) {
//            // 如果节点正在运行，显示消息框并返回
//            QMessageBox::information(this, "编队集结", "编队正在集结中...");

//            return;  // 不执行后续操作
//        }

//        // 如果节点未运行，启动新的进程
//        tb3 = new QProcess;
//        tb3->start("bash");
//        QTextStream stream(tb3);
//        stream << "roslaunch formation tb3_all_assemblenew.launch\n";
//        QMessageBox::information(this, "编队集结", "编队集结已启动.");

}


//按钮5 的配套子节点
//检查形成开路节点是否存在
void nrypp_hmi::MainWindow::checkOpenNodeExistence()
{
    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_openroad_node";  // 要检查的节点名称
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
    }
}



//按钮5 编队形成开路
void nrypp_hmi::MainWindow::on_pushButton_open_clicked()
{

    // 如果节点未运行，启动新的进程
    tb3 = new QProcess;
    tb3->start("bash");
    QTextStream stream(tb3);
    stream << "roslaunch formation tb3_all_openroad.launch\n";
    QMessageBox::about(this, "形成开路", "形成开路已启动.");


    // 延迟3秒钟后检查节点
    QTimer::singleShot(2000, this, &nrypp_hmi::MainWindow::checkOpenNodeExistence);

    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_openroad_node";  // 要检查的节点名称
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
    }

}



//按钮6 的配套子节点
//检查缺口愈合节点是否存在
void nrypp_hmi::MainWindow::checkCloseNodeExistence()
{
    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_closeroad_node";  // 要检查的节点名称
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
    }
}





//按钮6 编队缺口愈合
void nrypp_hmi::MainWindow::on_pushButton_close_clicked()
{

    checkCloseNodeExistence();
    // 如果节点未运行，启动新的进程
    tb3 = new QProcess;
    tb3->start("bash");
    QTextStream stream(tb3);
    stream << "roslaunch formation tb3_all_closeroad.launch\n";
    QMessageBox::about(this, "缺口愈合", "缺口愈合已启动.");


    // 延迟3秒钟后检查节点
    QTimer::singleShot(2000, this, &nrypp_hmi::MainWindow::checkCloseNodeExistence);

    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_closeroad_node";  // 要检查的节点名称
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
    }

    checkCloseNodeExistence();
}


void nrypp_hmi::MainWindow::checkMoveNodeExistence(){

    // 检查节点是否已经在运行
    QString node_name = "/tb3_all_move_node";  // 要检查的节点名称tb3_all_move_node
    QProcess check_node;
    check_node.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node.waitForFinished();
    QString output = check_node.readAllStandardOutput();

    // 判断节点是否存在
    if (output.contains(node_name)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node;
        kill_node.start("rosnode kill " + node_name);
        kill_node.waitForFinished(); // 等待停止节点的进程完成
    }



}



//按钮7 编队迁移
void nrypp_hmi::MainWindow::on_pushButton_move_clicked()
{

    checkMoveNodeExistence();

    QMessageBox::about(this, "编队迁移", "编队迁移已启动\n请选择编队目标位置.");
    // 如果节点未运行，启动新的进程
    tb3 = new QProcess;
    tb3->start("bash");
    QTextStream stream(tb3);
    stream << "roslaunch formation tb3_all_move.launch\n";

    myrviz->Set_Goal1_Pose();




    // 延迟3秒钟后检查节点
    QTimer::singleShot(8000, this, &nrypp_hmi::MainWindow::checkMoveNodeExistence);

//    // 检查节点是否已经在运行
//    QString node_name = "/tb3_all_move_node";  // 要检查的节点名称
//    QProcess check_node;
//    check_node.start("rosnode list");

//    // 等待进程执行完并获取输出
//    check_node.waitForFinished();
//    QString output = check_node.readAllStandardOutput();

//    // 判断节点是否存在
//    if (output.contains(node_name)) {
//        // 如果节点在运行，则先停止它
//        QProcess kill_node;
//        kill_node.start("rosnode kill " + node_name);
//        kill_node.waitForFinished(); // 等待停止节点的进程完成
//    }

}



void nrypp_hmi::MainWindow::checkChangeNodeExistence(){

    // 1.检查矩形队形节点是否已经在运行
    QString node_name1 = "/tb3_all_moveRectangle_node";  // 要检查的节点名称
    QProcess check_node1;
    check_node1.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node1.waitForFinished();
    QString output1 = check_node1.readAllStandardOutput();

    // 判断节点是否存在
    if (output1.contains(node_name1)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node1;
        kill_node1.start("rosnode kill " + node_name1);
        kill_node1.waitForFinished(); // 等待停止节点的进程完成
    }


    // 2.检查三角形队形节点是否已经在运行
    QString node_name2 = "/tb3_all_moveTriangle_node";  // 要检查的节点名称
    QProcess check_node2;
    check_node2.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node2.waitForFinished();
    QString output2 = check_node2.readAllStandardOutput();

    // 判断节点是否存在
    if (output2.contains(node_name2)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node2;
        kill_node2.start("rosnode kill " + node_name2);
        kill_node2.waitForFinished(); // 等待停止节点的进程完成
    }


    // 3.检查一字形队形节点是否已经在运行
    QString node_name3 = "/tb3_all_moveOne_node";  // 要检查的节点名称
    QProcess check_node3;
    check_node3.start("rosnode list");

    // 等待进程执行完并获取输出
    check_node3.waitForFinished();
    QString output3 = check_node3.readAllStandardOutput();

    // 判断节点是否存在
    if (output3.contains(node_name3)) {
        // 如果节点在运行，则先停止它
        QProcess kill_node3;
        kill_node3.start("rosnode kill " + node_name3);
        kill_node3.waitForFinished(); // 等待停止节点的进程完成
    }




}




//按钮8 队形变换
void nrypp_hmi::MainWindow::on_pushButton_change_clicked()
{

    bool ok;

    // 获取编队队形名称
        QString formationName = QInputDialog::getText(this,
                                                      "请输入编队队形",
                                                      "输入期望的编队队形名称:\n提示：矩形、三角形、一字形",
                                                      QLineEdit::Normal,
                                                      "", &ok);

        if (!ok || formationName.isEmpty()) {
            QMessageBox::warning(this, "输入无效", "编队队形名称不能为空！");
            return; // 如果用户取消或没有输入有效的队形名，则退出
        }

        // 根据输入的机器人数量和编队队形名称做后续判断或处理
        if (formationName == "矩形") {
            // 处理“矩形”队形
            checkChangeNodeExistence();



            // 如果节点未运行，启动新的进程
            tb3 = new QProcess;
            tb3->start("bash");
            QTextStream stream(tb3);
            stream << "roslaunch formation tb3_all_moveRectangle.launch\n";


        } else if (formationName == "三角形") {
            // 处理“三角形”队形
            checkChangeNodeExistence();

            // 如果节点未运行，启动新的进程
            tb3 = new QProcess;
            tb3->start("bash");
            QTextStream stream(tb3);
            stream << "roslaunch formation tb3_all_moveTriangle.launch\n";



        } else if (formationName == "一字形") {
            // 处理“一字形”队形
            checkChangeNodeExistence();

            // 如果节点未运行，启动新的进程
            tb3 = new QProcess;
            tb3->start("bash");
            QTextStream stream(tb3);
            stream << "roslaunch formation tb3_all_moveOne.launch\n";


        } else {
            QMessageBox::warning(this, "未知队形", "未识别的队形名称！");
        }



}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About ..."),tr("<h2>PACKAGE_NAME Test Program 0.10</h2><p>Copyright Yujin Robot</p><p>This package needs an about description.</p>"));
}


void MainWindow::closeEvent(QCloseEvent *event)
{
	QMainWindow::closeEvent(event);
}

}  // namespace nrypp_hmi

