#ifndef QRVIZ_HPP
#define QRVIZ_HPP

#include <QObject>
#include <ros/ros.h>
#include <rviz/visualization_manager.h>
#include <rviz/render_panel.h>
#include <rviz/display.h>
#include <rviz/tool_manager.h>
#include <rviz/tool.h>
#include <QVBoxLayout>

class qrviz
{
public:
    //按钮1初始化函数
    qrviz(QVBoxLayout* layout);
    void Set_FixedFrame(QString Frame_name);
    void Set_BackgroundColor(Ogre::ColourValue BackgroundColor);

    void Display_Grid(int Cell_Count,QColor color,bool enable);
    void Display_RobotModel1(QString Robot_Description,QString TF_Prefix,bool enable);
    void Display_RobotModel2(QString Robot_Description,QString TF_Prefix,bool enable);
    void Display_RobotModel3(QString Robot_Description,QString TF_Prefix,bool enable);
    void Display_RobotModel4(QString Robot_Description,QString TF_Prefix,bool enable);
    void Display_RobotModel5(QString Robot_Description,QString TF_Prefix,bool enable);
    void Display_RobotModel6(QString Robot_Description,QString TF_Prefix,bool enable);

    //环境地图
    void Display_localmap1(QString loacalmap_topic,QString style,double size,QString color_Transform,bool enable);
    void Display_localmap2(QString loacalmap_topic,QString style,double size,QString color_Transform,bool enable);
    void Display_localmap3(QString loacalmap_topic,QString style,double size,QString color_Transform,bool enable);

    //机器人间避障
    void Display_Robotmap1(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable);
    void Display_Robotmap2(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable);
    void Display_Robotmap3(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable);
    void Display_Robotmap4(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable);
    void Display_Robotmap5(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable);
    void Display_Robotmap6(QString robotmap_topic,QString style,double size,QString color_Transform,QColor color,bool enable);

    //按钮2接口函数
    void Set_Goal_Pose(int value);
    //按钮7接口函数
    void Set_Goal1_Pose();

private:
    //按钮1初始化
    rviz::RenderPanel* render_panel_= nullptr;
    rviz::VisualizationManager* manager_=nullptr;
    rviz::Display* Grid_= NULL;
    rviz::Display* RobotModel1_= NULL;
    rviz::Display* RobotModel2_= NULL;
    rviz::Display* RobotModel3_= NULL;
    rviz::Display* RobotModel4_= NULL;
    rviz::Display* RobotModel5_= NULL;
    rviz::Display* RobotModel6_= NULL;

    rviz::Display* localmap1_= NULL;
    rviz::Display* localmap2_= NULL;
    rviz::Display* localmap3_= NULL;

    rviz::Display* robotmap1_= NULL;
    rviz::Display* robotmap2_= NULL;
    rviz::Display* robotmap3_= NULL;
    rviz::Display* robotmap4_= NULL;
    rviz::Display* robotmap5_= NULL;
    rviz::Display* robotmap6_= NULL;

    //按钮2控制移动
    rviz::ToolManager* tool_manager_;

};

#endif // QRVIZ_HPP
