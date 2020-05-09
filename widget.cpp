#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    myFile.read(DateList);
    myFile.notification_read(RemindList);

    Today = CurrentDay = QDate::currentDate();
    DateSet();

    QTimer *timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(TimeUpdate()));

    timer->start(1000);
}

Widget::~Widget()
{
    myFile.save(DateList);
    myFile.notification_save(RemindList);
    delete ui;
}

void Widget::DateSet()
{
    QString str = CurrentDay.toString("yyyy  -  MM  -  dd\n");
    str = str + '\n' + "      ";
    switch(CurrentDay.dayOfWeek()){
    case 1:str += "Monday";break;
    case 2:str += "Tuesday";break;
    case 3:str += "Wednesday";break;
    case 4:str += "Thursday";break;
    case 5:str += "Friday";break;
    case 6:str += "Saturday";break;
    case 7:str += "Sunday";break;
    }
    ui->label_4->setText(str);
    ui->lineEdit->setText(CurrentDay.toString("yyyy"));
    ui->lineEdit_2->setText(CurrentDay.toString("MM"));
    ui->lineEdit_3->setText(CurrentDay.toString("dd"));

    Date date(CurrentDay);
    QDate lunar = date.get_lunar();
    str = lunar.toString("  MM - dd");
    ui->label_7->setText(str);

    TodoList();
}

void Widget::TodoList()
{
    ui->listWidget->clear();
    TodayList = DateList.value(CurrentDay);
    foreach(const QString &ListName, TodayList.keys()){
        QListWidgetItem *aItem = new QListWidgetItem;
        aItem->setText(ListName);
        ui->listWidget->addItem(aItem);
    }
}

void Widget::on_calendarWidget_clicked(const QDate &date)
{
    CurrentDay = date;
    DateSet();
}

void Widget::on_pushButton_clicked()
{
    QString year = ui->lineEdit->text();
    QString month = ui->lineEdit_2->text();
    QString day = ui->lineEdit_3->text();
    QDate date(year.toInt(),month.toInt(),day.toInt());
    CurrentDay = date;
    ui->calendarWidget->setSelectedDate(CurrentDay);
    DateSet();
}

void Widget::on_pushButton_2_clicked()
{
    CurrentDay = QDate::currentDate();
    ui->calendarWidget->setSelectedDate(CurrentDay);
    DateSet();
}

void Widget::on_pushButton_3_clicked()
{
    List *EventList =new List(this);
    EventList->setWindowTitle("新建清单");
    QList<QString> Tmp;
    EventList->exec();
    if(EventList->result() != EventList->Rejected)
        DateList[CurrentDay].insert(EventList->GetEventlist(),Tmp);
    DateSet();
}

void Widget::on_pushButton_4_clicked()
{
    QListWidgetItem *aItem = nullptr;
    aItem = ui->listWidget->currentItem();

    if(aItem != nullptr){
        QString EventName = aItem->text();
        DateList[CurrentDay].remove(EventName);
    }
    DateSet();
}

void Widget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Event *aEvent = new Event(this,DateList[CurrentDay][item->text()]);
    aEvent->setWindowTitle("添加任务");
    aEvent->exec();

    if(aEvent->result() == aEvent->Rejected){
        DateList[CurrentDay][item->text()] = aEvent->GetIncidents();
        DateSet();
    }

}

void Widget::TimeUpdate()
{
    QDateTime aCurrentTime = QDateTime::currentDateTime();

    QString myCurrentTime = aCurrentTime.toString("hh:mm:ss");
    QString myCurrentDate = aCurrentTime.toString("yyyy_MM_dd");

    ui->label_8->setText(myCurrentTime);
    CurrentTime = QTime::currentTime();
    Notify();
}

void Widget::Notify()
{
    foreach(const QString &aCurrentEvent, RemindList[Today].keys()){
        if(RemindList[Today][aCurrentEvent].toString("hh:mm:ss") == CurrentTime.toString("hh:mm:ss")){
            forRemind *aReminder = new forRemind(this, aCurrentEvent);
            aReminder->setWindowTitle("行程提醒");
            aReminder->exec();
        }
    }
}

void Widget::on_pushButton_5_clicked()
{
    Remind *aReminder = new Remind(this);
    aReminder->setWindowTitle("提醒时间设置");
    aReminder->exec();

    if(aReminder->result() != aReminder->Rejected){
        QTime aRemindTime = aReminder->GetRemindTime();
        //QMap<QString, QTime> TodayReminders = RemindList[CurrentDay];
        QString aRemindEvent = ui->listWidget->currentItem()->text();
        RemindList[CurrentDay][aRemindEvent] = aRemindTime;
    }
}
