#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "basictower.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:

    void on_pushButton_clicked();

private:
    void loadTowerPosition();

private:
    Ui::MainWindow *ui;

    QList<TowerPosition> _TowerPositionList;
    QList<BasicTower *> _BasicTowerList;
};

#endif // MAINWINDOW_H
