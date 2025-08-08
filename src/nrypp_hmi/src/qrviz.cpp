#include "../include/nrypp_hmi/qrviz.hpp"

#include <QDebug>
#include <QColor>
#include <QMessageBox>

qrviz::qrviz(QVBoxLayout* layout)
{

    //创建rviz panel
    render_panel_=new rviz::RenderPanel();

    //向layout添加
    layout->addWidget(render_panel_);

    //创建rviz控制对象
    manager_=new rviz::VisualizationManager(render_panel_);

    tool_manager_=manager_->getToolManager(); //tool_manager_可以看成是一个工具箱

    ROS_ASSERT(manager_!=NULL);
    //初始化render_panel 实现放大缩小等操作
    render_panel_->initialize(manager_->getSceneManager(),manager_);

    //初始化rviz控制对象
    manager_->initialize();
    manager_->startUpdate();
    manager_->removeAllDisplays();

}



void qrviz::Set_FixedFrame(QString Frame_name)
{

    manager_->setFixedFrame(Frame_name);
    qDebug()<<manager_->getFixedFrame();

}


void qrviz::Set_BackgroundColor(Ogre::ColourValue BackgroundColor)
{

    manager_->getRenderPanel()->setBackgroundColor(BackgroundColor);

}


void qrviz::Display_Grid(int Cell_Count,QColor color,bool enable)
{

    if(Grid_!=NULL){
        delete Grid_;
        Grid_=NULL;
    }


    Grid_=manager_->createDisplay("rviz/Grid","myGrid",enable);

    Grid_->subProp("Plane Cell Count")->setValue(Cell_Count);
    Grid_->subProp("Color")->setValue(color);

    ROS_ASSERT(Grid_!=NULL);//防止出现闪退的bug进行断言
}


void qrviz::Display_RobotModel1(QString Robot_Description,QString TF_Prefix,bool enable)
{


    if(RobotModel1_!=NULL){
        delete RobotModel1_;
        RobotModel1_=NULL;
    }


    RobotModel1_=manager_->createDisplay("rviz/RobotModel","myRobotModel1",enable);
    RobotModel1_->subProp("Robot Description")->setValue(Robot_Description);
    RobotModel1_->subProp("TF Prefix")->setValue(TF_Prefix);

    ROS_ASSERT(RobotModel1_!=NULL);//防止出现闪退的bug进行断言

}



void qrviz::Display_RobotModel2(QString Robot_Description,QString TF_Prefix,bool enable)
{


    if(RobotModel2_!=NULL){
        delete RobotModel2_;
        RobotModel2_=NULL;
    }



    RobotModel2_=manager_->createDisplay("rviz/RobotModel","myRobotModel2",enable);
    RobotModel2_->subProp("Robot Description")->setValue(Robot_Description);
    RobotModel2_->subProp("TF Prefix")->setValue(TF_Prefix);

    ROS_ASSERT(RobotModel2_!=NULL);//防止出现闪退的bug进行断言

}



void qrviz::Display_RobotModel3(QString Robot_Description,QString TF_Prefix,bool enable)
{


    if(RobotModel3_!=NULL){
        delete RobotModel3_;
        RobotModel3_=NULL;
    }



    RobotModel3_=manager_->createDisplay("rviz/RobotModel","myRobotModel3",enable);
    RobotModel3_->subProp("Robot Description")->setValue(Robot_Description);
    RobotModel3_->subProp("TF Prefix")->setValue(TF_Prefix);

    ROS_ASSERT(RobotModel3_!=NULL);//防止出现闪退的bug进行断言

}


void qrviz::Display_RobotModel4(QString Robot_Description,QString TF_Prefix,bool enable)
{


    if(RobotModel4_!=NULL){
        delete RobotModel4_;
        RobotModel4_=NULL;
    }


    RobotModel4_=manager_->createDisplay("rviz/RobotModel","myRobotModel4",enable);
    RobotModel4_->subProp("Robot Description")->setValue(Robot_Description);
    RobotModel4_->subProp("TF Prefix")->setValue(TF_Prefix);

    ROS_ASSERT(RobotModel4_!=NULL);//防止出现闪退的bug进行断言

}



