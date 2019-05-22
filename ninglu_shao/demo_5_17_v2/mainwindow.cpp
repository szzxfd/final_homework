#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadTowerPosition();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTowerPosition()
{
    QPoint pos[] =
    {
        //写一大堆点，maybe以后会用xml
        //first line
        QPoint(130, 100),
        QPoint(230, 100),
        QPoint(400, 100),
        QPoint(500, 100),
        //second line
        QPoint(140, 215),
        QPoint(240, 215),
        QPoint(390, 215),
        QPoint(490, 215),
        //third line
        QPoint(80, 320),
        QPoint(230, 320),
        QPoint(315, 320),
        QPoint(400, 320),
        QPoint(540, 320),
        //fourth line
        QPoint(225, 445),
        QPoint(405, 445)
    };
    int num = sizeof(pos) / sizeof(pos[0]);

    for(int i = 0; i < num; ++ i)
        this->_TowerPositionList.push_back(TowerPosition(pos[i]));
    //update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    //下面是有关游戏胜利or游戏失败

    //下面是加载地图
    QPixmap map_1(":/image/map_1.bmp");

    QPainter mapPainter(&map_1);
    for(auto &towerPosition: this->_TowerPositionList) {
        if(towerPosition.hasShow())
            towerPosition.draw(&mapPainter);
    }
    for(auto &basicTower: this->_BasicTowerList) {
        basicTower->draw(&mapPainter);
        if(basicTower->hasShowRange())
            basicTower->drawRange(&mapPainter);
    }
    QPainter painter(this);
    painter.drawPixmap(0, 0, map_1);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();

    //正经实现基类的放置
    auto curPos = _TowerPositionList.begin();
    while(curPos != _TowerPositionList.end())
    {
        if(curPos->hasShow() && curPos->inRange(pressPos) && !curPos->hasTower())  //以后要添加金币条件
        {
            curPos->setHasTower();
            BasicTower *tower = new BasicTower(curPos->getPos(), this);
            this->_BasicTowerList.push_back(tower);
            update();
            break;
        }
        if(curPos->hasTower() && curPos->inRange(pressPos))
        {
            for(auto &it: this->_BasicTowerList)
            {
                if(it->getPos() == curPos->getPos())
                {
                    if(!it->hasShowRange())
                        it->setHasShowRange();
                    else
                        it->setHasShowRange(false);
                    update();
                    break;
                }
            }
        }

        ++ curPos;
    }
    //鼠标恢复
    this->setCursor(Qt::ArrowCursor);

    //位点变暗
    for(auto &temp: this->_TowerPositionList)
    {
        temp.setHasShow(false);
    }

    /*
     *写着玩的（0.0）
    BasicTower *tower = new BasicTower(pressPos, this);
    this->_BasicTowerList.push_back(tower);
    update();
    */
}



void MainWindow::on_pushButton_clicked()
{
    //改变鼠标形状
    QCursor *myCursor = new QCursor(QPixmap(":/image/move_basic_tower.png"),-1,-1);
    this->setCursor(*myCursor);

    for(auto &temp: this->_TowerPositionList)
    {
        temp.setHasShow();
        update();
    }
}
