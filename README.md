# Schedule
# Qt5+C++

## Schedule

姓名：宋超群

邮箱：171860642@smail.nju.edu.cn

#### 一、项目简介

##### 1.项目名称

- 简单的日程表

##### 2.功能简介

- 方便记录TodoList和日程计划、支持闹钟提醒(播放音乐或推送系统通知），同时显示当前详细的日历信息，包括农历与当前时间等。

##### 3.运行环境

- 项目在Windows10、GMAKE环境下使用Qt开发。



#### 二、项目详情

##### 1.软件名称

- Schedule

##### 2.用法介绍

- 新建事件清单

  ​	点击新建清单

  <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230151944726.png" alt="image-20191230151944726" style="zoom:80%;" />

- 修改清单详情

  ​	双击清单名称

  <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230152125659.png" alt="image-20191230152125659" style="zoom: 80%;" />

- 添加具体步骤

  点击添加按钮	 

  <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230152407597.png" alt="image-20191230152407597" style="zoom:80%;" />

- 修改步骤信息

  ​	双击该步骤即可进行修改

- 已完成该步骤

  ​	单击该步骤，点击已完成，即表示该步骤已做完，可以删除掉。

- 更改其他时间的任务清单

  - 方法一：通过点击日历表上任意一天，所有信息即更新到所选当天，即可修改当天的任务清单。

    ​	 <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230153335933.png" alt="image-20191230153335933" style="zoom:80%;" />

  - 方法二：通过修改日历表下方的日期，然后点击跳转即可跳转至所修改日期，并对当日的任务清单进行修改。然后点击返回当日即可回到现在的日期。

    <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230153838663.png" alt="image-20191230153838663" style="zoom:80%;" />

    

- 设置事件提醒

  - 点击该事件，点击设置提醒按钮，然后修改要提醒的具体时间。

  <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230154149996.png" alt="image-20191230154149996" style="zoom:80%;" />

  - 到时间需要提醒时，系统会弹出窗口，推送一条通知，同时会响起音乐进行提醒。（具体声音请打开附件——该工程的exe打包文件，可以直接运行。）

  <img src="C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230154535831.png" alt="image-20191230154535831" style="zoom:80%;" />

- 删除行程清单

  单击该清单，点击删除清单按钮即可。

#### 三、工程设计

##### 1.设计思路

- 最外层窗口用一个Widget界面的对象，弹出的窗口用Dialog界面。每一个窗口作一个单独的对象，窗口中的组件都是其成员。

![image-20191230171715952](C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230171715952.png)



- 类的关系与结构

  ![image-20191230172425231](C:\Users\宋超群\AppData\Roaming\Typora\typora-user-images\image-20191230172425231.png)

- 数据结构

  - 界面

    > ```c
    >  //ui界面
    >  Ui::Widget *ui;
    > ```

  - 文件

    > ```c
    > 	//对文件的操作，File类
    >  File myFile;    
    > ```

  - 时间

    > ```c
    >  //当前日期
    >  QDate Today;
    >  //选择的日期
    >  QDate CurrentDay;
    >  //当前时间
    >  QTime CurrentTime;
    > ```

  - 存储

    > ```c
    >  //储存每天所有的任务清单
    >  QMap<QDate,QMap<QString,QList<QString>>> DateList;
    >  //储存已选择当天的任务清单
    >  QMap<QString,QList<QString>> TodayList;
    >  //储存已选择事件的所有步骤信息
    >  QList<QString> EventList;
    >  //储存所有需要提醒的事件及系统推送提醒内容
    >  QMap<QDate,QMap<QString,QTime>> RemindList;
    > ```

- 设计细节

  - 主窗口Widget：集成日历，日期与时间显示，日期的跳转，任务清单显示与删除等功能。

    - 普通函数

      ```c
      //日期跳转设置
      void DateSet();
      
      //任务列表添加任务
      void TodoList();
      
      //弹窗提醒并播放音乐
      void Notify();
      ```

      

    - 槽函数

      ```c
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
      ```

  - list.h/cpp:获得输入的时间标题

    > ```c
    > private slots:
    >  
    >  //获得输入的事件标题
    >  void on_buttonBox_accepted();
    > ```

  - event.h/cpp:对当前事件的具体步骤进行修改

    > ```c
    >  //显示当前行的步骤信息
    >  void ItemShow();
    > 
    > private slots:
    >  
    >  //添加步骤
    >  void on_pushButton_clicked();
    > 
    >  //删除步骤——该步骤已完成
    >  void on_pushButton_2_clicked();
    > 
    >  //双击该步骤进行修改
    >  void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    > ```

  - incident.h/cpp:对具体步骤进行信息修改或添加

    > ```c
    > private slots:
    >  //获取输入步骤信息
    >  void on_buttonBox_accepted();
    > ```

  - remind_time_set.h/cpp:对某事件需要提醒的时间进行设置

    > ```c
    > private slots:
    >  //获取输入步骤信息
    >  void on_buttonBox_accepted();
    > ```

  - for_remind.h/cpp:弹窗并播放音乐提醒需要进行的事件

    > ```c
    >  //构造函数，传入需要提醒的事件信息
    >  forRemind(QWidget *parent = nullptr, QString aReminder = "");
    > 
    >  //播放铃声
    >  void forMusicPlay();
    > ```

  - file.h/cpp:储存或读取相关文件

    > ```c
    >  //文件名
    >  QString FileName;
    >  //文件路径
    >  QString FilePath;
    > ```

    > ```c
    >  //储存事件清单
    >  bool save(QMap<QDate,QMap<QString,QList<QString>>> &DateList = Tmp);
    > 
    >  //读取事件清单
    >  bool read(QMap<QDate,QMap<QString,QList<QString>>> &DateList = Tmp);
    > 
    >  //储存需要提醒的事件清单
    >  void notification_save(QMap<QDate,QMap<QString,QTime>> &RemindList = Tmp1);
    > 
    >  //读取需要提醒的事件清单
    >  void notification_read(QMap<QDate,QMap<QString,QTime>> &RemindList = Tmp1);
    > ```

  - date.h/cpp:获取所选择日期的农历信息

    > ```c
    >  //获得农历信息
    >  QDate get_lunar();
    > ```

#### 四、问题及感悟

- 在显示实时更新的时间时试了很久总是不能成功。最终发现问题所在：应该将更新时间的函数与timeout()函数connect起来，所以更新时间的函数必须是槽函数，即要将timeUpdate()函数写在slots函数的列表下，不能以普通函数的形式存在。
- 读写文件时最初的想法是在存储的时候将之前储存的文件夹直接全部删掉，但是也是不能成功。后来才知道删除文件夹时，该文件夹必须是空的。我便放弃删除文件夹，改用替换文件的方式进行更新。
- 刚开始添加新的组件时并没有意识到到组件名的重要性，并没有对组件的名称就行修改，到后来出现bug的时候就开始分不清谁是谁了，而且到最后的时候一旦修改一个组件的名字，就要到所有用到这个名字的函数与文件里进行修改，还很容易遗漏，十分繁琐。



这些事告诉我们在使用函数之前一定要实现了解其原理与本质，否则可能产生的结果与预期相去甚远。并且一定要养成好的命名习惯，不仅是自己定义的变量名与函数名，在ui界面添加的组件名与槽函数名同样非常重要。