void qrviz::Display_RobotModel5(QString Robot_Description,QString TF_Prefix,bool enable)
{


    if(RobotModel5_!=NULL){
        delete RobotModel5_;
        RobotModel5_=NULL;
    }


    RobotModel5_=manager_->createDisplay("rviz/RobotModel","myRobotModel5",enable);
    RobotModel5_->subProp("Robot Description")->setValue(Robot_Description);
    RobotModel5_->subProp("TF Prefix")->setValue(TF_Prefix);

    ROS_ASSERT(RobotModel5_!=NULL);//防止出现闪退的bug进行断言

}


void qrviz::Display_RobotModel6(QString Robot_Description,QString TF_Prefix,bool enable)
{


    if(RobotModel6_!=NULL){
        delete RobotModel6_;
        RobotModel6_=NULL;
    }


    RobotModel6_=manager_->createDisplay("rviz/RobotModel","myRobotModel5",enable);
    RobotModel6_->subProp("Robot Description")->setValue(Robot_Description);
    RobotModel6_->subProp("TF Prefix")->setValue(TF_Prefix);

    ROS_ASSERT(RobotModel6_!=NULL);//防止出现闪退的bug进行断言

}


void qrviz::Display_localmap1(QString loacalmap_topic,QString style,double size,QString color_Transform,bool enable)
{

    if(localmap1_!=NULL){
        delete localmap1_;
        localmap1_=NULL;
    }


    localmap1_=manager_->createDisplay("rviz/PointCloud2","localmap1",enable);
    localmap1_->subProp("Topic")->setValue(loacalmap_topic);
    localmap1_->subProp("Style")->setValue(style);
    localmap1_->subProp("Size (m)")->setValue(size);
    localmap1_->subProp("Color Transformer")->setValue(color_Transform);

    ROS_ASSERT(localmap1_!=NULL);//防止出现闪退的bug进行断言



}


void qrviz::Display_localmap2(QString loacalmap_topic,QString style,double size,QString color_Transform,bool enable)
{

    if(localmap2_!=NULL){
        delete localmap2_;
        localmap2_=NULL;
    }


    localmap2_=manager_->createDisplay("rviz/PointCloud2","localmap2",enable);
    localmap2_->subProp("Topic")->setValue(loacalmap_topic);
    localmap2_->subProp("Style")->setValue(style);
    localmap2_->subProp("Size (m)")->setValue(size);
    localmap2_->subProp("Color Transformer")->setValue(color_Transform);

    ROS_ASSERT(localmap2_!=NULL);//防止出现闪退的bug进行断言



}


void qrviz::Display_localmap3(QString loacalmap_topic,QString style,double size,QString color_Transform,bool enable)
{

    if(localmap3_!=NULL){
        delete localmap3_;
        localmap3_=NULL;
    }


    localmap3_=manager_->createDisplay("rviz/PointCloud2","localmap3",enable);
    localmap3_->subProp("Topic")->setValue(loacalmap_topic);
    localmap3_->subProp("Style")->setValue(style);
    localmap3_->subProp("Size (m)")->setValue(size);
    localmap3_->subProp("Color Transformer")->setValue(color_Transform);

    ROS_ASSERT(localmap3_!=NULL);//防止出现闪退的bug进行断言



}



void qrviz::Display_Robotmap1(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable){


    if(robotmap1_!=NULL){
        delete robotmap1_;
        robotmap1_=NULL;
    }


    robotmap1_=manager_->createDisplay("rviz/PointCloud2","robotmap1",enable);
    robotmap1_->subProp("Topic")->setValue(robotmap_topic);
    robotmap1_->subProp("Style")->setValue(style);
    robotmap1_->subProp("Size (m)")->setValue(size);
    robotmap1_->subProp("Color Transformer")->setValue(color_Transform);
    robotmap1_->subProp("Color")->setValue(color);

    ROS_ASSERT(robotmap1_!=NULL);//防止出现闪退的bug进行断言



}


void qrviz::Display_Robotmap2(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable){


    if(robotmap2_!=NULL){
        delete robotmap2_;
        robotmap2_=NULL;
    }


    robotmap2_=manager_->createDisplay("rviz/PointCloud2","robotmap2",enable);
    robotmap2_->subProp("Topic")->setValue(robotmap_topic);
    robotmap2_->subProp("Style")->setValue(style);
    robotmap2_->subProp("Size (m)")->setValue(size);
    robotmap2_->subProp("Color Transformer")->setValue(color_Transform);
    robotmap2_->subProp("Color")->setValue(color);

    ROS_ASSERT(robotmap2_!=NULL);//防止出现闪退的bug进行断言



}


