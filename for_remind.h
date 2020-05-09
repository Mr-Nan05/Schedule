#ifndef FOR_REMIND_H
#define FOR_REMIND_H
#include <QUrl>
#include <QDir>
#include <QDialog>
#include <QMediaPlayer>
#include <QtMultimedia/qmediaplayer.h>
namespace Ui {
class forRemind;
}

class forRemind : public QDialog
{
    Q_OBJECT

public:
    explicit forRemind(QWidget *parent = nullptr);


    //构造函数，传入需要提醒的事件信息
    forRemind(QWidget *parent = nullptr, QString aReminder = "");
       ~forRemind();
    //播放铃声
    void forMusicPlay();

private:
    Ui::forRemind *ui;

    QMediaPlayer *aPlayer;
};

#endif // FOR_REMIND_H
