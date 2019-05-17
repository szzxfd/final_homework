#include "mainwindow.h"
#include <QApplication>
/*
 * name: 保卫萝卜皇家侍卫队
 * last modified: 2019.5.17
 *
 * 暂时先写一个map
 * 完成后后期再加上一个mainwindow
 * 利用dialog做主界面
 * main函数中写有关跳转的部分
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