void qrviz::Display_Robotmap3(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable){


    if(robotmap3_!=NULL){
        delete robotmap3_;
        robotmap3_=NULL;
    }


    robotmap3_=manager_->createDisplay("rviz/PointCloud2","robotmap3",enable);
    robotmap3_->subProp("Topic")->setValue(robotmap_topic);
    robotmap3_->subProp("Style")->setValue(style);
    robotmap3_->subProp("Size (m)")->setValue(size);
    robotmap3_->subProp("Color Transformer")->setValue(color_Transform);
    robotmap3_->subProp("Color")->setValue(color);

    ROS_ASSERT(robotmap3_!=NULL);//防止出现闪退的bug进行断言



}



void qrviz::Display_Robotmap4(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable){


    if(robotmap4_!=NULL){
        delete robotmap4_;
        robotmap4_=NULL;
    }


    robotmap4_=manager_->createDisplay("rviz/PointCloud2","robotmap4",enable);
    robotmap4_->subProp("Topic")->setValue(robotmap_topic);
    robotmap4_->subProp("Style")->setValue(style);
    robotmap4_->subProp("Size (m)")->setValue(size);
    robotmap4_->subProp("Color Transformer")->setValue(color_Transform);
    robotmap4_->subProp("Color")->setValue(color);

    ROS_ASSERT(robotmap4_!=NULL);//防止出现闪退的bug进行断言


}




void qrviz::Display_Robotmap5(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable){


    if(robotmap5_!=NULL){
        delete robotmap5_;
        robotmap5_=NULL;
    }


    robotmap5_=manager_->createDisplay("rviz/PointCloud2","robotmap5",enable);
    robotmap5_->subProp("Topic")->setValue(robotmap_topic);
    robotmap5_->subProp("Style")->setValue(style);
    robotmap5_->subProp("Size (m)")->setValue(size);
    robotmap5_->subProp("Color Transformer")->setValue(color_Transform);
    robotmap5_->subProp("Color")->setValue(color);

    ROS_ASSERT(robotmap5_!=NULL);//防止出现闪退的bug进行断言


}



void qrviz::Display_Robotmap6(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable){


    if(robotmap6_!=NULL){
        delete robotmap6_;
        robotmap6_=NULL;
    }


    robotmap6_=manager_->createDisplay("rviz/PointCloud2","robotmap6",enable);
    robotmap6_->subProp("Topic")->setValue(robotmap_topic);
    robotmap6_->subProp("Style")->setValue(style);
    robotmap6_->subProp("Size (m)")->setValue(size);
    robotmap6_->subProp("Color Transformer")->setValue(color_Transform);
    robotmap6_->subProp("Color")->setValue(color);

    ROS_ASSERT(robotmap6_!=NULL);//防止出现闪退的bug进行断言


}


//按钮2
void qrviz::Set_Goal_Pose(int value)
{

    rviz::Tool* current_tool_=tool_manager_->addTool("rviz/SetGoal");
    //获取容器属性
    rviz::Property* pro=current_tool_->getPropertyContainer();

    //设置发布导航目标点的topic
    if(value == 1)
    {
        pro->subProp("Topic")->setValue("/tb3_1/move_base_simple/goal");
    }

    else if(value == 2)
    {
        pro->subProp("Topic")->setValue("/tb3_2/move_base_simple/goal");
    }

    else if(value == 3)
    {
        pro->subProp("Topic")->setValue("/tb3_3/move_base_simple/goal");
    }

    else if(value == 4)
    {
        pro->subProp("Topic")->setValue("/tb3_4/move_base_simple/goal");
    }

    else if(value == 5)
    {
        pro->subProp("Topic")->setValue("/tb3_5/move_base_simple/goal");
    }

    else if(value == 6)
    {
        pro->subProp("Topic")->setValue("/tb3_6/move_base_simple/goal");
    }
    //设置当前使用的工具
    tool_manager_->setCurrentTool(current_tool_);

}


//按钮7
void qrviz::Set_Goal1_Pose()
{
    rviz::Tool* current_tool_=tool_manager_->addTool("rviz/SetGoal");
    //获取容器属性
    rviz::Property* pro=current_tool_->getPropertyContainer();

    pro->subProp("Topic")->setValue("/tb3_1/move_base_simple/goal");


    //设置当前使用的工具
    tool_manager_->setCurrentTool(current_tool_);

}
