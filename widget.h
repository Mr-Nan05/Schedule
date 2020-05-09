#ifndef WIDGET_H
#define WIDGET_H
#include <QTimer>
#include <QWidget>
#include <QDateTime>
#include <QtGlobal>
#include <QTextCodec>
#include "list.h"
#include "date.h"
#include "file.h"
#include "event.h"
#include "for_remind.h"
#include "remind_time_set.h"
#include "ui_widget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //日期跳转设置
    void DateSet();
    //任务列表添加任务
    void TodoList();
    //弹窗提醒并播放音乐
    void Notify();

    //void TimeUpdate();


public slots:

    //实时更新时间的槽函数
    void TimeUpdate();

private slots:

    //通过日历表改变当前日期
    void on_calendarWidget_clicked(const QDate &date);

    //修改日期并跳转
    void on_pushButton_clicked();

    //返回当日
    void on_pushButton_2_clicked();

    //新建任务清单
    void on_pushButton_3_clicked();

    //删除该任务清单
    void on_pushButton_4_clicked();

    //双击修改当前任务
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    //设置闹钟提醒
    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;
    File myFile;

    //当前日期
    QDate Today;
    //选择的日期
    QDate CurrentDay;
    //当前时间
    QTime CurrentTime;

    //储存每天所有的任务清单
    QMap<QDate,QMap<QString,QList<QString>>> DateList;
    //储存已选择当天的任务清单
    QMap<QString,QList<QString>> TodayList;
    //储存已选择事件的所有步骤信息
    QList<QString> EventList;
    //储存所有需要提醒的事件及系统推送提醒内容
    QMap<QDate,QMap<QString,QTime>> RemindList;

};
#endif // WIDGET_H
