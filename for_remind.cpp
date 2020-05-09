#include "for_remind.h"
#include "ui_for_remind.h"

forRemind::forRemind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forRemind)
{
    ui->setupUi(this);
}

forRemind::forRemind(QWidget *parent, QString aReminder):
    QDialog(parent),
    ui(new Ui::forRemind)
{
     ui->setupUi(this);
     ui->label_2->setText(aReminder);
     forMusicPlay();
}

forRemind::~forRemind()
{
    delete ui;
}


void forRemind::forMusicPlay()
{
    aPlayer = new QMediaPlayer;

    QString myCurrentPath = QDir::currentPath();
    aPlayer->setMedia(QUrl::fromLocalFile(myCurrentPath + "/music/alarm.mp3"));
    aPlayer->setVolume(50);
    aPlayer->play();
}
