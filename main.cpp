#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //解决汉字乱码问题
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("日程表");
    w.show();
    return a.exec();
}
